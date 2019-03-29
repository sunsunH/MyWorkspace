#include "SysTick.h"

static __IO uint32_t TimingDelay;

void Delay_ms(__IO uint32_t nTime)
{ 
  TimingDelay = nTime;

  while(TimingDelay != 0);
}


void TimingDelay_Decrement(void)
{
  if (TimingDelay != 0x00)
  { 
    TimingDelay--;
  }
}

void Systick_Init(void)
{
	if (SysTick_Config(SystemCoreClock / 1000))//1∫¡√Î
	{ 
		while (1);
	}
}
