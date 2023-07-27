#include <MY_interrupt.h>
#include <stdint.h>
#include<stm32f3xx.h>


void TIMER_interrupt_set(Timer_RegDef* wsk_tim){
	uint32_t * wsk;
	wsk = (uint32_t*)(NVIC_VECT_0);

	//Enable NVIC interrupt
	if(wsk_tim == TIMER2){
		//28 line interrupt TIM2
		*wsk |= (1<< 28);
	}else if(wsk_tim == TIMER3){
		//29 line interrupt TIM3
		*wsk |= (1<< 29);
	}else if(wsk_tim == TIMER4){
		//30 line interrupt TIM4
		*wsk |= (1<< 30);
	}
}

void GPIO_interrupt_set(void){

	uint32_t * wsk;
	//RRC sysclock enable for exti
	wsk = (uint32_t*)(RRC_OFFSET + 0x18UL);
	*wsk |= (1<<0);

	//EXTI rising edge detection
	wsk = (uint32_t*)(EXTI_OFFSET + 0x08UL);
	*wsk |= (1 << 0);

	//Exti interrupt enable
	wsk = (uint32_t*)(EXTI_OFFSET + 0x00UL);
	*wsk |= (1<< 0);

	//Enable NVIC_VECT_0 EXTI0 interrupt
	wsk = (uint32_t*)(NVIC_VECT_0);
	*wsk |= (1<< 6);


}
