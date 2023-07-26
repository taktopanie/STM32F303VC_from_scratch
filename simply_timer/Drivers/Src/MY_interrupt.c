#include <MY_interrupt.h>
#include <stdint.h>

#include<stm32f3xx.h>

void TIMER2_interrupt_set(void){
	uint32_t * wsk;

	//28 line interrupt TIM2
	wsk = (uint32_t*)(0xE000E100);
	*wsk |= (1<< 28);

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

	//Enable NVIC EXTI0 interrupt
	wsk = (uint32_t*)(0xE000E100);
	*wsk |= (1<< 6);


}
