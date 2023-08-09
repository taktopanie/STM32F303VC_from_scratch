/*
 * MY_interrupt.h
 *
 *  Created on: Dec 1, 2022
 *      Author: root
 */

#ifndef MY_INTERRUPT_H_
#define MY_INTERRUPT_H_

#include <stm32f3xx.h>

#define EXTI_OFFSET 0x40010400UL
#define RRC_OFFSET 0x40021000UL

#define NVIC_BASE	0xE000E100

#define NVIC_VECT_0 NVIC_BASE
#define NVIC_VECT_1 NVIC_BASE + 0x4


void TIMER_interrupt_set(Timer_RegDef* wsk_tim);

void GPIO_interrupt_set(void);
/*
 * @params: 	DMA_number - DMA_NUM_x,
 * 				DMA_channel - DMA_CHANNEL_x
 */
void DMA_interrupt_set(uint8_t DMA_number, uint8_t DMA_channel);

#endif /* MY_INTERRUPT_H_ */
