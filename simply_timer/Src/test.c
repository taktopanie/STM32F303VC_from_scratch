#include <stdio.h>
#include <GPIO_lib.h>
#include <string.h>
#include <stdlib.h>

#include<timer_lib.h>
#include<MY_interrupt.h>

void GPIOInits(void){
	GPIO_Handle_t GPIOPins;

	GPIOPins.GPIO_Regdef = GPIOE;
	GPIOPins.GPIO_config.Pin_Mode = GPIO_MODE_OUTPUT;
	GPIOPins.GPIO_config.Pin_Output_Type = GPIO_PUSH_PULL;
	GPIOPins.GPIO_config.Pin_Pull= GPIO_PULL_DOWN;
	GPIOPins.GPIO_config.Pin_Speed = GPIO_SPEED_HIGH;

	//NSS
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
	printf("HELLO WORLD \n");
	GPIOInits();
	Timer2_Init();

	TIMER2_interrupt_set();


	//Timer_RegDef *wsk_TIM = (Timer_RegDef*)0x40000000UL;

	while(1){
		//printf("%ld\n", wsk_TIM->TIMx_CNT);
	}
	return 0;
}

void TIM2_IRQHandler(void){
//Reset timer flag
Timer_RegDef *wsk_TIM = (Timer_RegDef*)0x40000000UL;
wsk_TIM->TIMx_SR &= ~(1<<0);
static int zmienna = 8;

GPIO_TogglePin(GPIOE, zmienna++);
if(zmienna == 16){
	zmienna = 8;
	}

}
