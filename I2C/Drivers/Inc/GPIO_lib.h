/*
 * GPIO_lib.h
 *
 *  Created on: Dec 1, 2022
 *      Author: root
 */

#ifndef GPIO_LIB_H_
#define GPIO_LIB_H_

#include<stm32f3xx.h>


/********************** HOW TO SET UP GPIO **********************
 * 1. Turn on GPIO port clock by PeriClockControl()
 *
 * 2. Create @GPIO_Handle_t and fill it with below informations
 * 	- GPIO_Handler.GPIO_Regdef -> GPIO_ADDRESS			SEE @GPIOADDRESS
 *  - GPIO_Handler.GPIO_config -> Pin_Number			SEE @PIN_NUMBERS
 *  - GPIO_Handler.GPIO_config -> Pin_Mode				SEE @GPIO_PIN_MODES
 *  - GPIO_Handler.GPIO_config -> Pin_Output_Type;		SEE @GPIO_OUT_TYPES
 *  - GPIO_Handler.GPIO_config -> Pin_Speed;			SEE @GPIO_SPEED
 *  - GPIO_Handler.GPIO_config -> Pin_Pull;				SEE @GPIO_PULL
 *  - GPIO_Handler.GPIO_config -> Pin_alt_func;			SEE @ALTERNATE_FUNCTIONS
 *
 * 3. Call the function GPIO_Init() to initialize the GPIO
 *
********************** IF IRQ's are needed **********************
 *
 * 4. Fill the IRQ handler function EXTIx_IRQHandler() with GPIO_IRQHandling();
 *
 * 5. Set up interrupt seting's in GPIO_interrupt_set()
 *
 * 6. Map the EXTI channel to proper GPIO port by GPIO_EXTI_PortMap();
 *
 * 7. Turn on NVIC_vector by GPIO_IRQITConfig()
 *
****************************************************************/

/*
 * GPIO Pin configuration structure
 */
typedef struct{
	uint8_t Pin_Number;				/*<	value can be one of @PIN_NUMBERS */
	uint8_t Pin_Mode;				/*<	value can be one of @GPIO_PIN_MODES */
	uint8_t Pin_Output_Type;		/*<	value can be one of @GPIO_OUT_TYPES */
	uint8_t Pin_Speed;				/*<	value can be one of @GPIO_SPEED */
	uint8_t Pin_Pull;				/*<	value can be one of @GPIO_PULL */
	uint8_t Pin_alt_func;			/*<	value can be one of @ALTERNATE_FUNCTIONS */

}GPIO_PinConfig_t;

typedef struct{
	GPIO_RegDef_t * GPIO_Regdef;	/*<	value can be one of @GPIOADDRESS */
	GPIO_PinConfig_t GPIO_config;	/*<	the GPIO config structure */

}GPIO_Handle_t;


/*
 * @PIN_NUMBERS
 * pin numbers definitions
 */
#define GPIO_PIN_0 0
#define GPIO_PIN_1 1
#define GPIO_PIN_2 2
#define GPIO_PIN_3 3
#define GPIO_PIN_4 4
#define GPIO_PIN_5 5
#define GPIO_PIN_6 6
#define GPIO_PIN_7 7
#define GPIO_PIN_8 8
#define GPIO_PIN_9 9
#define GPIO_PIN_10 10
#define GPIO_PIN_11 11
#define GPIO_PIN_12 12
#define GPIO_PIN_13 13
#define GPIO_PIN_14 14
#define GPIO_PIN_15 15

/*
 * @GPIO_PIN_MODES
 * avalible modes of pins
 */
#define GPIO_MODE_INPUT					0
#define GPIO_MODE_OUTPUT				1
#define GPIO_MODE_ALTERNATE				2
#define GPIO_MODE_ANALOG				3
#define GPIO_MODE_IT_FT					4
#define GPIO_MODE_IT_RT					5
#define GPIO_MODE_IT_FRT				6

/*
 * @GPIO_OUT_TYPES
 * pin output types
 */
#define GPIO_PUSH_PULL					0				/* < Output push-pull*/
#define GPIO_FLOATING					1				/* < Output open drain*/

/*
 * @GPIO_SPEED
 * Refer to the device datasheet for the frequency specifications and the power supply and load conditions for each speed.
 */
#define GPIO_SPEED_LOW					0
#define GPIO_SPEED_MEDIUM				1
#define GPIO_SPEED_HIGH					3

/*
 * @GPIO_PULL
 */
#define GPIO_NO_PULL					0
#define GPIO_PULL_UP					1
#define GPIO_PULL_DOWN					2

/*
 * @GPIO_PIN_States
 */
#define GPIO_PIN_RESET					0
#define GPIO_PIN_SET					1


/*
 * @CLOCK_STATE
 */
#define CLOCK_DISABLE					0
#define CLOCK_ENABLE 					1

/*
 * @ALTERNATE_FUNCTIONS
 */
#define AF_0							0
#define AF_1							1
#define AF_2							2
#define AF_3							3
#define AF_4							4
#define AF_5							5
#define AF_6							6
#define AF_7							7
#define AF_8							8
#define AF_9							9
#define AF_10							10
#define AF_11							11
#define AF_12							12
#define AF_13							13
#define AF_14							14
#define AF_15							15


/*
 * GPIO function definition
 */
void PeriClockControl(GPIO_RegDef_t * pGPIO, uint8_t En);

void GPIO_Init(GPIO_Handle_t * pGPIO_Handler);
void GPIO_DeInit(GPIO_RegDef_t * pGPIO_Reg);

uint8_t GPIO_ReadPin(GPIO_RegDef_t * pGPIO_Reg, uint8_t PIN_Number);
uint16_t GPIO_ReadPort(GPIO_RegDef_t * pGPIO_Reg);

void GPIO_WritePort(GPIO_RegDef_t * pGPIO_Reg, uint8_t Value);
void GPIO_WritePin(GPIO_RegDef_t * pGPIO_Reg, uint8_t PIN, uint8_t Value);
void GPIO_TogglePin(GPIO_RegDef_t * pGPIO_Reg, uint8_t PIN_Number);

void GPIO_IRQITConfig(uint8_t IRQNumber, uint8_t EnorDi);
void GPIO_IRQPriorityConfig(uint8_t IRQNumber, uint32_t IRQPriority);

void GPIO_IRQHandling(uint8_t PinNumber);

void GPIO_interrupt_set(uint8_t Edge, uint8_t PinNumber);

void GPIO_EXTI_PortMap(uint8_t EXTI_NR, GPIO_RegDef_t * GPIOx);

#endif /* GPIO_LIB_H_ */
