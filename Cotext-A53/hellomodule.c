
/*

内核模块  

字符设备驱动 


*/

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/uaccess.h>
#include <linux/string.h>
#include <linux/cdev.h>
#include <linux/fs.h>
#include <asm/gpio.h>
#include <asm/atomic.h>
#include <linux/semaphore.h>
#include <linux/wait.h>
#include <linux/poll.h>
#include <mach/s5p6818_irq.h>
#include <linux/interrupt.h>
#include <linux/types.h>
#include <asm/io.h>
#include <asm/signal.h>
#include <linux/sched.h>
#include <linux/delay.h>
#include <linux/slab.h>



//GPIO口定义

#define PAD_GPIO_A			(0 * 32)
#define PAD_GPIO_B			(1 * 32)
#define PAD_GPIO_C		 	(2 * 32)
#define PAD_GPIO_D			(3 * 32)
#define PAD_GPIO_E			(4 * 32)
#define PAD_GPIO_ALV		(5 * 32)


//PA 28

#define		PHY_GPIOA_BASE	 	0xC001A000
#define		GPIO_OUT			0x00
#define		GPIO_OUT_ENB		0x04
#define 	GPIO_ALTFN0			0x20
#define 	GPIO_ALTFN1			0x24


//用于保存映射后的GPIOA的基地址，虚拟地址
uint32_t  *IO_GPIOA_BASE = NULL;



//定义 + key 的中断号
#define  ADD_KEY_IRQ      (IRQ_GPIO_B_START+8)


//定义表示字符设备的cdev结构体变量
struct cdev  hello_cdev;

#define HELLO_BUF_SIZE   1024

//uint8_t  hello_buf[HELLO_BUF_SIZE] ={0}; //设备缓冲区

uint8_t  *hello_buf = NULL;



//使用信号量来保证 hello_buf 互斥访问
//定义信号量
struct semaphore hello_buf_sema;
static atomic_t atomic = ATOMIC_INIT(1); //定义原子变量并初始化为 1

//使用等待队列实现设备的阻塞访问

//定义并初始化等待队列
DECLARE_WAIT_QUEUE_HEAD(my_queue);
int hello_buf_ready = 0; //1表示有数据可读,0 表示没有数据可读

//定义轮询等待队列
wait_queue_head_t	hello_pool_que; 


//定义异步通知链表头指针
struct fasync_struct  *hello_fasyncX;


//定义tasklet 结构体变量，实现中断的下半部分处理
struct tasklet_struct keyisr_tasklet;


//定义内核软件定时器
struct timer_list hello_timer;

void turnOnOffLed(int onoff);



//定义定时器超时处理函数
void hello_timeout(unsigned long data)
{
	printk("enter hello_timeout");
	 enable_irq(ADD_KEY_IRQ);
}



//编写add_key 中断服务处理程序

irqreturn_t  addkey_isr(int irq, void *data)
{
	 printk("key add interrupt OK\n");


	
	 disable_irq_nosync(ADD_KEY_IRQ);
	 //延时 100ms
	 hello_timer.expires = jiffies + msecs_to_jiffies(100);
	 add_timer(&hello_timer);

	
	
	 tasklet_schedule(&keyisr_tasklet);

	 return IRQ_HANDLED;
}



//实现中断下半部分的处理函数
void addkey_isr_tasklet(unsigned long arg)
{
	printk("this is addkey_isr_tasklet\n");

}



//实现设备文件操作函数
int hello_open(struct inode *inode, struct file *file)
{
	#if 0
	if(!atomic_dec_and_test(&atomic))
	{
		//设备已经被别的进程打开，不能打开设备
		atomic_inc(&atomic);
		printk("hello device has open\n");

		return -EBUSY;
	}
	#endif 
	printk("hello device open\n");

	return 0;
}



//将设备的数据 ---》 用户空间
ssize_t hello_read (struct file *file, char __user *buf, size_t len, loff_t *offset)
{
	uint32_t iret=0;

	//判断是否有数据可读    hello_buf_ready
	if(hello_buf_ready == 1)
	{
		 //有数据可读 
		down(&hello_buf_sema); //访问共享资源之前获取信号量
		iret = copy_to_user(buf,hello_buf,len); //将内核空间数据传到用户空间
		memset(hello_buf,0,HELLO_BUF_SIZE);
		printk("read hello device\n");
		//释放信号量
		up(&hello_buf_sema);
		hello_buf_ready = 0;

		return len;
		
	}
	else if(hello_buf_ready == 0)
	{
	   // 没有数据可读
	   	if(file->f_flags & O_NONBLOCK)
		{
			//非阻塞访问
			printk("hello device data is not ready!\n");
			return -1;
		}
		else
		{
			//阻塞访问
			 wait_event(my_queue, (hello_buf_ready==1));

			  //wait_event返回，表示有数据可读，继续读数据
			 down(&hello_buf_sema); //访问共享资源之前获取信号量
			 iret = copy_to_user(buf,hello_buf,len); //将内核空间数据传到用户空间
			 memset(hello_buf,0,HELLO_BUF_SIZE);
			 hello_buf_ready = 0;
			 printk("read hello device\n");
			 //释放信号量
			 up(&hello_buf_sema);

			 
		}

		return len;

	   
	}

	return 0;

}


ssize_t hello_write (struct file *file, const char __user *buf, size_t len, loff_t *offset)
{
	uint32_t iret=0;

	down(&hello_buf_sema);

	//用户空间 ---》内核空间
	iret = copy_from_user(hello_buf,buf,len);

	up(&hello_buf_sema);

	hello_buf_ready = 1;
	wake_up(&my_queue); //唤醒等待队列 my_queue 上的进程
	wake_up(&hello_pool_que);//唤醒轮询等待队列上的进程

	//发送异步通知信号SIGIO 给进程
	kill_fasync(&hello_fasyncX,SIGIO,POLL_IN);
	
	
	
	printk("write hello device\n");

	return len;

}


/*
实现hello 设备命令操作

CMD_LED_ON
CMD_LED_OFF

*/


#define HELLO_DEVICE   'A'
#define  CMD_LED_ON  		_IO(HELLO_DEVICE,0)  //打开LED灯命令
#define  CMD_LED_OFF 		_IO(HELLO_DEVICE,1)  //关闭LED灯命令


long hello_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
{
	if(cmd == CMD_LED_ON)
	{
		//打开LED灯, 控制硬件，读写寄存器
		//gpio_set_value(PAD_GPIO_A+28,1);
		turnOnOffLed(1);
		printk("turn on Led OK\n");
		
	}
	else if(cmd == CMD_LED_OFF)
	{
		//关闭LED灯, 控制硬件，读写寄存器
		//gpio_set_value(PAD_GPIO_A+28,0);
		turnOnOffLed(0);
		printk("turn off Led OK\n");
	}

	return 0;
}


//实现轮询操作
unsigned int hello_poll(struct file *file, struct poll_table_struct *p)
{
	int mask = 0;
	poll_wait(file,&hello_pool_que ,p);

	//根据状态标志位，设置轮询的事件信息
	
	if(hello_buf_ready)
	{
		mask |= POLLIN; //设置可读事件标志
	}
	else
	{
		mask |= POLLOUT; //设置可写事件标志
	}
	

	return mask;
}


//实现异步通知函数
int hello_fasync (int fd, struct file *file , int on)
{
	return fasync_helper(fd, file,on, &hello_fasyncX);
}




int hello_release(struct inode *inode, struct file *file)
{

	printk("close hello device\n");
	atomic_inc(&atomic);

	return 0;
}




//定义并初始化 file_operations 结构体
struct file_operations  hello_fops=
{
	.owner = THIS_MODULE,
	.read = hello_read,
	.write = hello_write,
	.open = hello_open,
	.release = hello_release,	
	.unlocked_ioctl = hello_ioctl,
	.poll = hello_poll,
	.fasync = hello_fasync,
};




#define HELLO_MAJOR   200
#define HELLO_MINOR   0

/*
 初始化 hello_cdev 并要将 hello_cdev 加到内核里面
*/

int hello1809_init(void)
{
	int iret = 0;
	uint32_t reg_v = 0;

	//初始化 hello_cdev 
	dev_t hello_devno = MKDEV(HELLO_MAJOR, HELLO_MINOR);

	tasklet_init(&keyisr_tasklet, addkey_isr_tasklet, 0);

	//初始化内核软件定时器
	init_timer(&hello_timer);
	hello_timer.data = 0;
	hello_timer.function = hello_timeout;

	hello_buf = kmalloc(HELLO_BUF_SIZE,GFP_KERNEL);
	memset(hello_buf,0,HELLO_BUF_SIZE);

	//调用ioremap函数 将GPIOA寄存器的物理地址映射到虚拟地址空间
	IO_GPIOA_BASE = ioremap(PHY_GPIOA_BASE,0x80);
	if(IO_GPIOA_BASE == NULL)
	{
		printk("io remap error\n");
		return 0;
	}
	

	iret = request_irq(ADD_KEY_IRQ, addkey_isr,IRQF_DISABLED|IRQF_TRIGGER_FALLING,
						"key",NULL);

	if(iret < 0)
	{
		printk("request irq error\n");
		return 0;
	}

	
	
	//初始化轮询等待队列
	init_waitqueue_head(&hello_pool_que);

	sema_init(&hello_buf_sema, 1);

	/*
		配置GPIOA28 为GPIO口工作模式，输出模式，初始化为低电平

		GPIOAALTFN1  24 25 配置为 00，其他位保持不变
	*/
	
	reg_v = readl(IO_GPIOA_BASE + GPIO_ALTFN1);
	reg_v &= ~(0x3<<24);
	writel(reg_v, IO_GPIOA_BASE + GPIO_ALTFN1);

	//GPIOA 28 设为输出模式 
	reg_v = readl(IO_GPIOA_BASE + GPIO_OUT_ENB);
	reg_v |= (0x1<<28);
	writel(reg_v, IO_GPIOA_BASE + GPIO_OUT_ENB);
	

	//初始化GPIOA28 位 低电平
	reg_v = readl(IO_GPIOA_BASE + GPIO_OUT);
	reg_v &= ~(0x1<<28);
	writel(reg_v, IO_GPIOA_BASE + GPIO_OUT);
	
	

	//gpio_direction_output(PAD_GPIO_A + 28, 0);
	gpio_direction_output(PAD_GPIO_E + 13, 0);
	gpio_direction_output(PAD_GPIO_B + 12, 0);

	cdev_init(&hello_cdev, &hello_fops);
	hello_cdev.owner = THIS_MODULE;

	cdev_add(&hello_cdev,hello_devno,1);

	printk ("Hello1809 module init OK!\n");
	
	return 0;
}


void turnOnOffLed(int onoff)
{
	uint32_t reg_v = 0;
	if(onoff)
	{
		//开灯
		reg_v = readl(IO_GPIOA_BASE + GPIO_OUT);
		reg_v |= 0x1<<28;
		writel(reg_v, IO_GPIOA_BASE + GPIO_OUT);
		
	}
	else
	{
		reg_v = readl(IO_GPIOA_BASE + GPIO_OUT);
		reg_v &= ~(0x1<<28);
		writel(reg_v, IO_GPIOA_BASE + GPIO_OUT);
	}
}


void hello1809_exit(void)  //编写模块退出函数
{
   cdev_del(&hello_cdev);

   free_irq(ADD_KEY_IRQ,NULL);
   kfree(hello_buf); //释放内存
   
   printk ("Goodbye hello1809 world\n"); 
}

module_init(hello1809_init);  //指定模块初始化函数
module_exit(hello1809_exit);  //指定模块退出函数

MODULE_LICENSE ("GPL");  //license 声明






