/* usart.h */
#ifndef USART_H
#define USART_H

#include <stm32f4xx.h> // common stuff
#include <stm32f4xx_rcc.h> // reset anc clocking
#include <stm32f4xx_gpio.h> // gpio control
#include <stm32f4xx_usart.h> // USART

#define BUFSIZE 16

#define BAUDRATE 115200

void USART1_Init(void); // init USART1 peripheral
void USART1_SendChar(char c); // blocking send character
int USART1_Dequeue(char* c); // pop character from receive FIFO

#endif

