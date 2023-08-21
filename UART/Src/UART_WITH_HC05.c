/**
 ******************************************************************************
 * @file           : UART_WITH_HC05.c
 * @author         : Auto-generated by STM32CubeIDE
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2023 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */

#include <stdint.h>
#include <stdio.h>
#include <stm32f3xx.h>
#include <GPIO_lib.h>
#include <UART_lib.h>
#include <string.h>

#define DEBUGING_PRINTS 0

//BUFFOR to receive the message throught UART
char buff [MAX_BUFF];

//variable which is used to count the number of char received throiught UART
uint8_t tmp = 0;

uint8_t BLUETOOTH_STATUS = 0;

void UARTGPIOInit(void){

PeriClockControl(GPIOA, CLOCK_ENABLE);

GPIO_Handle_t GPIO_Pins ;

GPIO_Pins.GPIO_Regdef = GPIOA;
GPIO_Pins.GPIO_config.Pin_Mode = GPIO_MODE_ALTERNATE;
GPIO_Pins.GPIO_config.Pin_Output_Type = GPIO_PUSH_PULL;
//PULL UP UART PINS RESOLVE IDLE FRAM ISSUE
GPIO_Pins.GPIO_config.Pin_Pull = GPIO_PULL_UP;
GPIO_Pins.GPIO_config.Pin_Speed = GPIO_SPEED_HIGH;
GPIO_Pins.GPIO_config.Pin_alt_func = AF_7;

GPIO_Pins.GPIO_config.Pin_Number = GPIO_PIN_9;
GPIO_Init(&GPIO_Pins);

GPIO_Pins.GPIO_config.Pin_Number = GPIO_PIN_10;
GPIO_Init(&GPIO_Pins);

}

void UARTInit(USART_Handle_t* UART_1_handler){
	UART_PeriClockControl(USART1, ENABLE);
	UART_1_handler->USART = USART1;
	UART_1_handler->baud = BAUD_RATE_9600;
	UART_1_handler->data_bits = DATA_BITS_7;
	UART_1_handler->stop_bits = STOP_BITS_1;
	UART_Init(UART_1_handler);
}

void LED_init(){
	PeriClockControl(GPIOE, CLOCK_ENABLE);
	GPIO_Handle_t GPIO_T;
	GPIO_T.GPIO_Regdef = GPIOE;
	GPIO_T.GPIO_config.Pin_Mode = GPIO_MODE_OUTPUT;
	GPIO_T.GPIO_config.Pin_Output_Type = GPIO_PUSH_PULL;
	GPIO_T.GPIO_config.Pin_Pull = GPIO_PULL_DOWN;
	GPIO_T.GPIO_config.Pin_Speed = GPIO_SPEED_HIGH;

	GPIO_T.GPIO_config.Pin_Number = GPIO_PIN_15;
	GPIO_Init(&GPIO_T);
	GPIO_T.GPIO_config.Pin_Number = GPIO_PIN_14;
	GPIO_Init(&GPIO_T);
}

void Blue_Pin_en(){
	PeriClockControl(GPIOD, CLOCK_ENABLE);
	GPIO_Handle_t GPIO_Pins ;

	GPIO_Pins.GPIO_Regdef = GPIOD;
	GPIO_Pins.GPIO_config.Pin_Mode = GPIO_MODE_INPUT;
	GPIO_Pins.GPIO_config.Pin_Output_Type = GPIO_PUSH_PULL;
	GPIO_Pins.GPIO_config.Pin_Pull = GPIO_PULL_DOWN;
	GPIO_Pins.GPIO_config.Pin_Speed = GPIO_SPEED_HIGH;
	GPIO_Pins.GPIO_config.Pin_Number = GPIO_PIN_1;
	GPIO_Init(&GPIO_Pins);

	GPIO_interrupt_set(EDGE_BOTH, GPIO_PIN_1);
	GPIO_EXTI_PortMap(EXTI_1, GPIOD);
	GPIO_IRQITConfig(IRQ_NO_EXTI1, ENABLE);
}

int main(void)
{
	//TODO POWERSAFE MODE IN IDLE
	if(DEBUGING_PRINTS)
		printf("Program in MAIN function.\n");

	USART_Handle_t UART_1_handler;

	UARTGPIOInit();

	UARTInit(&UART_1_handler);

	LED_init();

	Blue_Pin_en();

	//While bluetooth is not connected
	while(!BLUETOOTH_STATUS);

	char WELCOME_TEXT [] = "Microcontroler STM32F303VC\r\nReady to work...\r\nTurning on the LED's\r\nD[n]_[ON/OFF] -- where n=led nr[1-2]\r\n";
	//send string with NULL value at the end(if not needed -1 from sizeof)

	//TODO: SENDING STRING CALLS EXTI1_IRQHandler
	UART_SendString(UART_1_handler.USART,WELCOME_TEXT, (sizeof(WELCOME_TEXT)-1));

	/* Loop forever */
	for(;;){


	}

}

void __making_the_decision(char* bfr){
	if(!strcmp(buff,"D1_ON")){
		if(DEBUGING_PRINTS)
			printf("TUNR ON DIODE 1\n");
		UART_SendString(USART1,"TUNR ON DIODE 1\n", (sizeof("TUNR ON DIODE 1")));
		GPIO_WritePin(GPIOE, GPIO_PIN_15, GPIO_PIN_SET);
	}
	if(!strcmp(buff,"D1_OFF")){
		if(DEBUGING_PRINTS)
			printf("TUNR OFF DIODE 1\n");
		UART_SendString(USART1,"TUNR OFF DIODE 1\n", (sizeof("TUNR OFF DIODE 1")));
		GPIO_WritePin(GPIOE, GPIO_PIN_15, GPIO_PIN_RESET);
	}
	if(!strcmp(buff,"D2_ON")){
		if(DEBUGING_PRINTS)
			printf("TUNR ON DIODE 2\n");
		UART_SendString(USART1,"TUNR ON DIODE 2\n", (sizeof("TUNR ON DIODE 2")));
		GPIO_WritePin(GPIOE, GPIO_PIN_14, GPIO_PIN_SET);
	}
	if(!strcmp(buff,"D2_OFF")){
		if(DEBUGING_PRINTS)
			printf("TUNR OFF DIODE 2\n");
		UART_SendString(USART1,"TUNR OFF DIODE 2\n", (sizeof("TUNR OFF DIODE 2")));
		GPIO_WritePin(GPIOE, GPIO_PIN_14, GPIO_PIN_RESET);
	}
}

void USART1_EXTI25_IRQHandler(){

	// TRANSMIT COMPLETE IRQ
	if(USART1->USART_ISR & (1 << 6)){

		if(DEBUGING_PRINTS)
			printf("TC IRQ\n");

		//clear the TC IRQ flag
		USART1->USART_ICR |= (1 << 6);
	}

	// READ DATA REGISTER NOT EMPTY IRQ
	if(USART1->USART_ISR & (1 << 5)){

		if(DEBUGING_PRINTS)
			printf("RXNE IRQ\n");

		//clear the TC IRQ flag
		USART1->USART_ICR |= (1 << 5);
		tmp = UART_ReceiveChar(USART1);
		if(tmp){
			//RECEIVE buff -2 because of the bluetooth suffixes <CR><LF>
			UART_ReceiveString(buff, tmp-2);

			__making_the_decision(buff);

			//flush the buffor
			BUFFOR_flush(buff);
		}

	}

}

void EXTI1_IRQHandler(){
	//IF PIN8 == high
	if(EXTI->PR1 & (1 << 1)){
	if(GPIOD->IDR & (1 << 1)){
		printf("Bluetooth connected\n");
		GPIO_TogglePin(GPIOE, GPIO_PIN_15);
		BLUETOOTH_STATUS = 1;
	}else if(!(GPIOD->IDR & (1 << 1))){
		printf("Bluetooth disconnected\n");
		BLUETOOTH_STATUS = 0;
	}
	GPIO_IRQHandling(GPIO_PIN_1);
	}
}
