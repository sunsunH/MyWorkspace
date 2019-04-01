

/*
 i2c 设备驱动 mma8451
*/


#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/io.h>
#include <linux/device.h>
#include <asm/uaccess.h>
#include <linux/i2c.h>



struct i2c_client *mma_client=NULL;


//mma8451 芯片内部寄存器的定义
#define XYZ_STATUS 		0x0
#define OUT_X_MSB		0x1
#define OUT_X_LSB 		0x2
#define OUT_Y_MSB 		0x3
#define OUT_Y_LSB 		0x4
#define OUT_Z_MSB 		0x5
#define OUT_Z_LSB 		0x6
#define WHO_AM_I 		0x0d
#define XYZ_DATA_CFG 	0x0e
#define MMA8451Q_ID 	0x1a
#define CTRL_REG1 		0x2a
#define CTRL_REG2 		0x2b


/*

读mma8451 内部寄存器的函数,返回寄存器的值

第一个参数: client --> 内核里面用来代表i2c 设备

reg -->mma8451芯片内部 寄存器的地址

返回值: 返回读到的寄存器的值

*/

static int mma8451_read_byte(struct i2c_client *client,uint8_t reg)
{

	//调用i2c总线驱动 来读写寄存器
	int result = 0;

	char txbuf[1] = {reg};
	char rxbuf[1] = {0};

	struct i2c_msg msg[2] = {
		{client->addr,0,1,txbuf},
		{client->addr,I2C_M_RD,1,rxbuf}
	};	

	result = i2c_transfer(client->adapter,msg, 2);
	if(result !=2)
	{
		printk(" i2c_transfer error\n");

		return 0;
	}
	
	return rxbuf[0];  //返回读取的结果
		
}


/*

功能：往 mma8451 的指定寄存器 写一个值 

reg： 要写的寄存器

value: 要写的值

成功返回 0，失败返回 -1


*/


static int mma8451_write_byte(struct i2c_client *client,uint8_t reg, uint8_t value)
{

	int result = 0;

	char txbuf[2] = {reg,value};

	struct i2c_msg msg[1] = {
		{client->addr,0,2,txbuf},
		
	};	

	result = i2c_transfer(client->adapter,msg, 1);
	if(result !=1)
	{
		printk(" i2c_transfer error\n");

		return -1;
	}
	
	return 0;  //返回读取的结果

}

/*
	初始化 mma8451
*/
void init_mma8451(void)
{
	//设置mma8451 量程为 8g
	mma8451_write_byte(mma_client,XYZ_DATA_CFG,0x2);

	//设置mma8451 active
	mma8451_write_byte(mma_client,CTRL_REG1,0x1);

	//设置mma8451 high resolution
	mma8451_write_byte(mma_client,CTRL_REG2,0x2);
}



/*
 实现 文件访问接口
*/


int mymma_open(struct inode *inode, struct file *filp)
{
	printk("enter %s\n",  __func__);

	return 0;
}


int mymma_release(struct inode *inode, struct file *filp)
{
	printk("enter %s\n",__func__);

	return 0;
}


//用来保存3个方向的加速度，也就是mma8451 传感器的数据
struct mma8451_data
{
	int x;
	int y;
	int z;
};


#define  MMA_DEVICE  		 'C'
#define  CMD_READX  		_IO(MMA_DEVICE,0)  
#define  CMD_READY  		_IO(MMA_DEVICE,1)  
#define  CMD_READZ          _IO(MMA_DEVICE,2)  


long mymma_ioctl(struct file *filp, unsigned int cmd, unsigned long arg)
{
	struct mma8451_data data;

	int status = mma8451_read_byte(mma_client,XYZ_STATUS);

	memset(&data, 0,sizeof(struct mma8451_data));

	switch(cmd){
		case CMD_READX:
			//有新的有效数据才读
			if((status&0x1)||(status&(0x1<<3))){
				data.x = mma8451_read_byte(mma_client,OUT_X_MSB)<<6;
				data.x |= mma8451_read_byte(mma_client,OUT_X_LSB)>>2;
			}
			break;
		case CMD_READY:
			if((status&0x2)||(status&(0x1<<3))){
				data.y = mma8451_read_byte(mma_client,OUT_Y_MSB)<<6;
				data.y |= mma8451_read_byte(mma_client,OUT_Y_LSB)>>2;
			}
			break;
		case CMD_READZ:
			if((status&0x4)||(status&(0x1<<3))){
				data.z = mma8451_read_byte(mma_client,OUT_Z_MSB)<<6;
				data.z |= mma8451_read_byte(mma_client,OUT_Z_LSB)>>2;
			}
			break;
		default:
			printk("invailed arg!\n");
			return -EINVAL;
	}

	if(copy_to_user((void *)arg, &data, sizeof(struct mma8451_data))){
		printk("copy_to_user failed!\n");
		return -EFAULT;
	}

	return 0;
}



struct file_operations mymma_fops = {
	.owner = THIS_MODULE,
	.open = mymma_open,
	.unlocked_ioctl = mymma_ioctl,
	.release = mymma_release,
};


static struct i2c_device_id mma8451q_id[] = 
{
	 {"mymma8451"},	//i2c设备名，与i2c_board_info中的type成员保持一致
	 {} 			//用于I2C设备和设备驱动匹配
};



struct cdev mymma_cdev;

int  mymma_probe(struct i2c_client *client, const struct i2c_device_id *id)
{
	int result = 0;
	dev_t mma_dev = 0; //mma设备号

    struct class  *mma_class = NULL;
    struct device *mma_device = NULL;
	
	mma_client = client;


	init_mma8451();


	// 1.申请设备号
	result = alloc_chrdev_region(&mma_dev, 0, 1, "mymma");
	if(result<0){
		printk("alloc_chrdev_region faimma!\n");
		return 0;
	}

	printk("mma devno:%d\n", mma_dev);


	cdev_init(&mymma_cdev, &mymma_fops);
	mymma_cdev.owner = THIS_MODULE;
	result = cdev_add(&mymma_cdev, mma_dev, 1);
	if(result<0){
		printk("cdev_add faimma!\n");
		return 0;
	}


	// 3.创建设备类
	mma_class = class_create(THIS_MODULE, "mma_class");
	if(IS_ERR(mma_class)){
		result = PTR_ERR(mma_class);
		return 0;
	}

	// 4.创建设备文件
	mma_device = device_create(mma_class, NULL, mma_dev, NULL, "mma");
	if(IS_ERR(mma_device)){
		result = PTR_ERR(mma_device);
		return 0;
	}
	
	


	printk("enter mymma_probe\n");

	return 0;
}


int mymma_remove(struct i2c_client *client)
{
	printk("enter mymma_remove\n");

	return 0;
}


/*
	定义表示i2c 设备驱动的结构体 i2c_driver
*/
struct i2c_driver mymma8451_drv =
{
	.driver = {
				.name = "mymma8451",    //i2c设备名，与i2c_board_info中的type成员保持一致
				.owner = THIS_MODULE,  //用于I2C设备和设备驱动匹配
			  },

	.probe = mymma_probe,
	.remove = mymma_remove,
	.id_table = mma8451q_id,
};



//模块初始化函数
int mymma_init(void)
{
	int result = 0;

	result = i2c_add_driver(&mymma8451_drv);
	if(result < 0)
	{
		printk("i2c_add_driver error\n");
		return 0;
	}
	
	printk("mymma_init  OK\n");
	return 0;
}


void mymma_exit(void)  //编写模块退出函数
{
	
	printk("mymma_exit OK\n");
	
}


module_init(mymma_init);  //指定模块初始化函数
module_exit(mymma_exit);  //指定模块退出函数

MODULE_LICENSE ("GPL");  //license 声明


