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
		//TODO
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
		//ENABLE THE UART RECEIVER
		UART->USART->USART_CR1 |= (1 << 2);

		//Transmission complete interrupt enable
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
	UART->USART_CR1 |= (1 << 3);

	UART->USART_CR1 |= (1 << 6);


	for (int i = 0; i < number_of_chars; i++){
		UART_SendChar(UART, sign++);
	}

	//ENABLE TX UART
	UART->USART_CR1 &= ~(1 << 3);
}

/*
 * 1. Write the USART_TDR register address in the DMA control register to configure it as
the destination of the transfer. The data is moved to this address from memory after
each TXE event.
2. Write the memory address in the DMA control register to configure it as the source of
the transfer. The data is loaded into the USART_TDR register from this memory area
after each TXE event.
3. Configure the total number of bytes to be transferred to the DMA control register.
4. Configure the channel priority in the DMA register
5. Configure DMA interrupt generation after half/ full transfer as required by the
application.
6. Clear the TC flag in the USART_ISR register by setting the TCCF bit in the
USART_ICR register.
7. Activate the channel in the DMA register
 */

//TODO: same function for all UART's
void UART1_DMA_WRITE(char* buffor, uint8_t number_of_chars){
//UART1 DMA1 / CHANNEL4
}
