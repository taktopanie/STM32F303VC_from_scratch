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
	//RRC sysclock enable for exti ??
	wsk = (uint32_t*)(RRC_OFFSET + 0x18UL);
	*wsk |= (1<<0);

	//EXTI rising edge detection
	wsk = (uint32_t*)(EXTI_OFFSET + 0x08UL);
	*wsk |= (1 << 0);

	//Exti interrupt enable
	wsk = (uint32_t*)(EXTI_OFFSET + 0x00UL);
	*wsk |= (1<< 0);

	///DOPISANE Z FILMU????????????????????????????????
	wsk = (uint32_t*)(0xE000E100);
	*wsk |= (1<< 6);
	//?????????????????????????????????????????????

}

void DMA_interrupt_set(uint8_t DMA_number, uint8_t DMA_channel){

	uint32_t * wsk;



	if(DMA_number == DMA_NUM_1){

		wsk = (uint32_t*)(NVIC_VECT_0);

		switch(DMA_channel){
			case 1:
				*wsk |= (1<<11);
				break;
			case 2:
				*wsk |= (1<<12);
				break;
			case 3:
				*wsk |= (1<<13);
				break;
			case 4:
				*wsk |= (1<<14);
				break;
			case 5:
				*wsk |= (1<<15);
				break;
			case 6:
				*wsk |= (1<<16);
				break;
			case 7:
				*wsk |= (1<<17);
				break;

		}
	}else if (DMA_number == DMA_NUM_2){

		wsk = (uint32_t*)(NVIC_VECT_1);

		switch(DMA_channel){
			case 1:
				*wsk |= (1<<24);
				break;
			case 2:
				*wsk |= (1<<25);
				break;
			case 3:
				*wsk |= (1<<26);
				break;
			case 4:
				*wsk |= (1<<27);
				break;
			case 5:
				*wsk |= (1<<28);
				break;
			case 6:
				*wsk |= (1<<29);
				break;
			case 7:
				*wsk |= (1<<30);
				break;

		}
	}
}
