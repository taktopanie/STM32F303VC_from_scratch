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

#endif /* UART_LIB_H_ */
