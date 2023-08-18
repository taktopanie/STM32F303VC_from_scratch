/*
 * UART_lib.c
 *
 *  Created on: Aug 5, 2023
 *      Author: maciej
 */

#include <UART_lib.h>
#include <stm32f3xx.h>

#include<stdio.h>

char BUFFOR [200];

void UART_PeriClockControl(uint8_t Clock_State){
	if( Clock_State == ENABLE){
		//turn on UART clock
		RCC->APB2ENR |= (1 << 14);
		}else{
		//MAYBE IN THE FUTURE - not in sample project
	}
}


void UART_Init(USART_Handle_t* UART){

	//1. Program the M bits in USART_CR1 to define the word length.
	//M[1:0] = 00: 1 Start bit, 8 data bits, n stop bits
		UART->USART->USART_CR1 |= ( ( (UART->data_bits & 0x2) << 28) | ( (UART->data_bits & 0x1) << 12));

	//2. Select the desired baud rate using the USART_BRR register.
		// BRR = SYSCLK/BAUD = 8000000/9600 = 833 =>0x341
		UART->USART->USART_BRR &= ~(0xFFFFFFFF);
		UART->USART->USART_BRR = UART->baud;
	//3. Program the number of stop bits in USART_CR2. 1 stopbit
		UART->USART->USART_CR2 &= ~(0x3 << 12);
		UART->USART->USART_CR2 |= (UART->stop_bits << 12);
	//4. Enable the USART by writing the UE bit in USART_CR1 register to 1.
		//TURN ON UART
		UART->USART->USART_CR1 |= (1 << 0);

		//ENABLE RXNE IRQ
		UART->USART->USART_CR1 |= (1 << 5);

		//ENABLE TC IRQ
		UART->USART->USART_CR1 |= (1 << 6);

		//ENABLE THE UART RECEIVER
		UART->USART->USART_CR1 |= (1 << 2);

		//ENABLE THE UART TRANSMITTER
		UART->USART->USART_CR1 |= (1 << 3);

		//USART1_EXTI25 interrupt enable
		*NVIC_ISER1 |= (1 << 5);

}

void UART_SendChar(USART_RegDef_t * UART, char* sign){
	while(!(UART->USART_ISR & (1 << 7)));
	UART->USART_TDR = *sign;
}

void UART_ReceiveChar(USART_RegDef_t * UART){
	static int i = 0;
	BUFFOR[i] = (char)UART->USART_RDR;
	//when receives enter[carriage return] sign print the buffor
	if(BUFFOR[i++] == 0x0D){
		printf("%s\n", BUFFOR);

		//flush the BUFFOR
		for(int p = 0; p < i; p ++){
			BUFFOR[p] = 0;
		}

		i = 0;
	}
}

void UART_SendString(USART_RegDef_t * UART,  char* sign, uint8_t number_of_chars){

	//ENABLE TX UART
	if( !(UART->USART_CR1 & (1<<3)) ){
		UART->USART_CR1 |= (1 << 3);
	}

	//ENABLE TC IRQ
	if( !(UART->USART_CR1 & (1<<6)) ){
		UART->USART_CR1 |= (1 << 6);
	}


	for (int i = 0; i < number_of_chars; i++){
		UART_SendChar(UART, sign++);
	}

	//DISABLE TX UART === affects DMA
	//UART->USART_CR1 &= ~(1 << 3);
}

