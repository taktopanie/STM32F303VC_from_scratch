/*
 * MY_interrupt.h
 *
 *  Created on: Dec 1, 2022
 *      Author: root
 */

#ifndef MY_INTERRUPT_H_
#define MY_INTERRUPT_H_

#define EXTI_OFFSET 0x40010400UL
#define RRC_OFFSET 0x40021000UL

void TIMER2_interrupt_set(void);
void GPIO_interrupt_set(void);


#endif /* MY_INTERRUPT_H_ */
