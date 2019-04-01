

/*
 最简单的 平台设备总线驱动
*/

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/uaccess.h>
#include <linux/string.h>

#include <linux/platform_device.h>


int gmem_probe(struct platform_device *pdev)
{
	printk("enter gmem_probe \n");

	return 0;
}


int gmem_remove(struct platform_device *pdev)
{
	printk("gmem_remove \n");

	return 0;
}



// 定义平台设备
struct platform_device  gmem_dev =
{
	.name ="gmem",
	.id  =-1,
};


struct platform_driver gmem_drv =
{
	.driver = 
	{
		.name ="gmem",
		.owner = THIS_MODULE,
	},

	.probe = gmem_probe,
	.remove = gmem_remove,
};




//模块初始化函数
int gmem_init(void)
{
	//向平台总线注册平台设备
	platform_device_register(&gmem_dev);

	platform_driver_register(&gmem_drv);


	printk("gmem_init OK\n");
	return 0;
}



void gmem_exit(void)  //编写模块退出函数
{
	printk("gmem_exit OK\n");
}


module_init(gmem_init);  //指定模块初始化函数
module_exit(gmem_exit);  //指定模块退出函数

MODULE_LICENSE ("GPL");  //license 声明



