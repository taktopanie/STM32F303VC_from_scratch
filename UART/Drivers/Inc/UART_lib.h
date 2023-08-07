/*
 * UART_lib.h
 *
 *  Created on: Aug 5, 2023
 *      Author: maciej
 */

#ifndef UART_LIB_H_
#define UART_LIB_H_

#include<stm32f3xx.h>

typedef struct{
	USART_RegDef_t UART;
	//uint16_t TIM_PRESCALLER;

}USART_Handle_t;

void UART_PeriClockControl(uint8_t Clock_State);

void UART_Init(void);

void UART_SendChar(char* sign);
void UART_SendString(char* sign, uint8_t number_of_chars);

#endif /* UART_LIB_H_ */
