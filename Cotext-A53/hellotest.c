
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <string.h>
#include <poll.h>
#include <signal.h>



unsigned char buf[100]={0};

/*

./hellotest w  "写的内容"
./hellotest r
./hellotest ledon
./hellotest ledoff

 
*/


#define  HELLO_DEVICE  		 'A'
#define  CMD_LED_ON  		_IO(HELLO_DEVICE,0)  //打开LED灯命令
#define  CMD_LED_OFF 		_IO(HELLO_DEVICE,1)  //关闭LED灯命令


int rw_len = 0;
int fd_hello=0;


//SIG IO信号处理函数
void hello_sig_handler(int signum, siginfo_t *siginfo, void *act)
{	   
 
   if(signum == SIGIO)
   {
   		//printf("enter hello_sig_handler :%d\n", signum);

   		//printf("si_band:%x %x %x\n", siginfo->si_band,POLLIN,POLLOUT );
   
	   if(siginfo->si_band & POLLIN) //在ubuntu16.04版本上无法识别该标志
	   {
		   //表示有数据可读，读这个设备

		    rw_len = read(fd_hello,buf,50);
			printf("SIGIIO read len:%d buf:%s\n",rw_len, buf);

		   
	   }
	   if(siginfo->si_band & POLLOUT)
	   {
		   //表示该设备可写

	   }
	   
   }
}



int main(int argc, char *argv[])
{

	fd_hello = open("/dev/hello",O_RDWR);
	if(fd_hello < 0)
	{
		perror("open file error\n");
	}


	#if 0
	int flag = 0;
	//设置 fd_hello 为非阻塞访问
	flag = fcntl(fd_hello,F_GETFL,0);
	flag |= O_NONBLOCK;
	fcntl(fd_hello,F_SETFL,flag);
	#endif


	if(strcmp(argv[1],"r") == 0)
	{

		struct pollfd fds[1]; 

		fds[0].fd = fd_hello;
		fds[0].events = POLLIN;
		fds[0].revents = 0; //输出参数

		poll(fds, 1,-1); //轮询设备

		if(fds[0].revents & POLLIN)
		{
			rw_len = read(fd_hello,buf,50);
			printf("read len:%d buf:%s\n",rw_len, buf);
		}

	}
	else if(strcmp(argv[1],"w") == 0)
	{
		memset(buf,0,100);
		strcpy(buf,argv[2]);
		rw_len = write(fd_hello,buf,strlen(buf));
		
	}
	else if(strcmp(argv[1],"ledon") == 0)
	{
		ioctl(fd_hello, CMD_LED_ON,0);
	}
	else if(strcmp(argv[1],"ledoff") == 0)
	{
		ioctl(fd_hello, CMD_LED_OFF,0);
	}

	else if(strcmp(argv[1],"fa") == 0)
	{
		//测试异步通知
		
	//初始化SIGIO信号的处理结构体，并设置SIGIO信号的处理
	   struct sigaction act;
	   struct sigaction oldact;
	  
	   
	   memset(&act,0, sizeof(struct sigaction));
	   memset(&oldact,0, sizeof(struct sigaction));
	
	   act.sa_flags = SA_SIGINFO; //设置信号可以传递参数到信号处理函数中
	   act.sa_sigaction = hello_sig_handler;
	
	   sigaction(SIGIO, &act,&oldact); // 安装信号处理函数
	
	   //设置文件的拥有者为当前进程，目的是使驱动程序根据打开的文件file结构，
							   //能找到对应的进程，从而向该进程发送信号
	   fcntl(fd_hello, F_SETOWN, getpid());
	   fcntl(fd_hello, F_SETSIG, SIGIO);   //设置 标志输入输出 的信号
	   
	   int flag = 0; //设置文件的FASYNC标志，启动异步通知机制
	   flag = fcntl(fd_hello, F_GETFL);
	   fcntl(fd_hello, F_SETFL, flag|FASYNC);

	   while(1);
	}

	

	close(fd_hello);

	return 0;
}

