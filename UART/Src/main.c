/**
 ******************************************************************************
 * @file           : main.c
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
#include<stm32f3xx.h>
#include <GPIO_lib.h>
#include <UART_lib.h>

extern volatile uint8_t IRQ_TC_FLAG;

void UARTGPIOInit(void){
//GPIO_RegDef_t* GPIO = (GPIO_RegDef_t*)GPIOE;

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

void GPIO_FOR_DEBUG(void){
	GPIO_Handle_t GPIO_deb ;

	GPIO_deb.GPIO_Regdef = GPIOA;

	GPIO_deb.GPIO_config.Pin_Mode = GPIO_MODE_OUTPUT;
	GPIO_deb.GPIO_config.Pin_Output_Type = GPIO_PUSH_PULL;
	//PULL UP UART PINS RESOLVE IDLE FRAM ISSUE
	GPIO_deb.GPIO_config.Pin_Pull = GPIO_PULL_DOWN;
	GPIO_deb.GPIO_config.Pin_Speed = GPIO_SPEED_HIGH;
	GPIO_deb.GPIO_config.Pin_Number = GPIO_PIN_8;
	GPIO_Init(&GPIO_deb);
}

int main(void)
{

GPIO_FOR_DEBUG();
UARTGPIOInit();

UART_PeriClockControl(ENABLE);

USART_Handle_t UART_1_handler;
UART_1_handler.USART = USART1;
UART_1_handler.baud = BAUD_RATE_9600;
UART_1_handler.data_bits = DATA_BITS_7;
UART_1_handler.stop_bits = STOP_BITS_1;
UART_Init(&UART_1_handler);

//Transmission complete interrupt enable

//
*NVIC_ISER1 |= (1 << 5);

printf("Hello FROM MAIN\n");
//send string with NULL value at the end(if not needed -1 from sizeof)
UART_SendString(UART_1_handler.USART,"taktopanie", sizeof("taktopanie"));


	/* Loop forever */
	for(;;);

}

void USART1_EXTI25_IRQHandler(){

	//clear the TC IRQ flag
	USART1->USART_ICR |= (1 << 6);
	GPIO_TogglePin(GPIOA, GPIO_PIN_8);


}
