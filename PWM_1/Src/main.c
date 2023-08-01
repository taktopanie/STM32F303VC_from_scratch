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

	// Timer_2 CH2 AF PIN
	GPIOPins.GPIO_Regdef = GPIOA;
	GPIOPins.GPIO_config.Pin_Mode = GPIO_MODE_ALTERNATE;
	GPIOPins.GPIO_config.Pin_Output_Type = GPIO_PUSH_PULL;
	GPIOPins.GPIO_config.Pin_Pull= GPIO_NO_PULL;
	GPIOPins.GPIO_config.Pin_Speed = GPIO_SPEED_HIGH;
	GPIOPins.GPIO_config.Pin_alt_func = AF_1;
	GPIOPins.GPIO_config.Pin_Number = GPIO_PIN_1;
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

	GPIO_WritePort(GPIOE, GPIO_PIN_SET);

}


int main (void){

	//INIT
	printf("Generating PWM started");
	PeriClockControl(GPIOE, CLOCK_ENABLE);
	PeriClockControl(GPIOA, CLOCK_ENABLE);

	GPIOInits();

	Timer_Handle_t timer_2;
	Timer_Handle_t timer_3;
	Timer_Handle_t timer_4;

	////TIMER2////
	timer_2.TIMER = TIMER2;
	//1s duty PWM
	timer_2.TIM_ARR = (1000-1);
	//8 000 000 / 8000 / 1000 =>  1Hz freq
	timer_2.TIM_PRESCALLER = (8000-1);
	timer_2.TIM_COUNTER_mode = COUNTER_MODE_UP;
	timer_2.TIM_PWM_WIDTH_PERCENT = 32;
	timer_2.TIM_PWM_INVERTED_MODE = 1;

	Timer_Init_PWM_MODE(&timer_2);
	TIMER_interrupt_set(timer_2.TIMER);

	////TIMER3////
	timer_3.TIMER = TIMER3;
	//8 000 000 / 8000 / 1000 =>  1s ovf
	timer_3.TIM_ARR = (1000-1);
	timer_3.TIM_PRESCALLER = (8000-1);
	timer_3.TIM_COUNTER_mode = COUNTER_MODE_UP;
	timer_3.TIM_ONEPULSE = 0;
	Timer_Init_FREE_RUN(&timer_3);
	TIMER_interrupt_set(timer_3.TIMER);

	////TIMER4////
	timer_4.TIMER = TIMER4;
	timer_4.TIM_ARR = (100-1);
	timer_4.TIM_PRESCALLER = (8000-1);
	timer_4.TIM_COUNTER_mode = COUNTER_MODE_UP;
	timer_4.TIM_ONEPULSE = 0;
	Timer_Init_FREE_RUN(&timer_4);
	TIMER_interrupt_set(timer_4.TIMER);


	while(1){
	}
	return 0;
}

void TIM3_IRQHandler(){

	static int GPIO_PIN = 8;
	//CLEAN the interrupt FLAG
	Timer_IRQ_handling(TIMER3);


	GPIO_TogglePin(GPIOE, GPIO_PIN++);
	printf("IRQ3\n");
	if(GPIO_PIN==16){
		GPIO_PIN=8;
	}
}
void TIM4_IRQHandler(){
	//CLEAN the interrupt FLAG
	Timer_IRQ_handling(TIMER4);
	printf("IRQ4\n");


}
