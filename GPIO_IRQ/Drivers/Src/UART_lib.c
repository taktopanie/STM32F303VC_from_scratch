/*
 * UART_lib.c
 *
 *  Created on: Aug 5, 2023
 *      Author: maciej
 */

#include <UART_lib.h>
#include <stm32f3xx.h>

#include<stdio.h>

char BUFFOR [MAX_BUFF];

void UART_PeriClockControl(USART_RegDef_t * USART, uint8_t Clock_State){
	if( Clock_State == ENABLE){
		//turn ON UART clock
		if (USART == USART1){
			RCC->APB2ENR |= (1 << 14);
		}else if (USART == USART2){
			RCC->APB1ENR |= (1 << 17);
		}else if (USART == USART3){
			RCC->APB1ENR |= (1 << 18);
		}else if (USART == UART4){
			RCC->APB1ENR |= (1 << 19);
		}else if (USART == UART5){
			RCC->APB1ENR |= (1 << 20);
		}
	}else if( Clock_State == DISABLE){
		//turn OFF UART clock
		if (USART == USART1){
			RCC->APB2ENR &= ~(1 << 14);
		}else if (USART == USART2){
			RCC->APB1ENR &= ~(1 << 17);
		}else if (USART == USART3){
			RCC->APB1ENR &= ~(1 << 18);
		}else if (USART == UART4){
			RCC->APB1ENR &= ~(1 << 19);
		}else if (USART == UART5){
			RCC->APB1ENR &= ~(1 << 20);
		}
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

		//ENABLE TC IRQ -- TURNED OFF BECAUE MAKE MESS WITH SENDING(TC CLEARED IN WHILE LOOP)
		//UART->USART->USART_CR1 |= (1 << 6);

		//ENABLE THE UART RECEIVER
		UART->USART->USART_CR1 |= (1 << 2);

		//ENABLE THE UART TRANSMITTER
		UART->USART->USART_CR1 |= (1 << 3);

		//WHILE TC FLAG SET NOT SET -- AFTER IDLE FRAME
		while(!(UART->USART->USART_ISR & (1 << 6)));

		//TODO: CAN NOT USE USART1 DIRECTLY////////////////////////////
		//CLEAR THE FLAG
		USART1->USART_ICR |= (1 << 6);

		//USART1_EXTI25 interrupt enable
		*NVIC_ISER1 |= (1 << 5);
///////////////////////////////////////////////////
}

void BUFFOR_flush(char* buf){
	for(int i =0; i < MAX_BUFF; i++){
		if(buf[i]!= 0 ){
			buf[i]=0;
		}else{
			return;
		}
	}
}

void UART_SendChar(USART_RegDef_t * UART, char* sign){
	//WHILE TXE FLAG NOT SET
	while(!(UART->USART_ISR & (1 << 7)));
	UART->USART_TDR = *sign;
}

uint8_t UART_ReceiveChar(USART_RegDef_t * UART){
	static int i = 0;
	BUFFOR[i] = (char)UART->USART_RDR;
	//TODO:function protecting buffor against overflow

	//when receives enter[carriage return] sign print the buffor
	if(BUFFOR[i++] == 0x0A){
		uint8_t tmp = i;
		i = 0;
		return tmp;
	}
	return 0;
}

void UART_ReceiveString(char* buff, uint8_t char_amount){
	for(int p = 0; p < char_amount; p ++){
		buff[p]=BUFFOR[p];
	}
	//flush the BUFFOR
	BUFFOR_flush(BUFFOR);
}

void UART_SendString(USART_RegDef_t * UART,  char* sign, uint8_t number_of_chars){

	//ENABLE TX UART
	if( !(UART->USART_CR1 & (1<<3)) ){
		UART->USART_CR1 |= (1 << 3);
	}

	//ENABLE TC IRQ
	//if( !(UART->USART_CR1 & (1<<6)) ){
	//	UART->USART_CR1 |= (1 << 6);
	//}


	for (int i = 0; i < number_of_chars; i++){
		UART_SendChar(UART, sign++);
	}

	//WHILE TC FLAG SET NOT SET
	while(!(UART->USART_ISR & (1 << 6)));

	//CLEAR THE FLAG
	UART->USART_ICR |= (1 << 6);

	//DISABLE TX UART === affects DMA
	UART->USART_CR1 &= ~(1 << 3);
}

