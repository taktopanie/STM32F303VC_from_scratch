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

#include <stdio.h>
#include <GPIO_lib.h>
#include <string.h>
#include <stdlib.h>

#include<TIMER_lib.h>
#include<MY_interrupt.h>

#include<DMA_lib.h>

uint32_t zmienna;

void GPIOInits(void){
	GPIO_Handle_t GPIOPins;

	//PUSH_BUTTON
	GPIOPins.GPIO_Regdef = GPIOA;
	GPIOPins.GPIO_config.Pin_Mode = GPIO_MODE_ALTERNATE;
	GPIOPins.GPIO_config.Pin_Output_Type = GPIO_PUSH_PULL;
	GPIOPins.GPIO_config.Pin_Pull= GPIO_NO_PULL;
	GPIOPins.GPIO_config.Pin_Speed = GPIO_SPEED_HIGH;
	GPIOPins.GPIO_config.Pin_alt_func = AF_1;
	GPIOPins.GPIO_config.Pin_Number = GPIO_PIN_0;
	GPIO_Init(&GPIOPins);


	GPIOPins.GPIO_Regdef = GPIOE;
	GPIOPins.GPIO_config.Pin_Mode = GPIO_MODE_OUTPUT;
	GPIOPins.GPIO_config.Pin_Output_Type = GPIO_PUSH_PULL;
	GPIOPins.GPIO_config.Pin_Pull= GPIO_PULL_DOWN;
	GPIOPins.GPIO_config.Pin_Speed = GPIO_SPEED_HIGH;

	//STM32_LEDS
	GPIOPins.GPIO_config.Pin_Number = GPIO_PIN_8;
	GPIO_Init(&GPIOPins);
	GPIOPins.GPIO_config.Pin_Number = GPIO_PIN_9;
	GPIO_Init(&GPIOPins);
	GPIOPins.GPIO_config.Pin_Number = GPIO_PIN_10;
	GPIO_Init(&GPIOPins);
	GPIOPins.GPIO_config.Pin_Number = GPIO_PIN_11;
	GPIO_Init(&GPIOPins);
	GPIOPins.GPIO_config.Pin_Number = GPIO_PIN_12;
	GPIO_Init(&GPIOPins);
	GPIOPins.GPIO_config.Pin_Number = GPIO_PIN_13;
	GPIO_Init(&GPIOPins);
	GPIOPins.GPIO_config.Pin_Number = GPIO_PIN_14;
	GPIO_Init(&GPIOPins);
	GPIOPins.GPIO_config.Pin_Number = GPIO_PIN_15;
	GPIO_Init(&GPIOPins);

}


int main (void){

	//INIT
	PeriClockControl(GPIOE, CLOCK_ENABLE);
	PeriClockControl(GPIOA, CLOCK_ENABLE);


	GPIOInits();

	Timer_Handle_t timer_2;
	DMA_Handle_t DMA_st;

	////TIMER2////
	timer_2.TIM_ARR = 0xFFFFFFFFUL;
	//0.1 ms precision
	timer_2.TIM_PRESCALLER = 8000-1;
	timer_2.TIMER = TIMER2;
	timer_2.TIM_COUNTER_mode = COUNTER_MODE_UP;
	timer_2.TIM_EDGE_TRIGGER = TIM_EDGE_RISING;
	timer_2.TIM_INT_PRSC = TIM_INTERRUPT_1_EVENT;
	timer_2.TIM_FILTERING = TIM_FILTERING_NO;

	Timer_Init_INPUT_CC_MODE(&timer_2);
	TIMER_interrupt_set(timer_2.TIMER);

	//turn on DMA clock
	DMAClockControl(DMA_NUM_1, CLOCK_ENABLE);

	//bufor danych
	uint32_t zmienna = 0;

	DMA_st.DMA_NUMBER = DMA_NUM_1;
	DMA_st.CHANNEL_NUMBER = 5;
	DMA_st.SOURCE_ADDRESS = TIM_2_BASEADDR;
	DMA_st.DESTINATION_ADDRESS = (uint32_t)&zmienna;
	DMA_st.NUMBER_OF_DATA_TRANSFER = 1;
	DMA_st.PRIORITY = DMA_PRIORITY_HIGH;
	DMA_st.M2M_MODE = 0;
	DMA_st.MEM_SIZE = DMA_MEM_SIZE_32_BIT;
	DMA_st.PERI_SIZE = DMA_MEM_SIZE_32_BIT;
	DMA_st.MEMORY_INCREMENT_MODE = 0;
	DMA_st.PERIPH_INCREMENT_MODE = 0;
	DMA_st.CIRCULAR_MODE = 1;
	DMA_st.DATA_TRANSFER_DIRECTION = DMA_READ_FROM_PERIPH;

	//set the DMA intererupt
	DMA_interrupt_set(DMA_NUM_1, DMA_CHANNEL_5);

	DMA_Init(&DMA_st);


	while(1){
	}
	return 0;
}

void DMA1_CH5_IRQHandler(){
	printf("HELLO FROM DMA1 CH5\n");

	//TODO Function clearing flags
	//CLEAR FLAGS
	DMA_RegDef_t* DMA_handler = (DMA_RegDef_t*)0x40020000;
	DMA_handler->DMA_IFCR |= (7<<16);
}

void TIM2_IRQHandler(){
	Timer_indicate_time(TIMER2);

}