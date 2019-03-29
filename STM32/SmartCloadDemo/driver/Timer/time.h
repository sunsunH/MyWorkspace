#ifndef _TIME_H_
#define _TIME_H_

#include "stm32f0xx.h"


void TIM3_INT_Config(void);
void TIM3_Config(void);

void TIM2_Config(void);

void Delay_us(uint32_t delay_time);


#define  delay_us    Delay_us

#define  delay_ms    Delay_ms



#endif  /* _TIME_H_ */
