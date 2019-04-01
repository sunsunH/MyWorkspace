

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>


/*

 pwmtest  set 1000
 pwmtest on
 pwmtest off
 
*/

#define  PWM_DEVICE   'B'
#define  CMD_PWM_ON  		_IO(PWM_DEVICE,0)  //打开pwm
#define  CMD_PWM_OFF 		_IO(PWM_DEVICE,1)  //关闭pwm
#define  CMD_PWM_SET        _IO(PWM_DEVICE,2)  //设置PWM频率



int main(int argc, char *argv[])
{
	
   int fd_pwm = 0;

   int freq_value = 0;
   
   fd_pwm = open("/dev/mypwm",O_RDWR);

   if(fd_pwm<0){
	   printf("open failed!\n");
	   return 0;
   }

   if(strcmp(argv[1],"on") == 0)
   {
	   ioctl(fd_pwm,CMD_PWM_ON,0);
   }
   else if(strcmp(argv[1],"off") == 0) 
   {
	 ioctl(fd_pwm,CMD_PWM_OFF,0);
   }
   else if(strcmp(argv[1],"set") == 0) 
   {
	 freq_value = atoi(argv[2]);
	 ioctl(fd_pwm,CMD_PWM_SET, (unsigned long)freq_value);
   }

   close(fd_pwm);
	
}
