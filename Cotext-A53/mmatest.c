

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>

struct mma8451_data{
	int x;
	int y;
	int z;
};


#define  MMA_DEVICE  		 'C'
#define  CMD_READX  		_IO(MMA_DEVICE,0)  
#define  CMD_READY  		_IO(MMA_DEVICE,1)  
#define  CMD_READZ          _IO(MMA_DEVICE,2)  


int fd;

int main()
{
     char ch = 0;
	struct mma8451_data data;

 	fd = open("/dev/mma",O_RDWR);
	if(fd<0){
		printf("open failed!\n");
		return 0;
	}

	printf("mma open successed!\n");

	while(1)
	{
		ioctl(fd,CMD_READX,&data);
	
		if(data.x>=8192){
			data.x = data.x-16384;
		}
		printf("accel data:x = %d\n",data.x);
		ioctl(fd,CMD_READY,&data);
		if(data.y>=8192){
			data.y = data.y-16384;
		}
		printf("accel data:y = %d\n",data.y);
		ioctl(fd,CMD_READZ,&data);
		if(data.z>=8192){
			data.z = data.z-16384;
		}
		printf("accel data:z = %d\n",data.z);
		
		sleep(1);
	}

	close(fd);
	return 0;
}


