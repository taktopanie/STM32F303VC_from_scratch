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
#define NVIC_VECT_0 0xE000E100

void TIMER_interrupt_set(Timer_RegDef* wsk_tim);
void GPIO_interrupt_set(void);


#endif /* MY_INTERRUPT_H_ */
