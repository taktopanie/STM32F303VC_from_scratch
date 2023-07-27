/*
 * stm32f3xx.h
 *
 *  Created on: Dec 1, 2022
 *      Author: root
 */

#ifndef STM32F3XX_H_
#define STM32F3XX_H_

#include <stddef.h>
#include <stdint.h>
/*
 * Function definitons
 */
void systick (int time_ms);

/*
 * user define
 */
#define __vo volatile
#define __weak __attribute__ ((weak))
/*
 * @STATES
 */
#define ENABLE 						1
#define DISABLE 					0

/*
 * ARM Cortex Mx Processor NVIC ISERx register Addresses
 */
#define NVIC_ISER0					((__vo uint32_t *)0xE000E100)
#define NVIC_ISER1					((__vo uint32_t *)0xE000E104)
#define NVIC_ISER2					((__vo uint32_t *)0xE000E108)
#define NVIC_ISER3					((__vo uint32_t *)0xE000E10C)

/*
 * ARM Cortex Mx Processor NVIC ICERx register Addresses
 */
#define NVIC_ICER0					((__vo uint32_t *)0XE000E180)
#define NVIC_ICER1					((__vo uint32_t *)0XE000E184)
#define NVIC_ICER2					((__vo uint32_t *)0XE000E188)
#define NVIC_ICER3					((__vo uint32_t *)0XE000E18C)

/*
 * ARM Cortex Mx Processor Priorioty Register Address Calculation
 */
#define NVIC_PR_BASE_ADDR			((__vo uint32_t *)0xE000E400)

#define NO_PR_BITS_IMPLEMENTED		4

/*
 * GPIO port definitions
 */
#define GPIOA_BASEADDR 				0x48000000UL
#define GPIOB_BASEADDR 				0x48000400UL
#define GPIOC_BASEADDR 				0x48000800UL
#define GPIOD_BASEADDR 				0x48000C00UL
#define GPIOE_BASEADDR 				0x48001000UL

#define RCC_BASEADDR 				0x40021000UL
#define EXTI_BASEADDR				0x40010400UL
#define SYSCFG_BASEADDR				0x40010000UL

#define SPI_1_BASEADDR				0x40013000UL
#define SPI_2_BASEADDR				0x40003800UL
#define SPI_3_BASEADDR				0x40003C00UL


/*
 * Registers typedef
 */

/*
 * RCC overall registers
 */
typedef struct{
	__vo uint32_t CR; 					/* < Clock control register							Address offset: 0x00*/
	__vo uint32_t CFGR; 				/* < Clock configuration register					Address offset: 0x04*/
	__vo uint32_t CIR; 					/* < Clock interrupt register						Address offset: 0x08*/
	__vo uint32_t APB2RSTR; 			/* < APB2 peripheral reset register					Address offset: 0x0C*/
	__vo uint32_t APB1RSTR; 			/* < APB1 peripheral reset register					Address offset: 0x10*/
	__vo uint32_t AHBENR; 				/* < AHB peripheral clock enable register			Address offset: 0x14*/
	__vo uint32_t APB2ENR; 				/* < APB2 peripheral clock enable register			Address offset: 0x18*/
	__vo uint32_t APB1ENR; 				/* < APB1 peripheral clock enable register			Address offset: 0x1C*/
	__vo uint32_t BDCR; 				/* < RTC domain control register					Address offset: 0x20*/
	__vo uint32_t CSR; 					/* < Control/status register						Address offset: 0x24*/
	__vo uint32_t AHBRSTR; 				/* < AHB peripheral reset register					Address offset: 0x28*/
	__vo uint32_t CFGR2; 				/* < Clock configuration register 2					Address offset: 0x2C*/
	__vo uint32_t CFGR3; 				/* < Clock configuration register 3					Address offset: 0x30*/
}RCC_RegDef_t;

/*
 * GPIO structure definition
 */
typedef struct {
	__vo uint32_t MODER;				/* < Register with PIN mode					Address offset:0x00 */
	__vo uint32_t OTYPER;				/* < Register with PIN type					Address offset:0x04 */
	__vo uint32_t OSPEEDR;				/* < Register with PIN speed				Address offset:0x08 */
	__vo uint32_t PUPDR;				/* < Register with pull UP/DOWN res			Address offset:0x0C */
	__vo uint32_t IDR;					/* < Input data register					Address offset:0x10 */
	__vo uint32_t ODR;					/* < Output data register					Address offset:0x14 */
	__vo uint32_t BSRR;					/* < Bit set/reset register					Address offset:0x18 */
	__vo uint32_t LCKR;					/* < Lock register							Address offset:0x1C */
	__vo uint32_t AF[2];				/* < Alternate function register	 		0 -	Address offset:0x20 - LOW REGISTER
																				1 - Address offset:0x24 - HIGH REGISTER */
	__vo uint32_t BRR;					/* < Bit reset register						Address offset:0x28 */

}GPIO_RegDef_t;

/*
 * EXTI structure definition
 */
typedef struct{
	__vo uint32_t IMR1;					/* < Interrupt mask register 1					Address offset: 0x00 */
	__vo uint32_t EMR1;					/* < Event mask register 1						Address offset: 0x04 */
	__vo uint32_t RTSR1;				/* < Rising trigger selection register			Address offset: 0x08 */
	__vo uint32_t FTSR1;				/* < Falling trigger selection register 1		Address offset: 0x0C */
	__vo uint32_t SWIER1;				/* < Software interrupt event register 1		Address offset: 0x10 */
	__vo uint32_t PR1;					/* < Pending register 1							Address offset: 0x14 */
	__vo uint32_t IMR2;					/* < Interrupt mask register 2					Address offset: 0x20 */
	__vo uint32_t EMR2;					/* < Event mask register 2						Address offset: 0x24 */
	__vo uint32_t RTSR2;				/* < Rising trigger selection register 2		Address offset: 0x28 */
	__vo uint32_t FTSR2;				/* < Falling trigger selection register 2		Address offset: 0x2C */
	__vo uint32_t SWIER2;				/* < Software interrupt event register 2		Address offset: 0x30 */
	__vo uint32_t PR2;					/* < Pending register 2							Address offset: 0x34 */
}EXTI_RegDef_t;

/*
 * SYSCFG structure definition
 */
typedef struct{
	__vo uint32_t CFGR1;				/* <  */
	__vo uint32_t RCR;					/* <  */
	__vo uint32_t EXTICR[4];			/* <  */
	__vo uint32_t CFGR2;				/* <  */
	uint32_t RESERVED_1 [12];
	__vo uint32_t CFGR4;				/* <  */
	__vo uint32_t CFGR3;				/* <  */
}SYSCFG_RegDef_t;


typedef struct{
	__vo uint32_t TIMx_CR1;
	__vo uint32_t TIMx_CR2;
	__vo uint32_t TIMx_SMCR;
	__vo uint32_t TIMx_DIER;
	__vo uint32_t TIMx_SR;
	__vo uint32_t TIMx_EGR;
	__vo uint32_t TIMx_CCMR1;
	__vo uint32_t TIMx_CCMR2;
	__vo uint32_t TIMx_CCER;
	__vo uint32_t TIMx_CNT;
	__vo uint32_t TIMx_PSC;
	__vo uint32_t TIMx_ARR;
	uint32_t RESERVED_1;
	__vo uint32_t TIMx_CCR1;
	__vo uint32_t TIMx_CCR2;
	__vo uint32_t TIMx_CCR3;
	__vo uint32_t TIMx_CCR4;
	uint32_t RESERVED_2;
	__vo uint32_t TIMx_DCR;
	__vo uint32_t TIMx_DMAR;
}Timer_RegDef;

/*
 * Peripheral definitions
 */
//@GPIOADDRESS
#define GPIOA 						((GPIO_RegDef_t *)GPIOA_BASEADDR)
#define GPIOB 						((GPIO_RegDef_t *)GPIOB_BASEADDR)
#define GPIOC 						((GPIO_RegDef_t *)GPIOC_BASEADDR)
#define GPIOD 						((GPIO_RegDef_t *)GPIOD_BASEADDR)
#define GPIOE 						((GPIO_RegDef_t *)GPIOE_BASEADDR)

#define RCC 						((RCC_RegDef_t*)RCC_BASEADDR)
#define EXTI						((EXTI_RegDef_t*)EXTI_BASEADDR)
#define SYSCFG						((SYSCFG_RegDef_t*)SYSCFG_BASEADDR)

#define GPIOA_PCLK_EN() 			(RCC->AHBENR |= (1<<17))
#define GPIOB_PCLK_EN() 			(RCC->AHBENR |= (1<<18))
#define GPIOC_PCLK_EN() 			(RCC->AHBENR |= (1<<19))
#define GPIOD_PCLK_EN() 			(RCC->AHBENR |= (1<<20))
#define GPIOE_PCLK_EN() 			(RCC->AHBENR |= (1<<21))

#define GPIOA_PCLK_DIS() 			(RCC->AHBENR &= ~(1<<17))
#define GPIOB_PCLK_DIS() 			(RCC->AHBENR &= ~(1<<18))
#define GPIOC_PCLK_DIS() 			(RCC->AHBENR &= ~(1<<19))
#define GPIOD_PCLK_DIS() 			(RCC->AHBENR &= ~(1<<20))
#define GPIOE_PCLK_DIS() 			(RCC->AHBENR &= ~(1<<21))

#define GPIOA_DEINIT() 				do{RCC->AHBRSTR |= (1<<17); RCC->AHBRSTR &= ~(1<<17);}while(0)
#define GPIOB_DEINIT() 				do{RCC->AHBRSTR |= (1<<18); RCC->AHBRSTR &= ~(1<<18);}while(0)
#define GPIOC_DEINIT() 				do{RCC->AHBRSTR |= (1<<19); RCC->AHBRSTR &= ~(1<<19);}while(0)
#define GPIOD_DEINIT() 				do{RCC->AHBRSTR |= (1<<20); RCC->AHBRSTR &= ~(1<<20);}while(0)
#define GPIOE_DEINIT() 				do{RCC->AHBRSTR |= (1<<21); RCC->AHBRSTR &= ~(1<<21);}while(0)

#define SYSCFG_PCLK_EN() 			(RCC->APB2ENR |= (1<<0))

/*
 * Clock enable macros for SPIx peripherals
 */

#define SPI1_PCLK_EN() 				(RCC->APB2ENR |= (1<<12))
#define SPI2_PCLK_EN() 				(RCC->APB1ENR |= (1<<14))
#define SPI3_PCLK_EN() 				(RCC->APB1ENR |= (1<<15))

/*
 * macro which set GPIO port in SYSCFG config REG
 */
#define GPIO_BASEADDR_TO_CODE(x)	(	(x == GPIOA) ? 0 :\
										(x == GPIOB) ? 1 :\
										(x == GPIOC) ? 2 :\
										(x == GPIOD) ? 3 :\
										(x == GPIOE) ? 4 : 0 )

/*
 * @IRQ_IT_NUM
 * IRQ (interrupt request) Number of STM32F303VC MCU
 * NOTE: look on MCU Reference Manual for more
 */
#define IRQ_NO_EXTI0				6
#define IRQ_NO_EXTI1				7
#define IRQ_NO_EXTI2				8
#define IRQ_NO_EXTI3				9
#define IRQ_NO_EXTI4				10
#define IRQ_NO_EXTI9_5				23
#define IRQ_NO_EXTI10_15			40
#define IRQ_NO_SPI1					35
#define IRQ_NO_SPI2					36
#define IRQ_NO_SPI3					51


/*
 * SPI registers
 */
typedef struct{
__vo uint32_t SPIx_CR1;
__vo uint32_t SPIx_CR2;
__vo uint32_t SPIx_SR;
__vo uint32_t SPIx_DR;
__vo uint32_t SPIx_CRCPR;
__vo uint32_t SPIx_RXCRCR;
__vo uint32_t SPIx_TXCRCR;
__vo uint32_t SPIx_I2SCFGR;
__vo uint32_t SPIx_I2SPR;
}SPI_RegDef_t;

#define SPI1						((SPI_RegDef_t*) SPI_1_BASEADDR)
#define SPI2						((SPI_RegDef_t*) SPI_2_BASEADDR)
#define SPI3						((SPI_RegDef_t*) SPI_3_BASEADDR)

/*********************************************************************************
 * BIT POSITION DEFINITIONS OF SPI PERIPHERAL
 ********************************************************************************/
#define SPI_CR1_CPHA				0
#define SPI_CR1_CPOL				1
#define SPI_CR1_MSTR				2
#define SPI_CR1_BR					3
#define SPI_CR1_SPE					6
#define SPI_CR1_LSBFIRST			7
#define SPI_CR1_SSI					8
#define SPI_CR1_SSM					9
#define SPI_CR1_RXONLY				10
#define SPI_CR1_CRCL				11
#define SPI_CR1_CRCNEXT				12
#define SPI_CR1_CRCEN				13
#define SPI_CR1_BIDIOE				14
#define SPI_CR1_BIDIMODE			15

#define SPI_CR2_RXDMAEN				0
#define SPI_CR2_TXDMAEN				1
#define SPI_CR2_SSOE				2
#define SPI_CR2_NSSP				3
#define SPI_CR2_FRF					4
#define SPI_CR2_ERRIE				5
#define SPI_CR2_RXNEIE				6
#define SPI_CR2_TXEIE				7
#define SPI_CR2_DS					8
#define SPI_CR2_FRXT_H				12
#define SPI_CR2_LDMA_RX				13
#define SPI_CR2_LDMA_TX				14

#define SPI_SR_RXNE					0
#define SPI_SR_TXE					1
#define SPI_SR_CHSIDE				2
#define SPI_SR_UDR					3
#define SPI_SR_CRCERR				4
#define SPI_SR_MODF					5
#define SPI_SR_OVR					6
#define SPI_SR_BSY					7
#define SPI_SR_FRE					8
#define SPI_SR_FRLVL				9
#define SPI_SR_FTLVL				11

//SPI FLAGS
#define SPI_RXNE_FLAG				(1 << SPI_SR_RXNE)
#define SPI_TXE_FLAG				(1 << SPI_SR_TXE)
#define SPI_BUSY_FLAG				(1 << SPI_SR_BSY)

#define FLAG_SET					1
#define FLAG_RESET					0

//TIMERS
#define  TIMER2	((Timer_RegDef*)0x40000000UL)
#define  TIMER3	((Timer_RegDef*)0x40000400UL)
#define  TIMER4	((Timer_RegDef*)0x40000800UL)

#endif /* STM32F3XX_H_ */
