#ifndef __UART_H
#define	__UART_H

#include "stm32f0xx.h"
#include <stdio.h>


void USART_Configuration(void);
int fputc(int ch, FILE *f);
void UART_send_byte(uint8_t byte);
void UART_Send(uint8_t *Buffer, uint32_t Length);
uint8_t UART_Recive(void);

//´®¿Ú2º¯Êý
void USART2_Configuration(void);
uint8_t UART2_Recive(void);
void USART2_IRQHandler(void);

void UART2_send_byte(uint8_t byte);
void UART2_Send(uint8_t *Buffer, uint32_t Length);





#endif /* __UART_H */
