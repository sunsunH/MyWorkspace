



/*
 最简单的 平台设备总线驱动

 PWM驱动

 GPIOC14 ---> pwm2
 
*/




#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/io.h>
#include <linux/device.h>
#include <asm/uaccess.h>
#include <mach/platform.h>
#include <mach/soc.h>
#include <linux/platform_device.h>
#include <linux/slab.h>


//定义GPIO口寄存器的物理基地址和偏移地址
#define		PHY_GPIOC_BASE	 	0xC001C000
#define		GPIO_OUT			0x00
#define		GPIO_OUT_ENB		0x04
#define 	GPIO_ALTFN0			0x20
#define 	GPIO_ALTFN1			0x24

//定义定时器（PWM）寄存器的物理地址
#define  	PHY_PWM_BASE		0xC0018000
#define  	TCFG0       		 0x00
#define  	TCFG1       		 0x04
#define  	TCON       		 	 0x08
#define  	TCNTB2       		 0x24
#define  	TCMPB2       		 0x28
#define  	TCNTO2      		 0x2C
#define  	TINT_CSTAT       	 0x44




//用于保存映射后的GPIOA的基地址，虚拟地址
void   *IO_GPIOC_BASE = NULL;

//保存映射后的TIME定时器的基地址，虚拟地址
void   *MY_PWM_BASE = NULL;


struct cdev  *pwm_cdev = NULL;

void turn_on_off_pwm(int onoff);
void set_pwm_freq(uint32_t pwm_hz);





//定义 pwm设备 所使用的MEM资源
struct resource mypwm_res[] = 
{
	[0] = 
	{
		.start = PHY_GPIOC_BASE,
		.end = PHY_GPIOC_BASE+0x100,
		.flags = IORESOURCE_MEM,
	},

	[1] = 
	{
		.start = PHY_PWM_BASE,
		.end = PHY_PWM_BASE+0x100,
		.flags = IORESOURCE_MEM,
	},
};



int mypwm_open(struct inode *inode, struct file *file)
{

	printk("open mypwm device\n");


	return 0;
}


#define  PWM_DEVICE   'B'
#define  CMD_PWM_ON  		_IO(PWM_DEVICE,0)  //打开pwm
#define  CMD_PWM_OFF 		_IO(PWM_DEVICE,1)  //关闭pwm
#define  CMD_PWM_SET        _IO(PWM_DEVICE,2)  //设置PWM频率


long mypwm_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
{
	switch(cmd)
	{
		case CMD_PWM_ON:
			turn_on_off_pwm(1);
			break;

		case CMD_PWM_OFF:
			turn_on_off_pwm(0);
			break;

		case CMD_PWM_SET:
			set_pwm_freq((uint32_t )arg);
			break;
		default:
			printk("error command\n");
			break;
			
	}

	return 0;
}




int mypwm_release(struct inode *inode, struct file *file)
{

	printk("close mypwm device\n");


	return 0;
}


//定义并初始化 file_operations 结构体
struct file_operations  pwm_fops=
{
	.owner = THIS_MODULE,
	.open = mypwm_open,
	.release = mypwm_release,	
	.unlocked_ioctl = mypwm_ioctl,
};




/*
 将 GPIOC14 ---> PWM2的功能(可选功能2)

 Timer2 定时器
 
*/
void InitPwmGpio(void)
{
	uint32_t reg_value = 0;

	reg_value = readl(IO_GPIOC_BASE+GPIO_ALTFN0);
	reg_value &= (~(0x3<<28));
	reg_value |= (0x2<<28);
	writel(reg_value, IO_GPIOC_BASE+GPIO_ALTFN0);
}


/*
  首先我们初始化 PMW信号的计数时钟频率 37.5 KHz

  PRESCALER1 ---> 249
   定时器初值 100

   PWM信号频率 = 375Hz

*/

void InitTimer2(void)
{

	uint32_t reg_value = 0; 

	//TIMER2 计数时钟频率    ---> 1MHz
	// 150 M /150/1 = 1MHz
	
	//prescaler1 ---> 149
	reg_value = readl(MY_PWM_BASE+TCFG0);
	reg_value &= (~(0xff<<8));
	reg_value |= (149<<8);
	writel(reg_value , MY_PWM_BASE+TCFG0);
	
	//div --> 1分频
	reg_value = readl(MY_PWM_BASE+TCFG1);
	reg_value &= (~(0xf<<8));
	reg_value |= (0x0<<8);
	writel(reg_value , MY_PWM_BASE+TCFG1);

	//配置TCON寄存器，autoreload = 1
	reg_value = readl(MY_PWM_BASE+TCON);
	reg_value &= (~(0xf<<12));
	reg_value |= (0x8<<12);
	writel(reg_value , MY_PWM_BASE+TCON);

	    //设置PWM 输出信号取反
	reg_value =  readl(MY_PWM_BASE + TCON);
	reg_value |= (0x1<<14); 
	writel(reg_value,MY_PWM_BASE + TCON);


	/*
		10Hz
	
       x -->HZ

       周期 us ,1000000/x

       
      
	*/
	//定时器初值----> PWM信号的频率 
	writel(1000 , MY_PWM_BASE+TCNTB2);
	writel(500 , MY_PWM_BASE+TCMPB2);

	//更新 TCNTB2 TCMPB2
	reg_value = readl(MY_PWM_BASE+TCON);	
	reg_value |= (0x1<<13);
	writel(reg_value , MY_PWM_BASE+TCON);

	reg_value = readl(MY_PWM_BASE+TCON);	
	reg_value &= (~(0x1<<13));
	writel(reg_value , MY_PWM_BASE+TCON);

	//关闭定时器，PWM2引脚上就会输出 375Hz PWM信号
	
	reg_value = readl(MY_PWM_BASE+TCON);	
	reg_value &= (~(0x1<<12));
	writel(reg_value , MY_PWM_BASE+TCON);

	printk("Init Timer2 OK\n");
		
	
}


/*
 设置频率

 pwm_hz ： 给定的频率，单位 HZ
*/
void set_pwm_freq(uint32_t pwm_hz)
{
	uint32_t tus = 1000000 / pwm_hz;
	uint32_t reg_value = 0; 

	writel(tus , MY_PWM_BASE+TCNTB2);
	writel((tus/2) , MY_PWM_BASE+TCMPB2);

	//更新 TCNTB2 TCMPB2
	reg_value = readl(MY_PWM_BASE+TCON);	
	reg_value |= (0x1<<13);
	writel(reg_value , MY_PWM_BASE+TCON);

	reg_value = readl(MY_PWM_BASE+TCON);	
	reg_value &= (~(0x1<<13));
	writel(reg_value , MY_PWM_BASE+TCON);
	
}


//打开关闭 pwm
void turn_on_off_pwm(int onoff)
{
	uint32_t reg_value = 0; 
	if(onoff)
	{
		reg_value = readl(MY_PWM_BASE+TCON);	
		reg_value |= (0x1<<12);
		writel(reg_value , MY_PWM_BASE+TCON);
	}
	else
	{
		reg_value = readl(MY_PWM_BASE+TCON);	
		reg_value &= (~(0x1<<12));
		writel(reg_value , MY_PWM_BASE+TCON);
	}
}


#define MYPWM_MAJOR   200
#define MYPWM_MINOR   0

int mypwm_probe(struct platform_device *pdev)
{

	struct resource *pwm_res = NULL;
	dev_t mypwm_devno = MKDEV(MYPWM_MAJOR, MYPWM_MINOR);

	if(register_chrdev_region(mypwm_devno,1,"mypwm")< 0)
	{
		printk("register_chrdev_region error\n");
		return 0;
	}

	pwm_res=platform_get_resource(pdev,IORESOURCE_MEM,0);

	 //调用ioremap函数 将GPIOC寄存器的物理地址映射到虚拟地址空间
	IO_GPIOC_BASE = ioremap(pwm_res->start,pwm_res->end-pwm_res->start);
	if(IO_GPIOC_BASE == NULL)
	{
		printk("io remap error\n");
		return 0;
	}

	pwm_res=platform_get_resource(pdev,IORESOURCE_MEM,1);
	MY_PWM_BASE = ioremap(pwm_res->start,pwm_res->end-pwm_res->start);
	if(MY_PWM_BASE == NULL)
	{
		printk("io remap error\n");
		return 0;
	}

	InitPwmGpio();
	InitTimer2();

	pwm_cdev = (struct cdev *)kmalloc(sizeof(struct cdev), GFP_KERNEL);

	cdev_init(pwm_cdev, &pwm_fops);
	pwm_cdev->owner = THIS_MODULE;
   
	cdev_add(pwm_cdev,mypwm_devno,1);


	printk("enter mypwm_probe \n");

	return 0;
}


int mypwm_remove(struct platform_device *pdev)
{
	printk("pwm_remove \n");

	return 0;
}



// 定义平台设备
struct platform_device  mypwm_dev =
{
	.num_resources = ARRAY_SIZE(mypwm_res),
	.resource = mypwm_res,
	.name ="mypwm",
	.id  =-1,
};


struct platform_driver mypwm_drv =
{
	.driver = 
	{
		.name ="mypwm",
		.owner = THIS_MODULE,
	},

	.probe = mypwm_probe,
	.remove = mypwm_remove,
};




//模块初始化函数
int mypwm_init(void)
{

	//向平台总线注册平台设备
	platform_device_register(&mypwm_dev);

	platform_driver_register(&mypwm_drv);


	printk("mypwm_init OK\n");
	return 0;
}



void mypwm_exit(void)  //编写模块退出函数
{

	platform_device_unregister(&mypwm_dev);
	platform_driver_unregister(&mypwm_drv);
	
	printk("mypwm_exit OK\n");
	
}


module_init(mypwm_init);  //指定模块初始化函数
module_exit(mypwm_exit);  //指定模块退出函数

MODULE_LICENSE ("GPL");  //license 声明






