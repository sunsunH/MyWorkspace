

/*

 虚拟磁盘驱动

 块设备驱动
 
*/

#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/genhd.h>
#include <linux/hdreg.h>
#include <linux/fs.h>
#include <linux/blkdev.h>
#include <linux/spinlock.h>
#include <linux/vmalloc.h>


#define HEADS   2  //磁头数目 
#define CYLINDERS   32 //柱面数 4*8
#define SECTTORS    32


struct gendisk *gen_mydisk; //定义表示磁盘的struct gendisk 指针
u8 *mydisk_buf;				//定义磁盘缓冲区
unsigned int mydisk_size; //定义磁盘大小



int sector_size = 512;  //定义扇区大小 512字节
int nsectors = HEADS * CYLINDERS * SECTTORS;  //扇区数 1024

spinlock_t mydisk_lock; //创建请求队列时要用
struct request_queue *mydisk_queue = NULL; //mydisk 块设备的请求队列


static int mydisk_open(struct block_device *bdev, fmode_t mode)
{
	printk("mydisk_open\n");
	return 0;
}

static int  mydisk_release(struct gendisk *gd, fmode_t mode)
{
	printk("mydisk_release\n");

	return 0;
}

static int mydisk_ioctl(struct block_device *bdev, fmode_t mode, unsigned cmd, unsigned long arg)
{
	return 0;
}

//获取磁盘相关信息
static int mydisk_getgeo(struct block_device *bdev, struct hd_geometry *geo)
{
	printk("mydisk_getgeo \n");
	geo->cylinders = 256;
	geo->heads = 4;
	geo->sectors = nsectors;
	geo->start = 0;
	return 0;
}



/*
定义块设备 fops结构体 并初始化
*/
struct block_device_operations mydisk_fops = {
	.owner = THIS_MODULE,
	.open = mydisk_open,
	.release = mydisk_release,
	.ioctl = mydisk_ioctl,
	.getgeo = mydisk_getgeo,
	
};


/*
 	实现底层硬件操作接口函数

	start_sector: 访问的起始扇区号
	nsect_num: 访问扇区个数
 	buffer: 内存的起始地址
 	write：读写标志

*/


void mydisk_transfer(sector_t start_sector,unsigned long nsect_num,
                               char *buffer,int write)
{
	unsigned long offset = start_sector*sector_size;
	unsigned long nbytes = nsect_num*sector_size;

	if(offset+nbytes >= mydisk_size){
		printk("beyond end!\n");
		return;
	}

	/*操作硬件*/
	if(write){
	  //写内存数据到 磁盘
		memcpy(mydisk_buf+offset,buffer,nbytes);
	}
	else{
	 //读磁盘数据到内存
		memcpy(buffer,mydisk_buf+offset,nbytes);
	}
	
}



//请求处理函数,用来处理bio请求
void mydisk_request(struct request_queue *q)
{
   struct request *req = NULL;

   int start_sector = 0;
   int sector_num = 0;
   int write_flag = 0;

   //从请求队列中取出一个请求
   req = blk_fetch_request(q);
   while(req!=NULL)
   {
	   	//处理获取到的请求
		start_sector = blk_rq_pos(req); //获取请求读写的起始扇区
		sector_num = blk_rq_cur_sectors(req);//获取请求读写的扇区数
		write_flag = rq_data_dir(req); //获取请求的读写标志

		mydisk_transfer(start_sector,sector_num,req->buffer, write_flag);
	

	   //处理请求后，结束请求
	   if(!__blk_end_request_cur(req, 0))
	   {
		   //该请求处理完成，取出下一个请求
		   req = blk_fetch_request(q);
	   }

	   //否则继续处理该请求的其他bio
   }
   
}


//模块初始化函数

int mydisk_dev = 0; //定义块设备号

static int __init mydisk_init(void)
{
	//初始化磁盘信息
	mydisk_size = sector_size*nsectors;
	mydisk_buf = vmalloc(mydisk_size);

	// 申请块设备号
	mydisk_dev = register_blkdev(0, "mydisk");

	// 申请gendisk空间，创建表示磁盘的 gendisk 对象gen_mydisk
	gen_mydisk = alloc_disk(1);

	// 设置gendisk内容,初始化 gen_mydisk
	gen_mydisk->major = mydisk_dev;
	gen_mydisk->first_minor = 0;
	gen_mydisk->fops = &mydisk_fops;
	strcpy(gen_mydisk->disk_name,"mydisk");

	//设置容量
	set_capacity(gen_mydisk, nsectors);

	//创建请求队列，初始化请求队列
	spin_lock_init(&mydisk_lock);
	mydisk_queue = blk_init_queue(mydisk_request, &mydisk_lock);

	//将请求队列关联到gendisk,初始化磁盘设备的请求队列
	gen_mydisk->queue = mydisk_queue;

	//添加gendisk到内核,添加磁盘设备到内核
	add_disk(gen_mydisk);

	return 0;
}


//模块退出函数
static void __exit mydisk_exit(void)
{
	del_gendisk(gen_mydisk);

	//将引用计数-1
	put_disk(gen_mydisk);

	blk_cleanup_queue(mydisk_queue); //清除请求队列

	unregister_blkdev(mydisk_dev, "mydisk"); //注销设备号

	vfree(mydisk_buf); //释放磁盘空间
}

module_init(mydisk_init);
module_exit(mydisk_exit);


MODULE_LICENSE ("GPL");



