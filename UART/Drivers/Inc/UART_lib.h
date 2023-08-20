/*
 * UART_lib.h
 *
 *  Created on: Aug 5, 2023
 *      Author: maciej
 */

#ifndef UART_LIB_H_
#define UART_LIB_H_

#include<stm32f3xx.h>

//@DATABITS
#define DATA_BITS_9						0
#define DATA_BITS_8						1
#define DATA_BITS_7						2

//TODO: REST OF BAUDRATES
//@BAUDRATES
#define BAUD_RATE_9600					0x341

//@STOPBITS
#define STOP_BITS_1						0
#define STOP_BITS_0_5					1
#define STOP_BITS_2						2
#define STOP_BITS_1_5					3

#define MAX_BUFF 200


typedef struct{
	USART_RegDef_t* USART;
	uint8_t data_bits;					// see @DATABITS
	uint32_t baud;						// see @BAUDRATES
	uint8_t stop_bits;					// see @STOPBITS

}USART_Handle_t;

void UART_PeriClockControl(USART_RegDef_t * USART, uint8_t Clock_State);

void UART_Init(USART_Handle_t* UART);

void BUFFOR_flush(char* buf);

void UART_SendChar(USART_RegDef_t * UART, char* sign);
uint8_t  UART_ReceiveChar(USART_RegDef_t * UART);
void UART_ReceiveString(char* buff, uint8_t char_amount);

void UART_SendString(USART_RegDef_t * UART,  char* sign, uint8_t number_of_chars);

void UART1_DMA_WRITE(void);

#endif /* UART_LIB_H_ */
