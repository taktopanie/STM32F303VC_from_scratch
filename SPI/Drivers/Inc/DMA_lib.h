/*
 * DMA_lib.h
 *
 *  Created on: Aug 1, 2023
 *      Author: maciej
 */

#ifndef INC_DMA_LIB_H_
#define INC_DMA_LIB_H_

#include<stm32f3xx.h>

/********************** HOW TO SET UP SIMPLE DMA REQUEST **********************
 *
 * 1. Turn on DMA clock by DMAClockControl
 *
 * 2. Create @DMA_Handle_t and fill it with below informations
 *  - DMA_Handler -> DMA_NUMBER					SEE @DMA_NUMBERS
 *  - DMA_Handler -> CHANNEL_NUMBER				SEE @DMA_CHANNELS
 *  - DMA_Handler -> SOURCE_ADDRESS				32-bit periph/memory
 *  											source base address
 *  - DMA_Handler -> DESTINATION_ADDRESS		32-bit memory base address
 *  - DMA_Handler -> NUMBER_OF_DATA_TRANSFER	number of transfer which
 *  											should be performed after event
 *	- DMA_Handler -> PRIORITY. 					SEE @DMA_PRIORITIES
 *	- DMA_Handler -> M2M_MODE					1-ON, 0-OFF
 *	- DMA_Handler -> MEM_SIZE					SEE @DMA_MEM_SIZE
 *	- DMA_Handler -> PERI_SIZE					SEE @DMA_MEM_SIZE
 *	- DMA_Handler -> MEMORY_INCREMENT_MODE		1-ON, 0-OFF
 *	- DMA_Handler -> PERIPH_INCREMENT_MODE		1-ON, 0-OFF
 *	- DMA_Handler -> CIRCULAR_MODE				1-ON, 0-OFF
 *	- DMA_Handler -> DATA_TRANSFER_DIRECTION	SEE @DMA_DIRECTIONS
 *
 * 3. Call the function DMA_Init to initialize the DMA
 *
 * 4. Fill the IRQ handler function DMA[x]_CH[y]_IRQHandler
 *
 * 4. Turn on NVIC_vector by DMA_interrupt_set
 *
 *******************************************************************************/

typedef struct{
	uint8_t DMA_NUMBER;
	uint8_t CHANNEL_NUMBER;
	uint32_t SOURCE_ADDRESS;
	uint32_t DESTINATION_ADDRESS;
	uint32_t NUMBER_OF_DATA_TRANSFER;
	uint32_t PRIORITY;
	uint32_t M2M_MODE;
	uint8_t	MEM_SIZE;
	uint8_t PERI_SIZE;
	uint8_t MEMORY_INCREMENT_MODE;
	uint8_t PERIPH_INCREMENT_MODE;
	uint8_t CIRCULAR_MODE;
	uint8_t DATA_TRANSFER_DIRECTION;
}DMA_Handle_t;

/*
 * DMA_NUMBERS
 */
#define DMA_NUM_1					1
#define DMA_NUM_2					2

/*
 * DMA_CHANNELS
 */
#define DMA_CHANNEL_1				1
#define DMA_CHANNEL_2				2
#define DMA_CHANNEL_3				3
#define DMA_CHANNEL_4				4
#define DMA_CHANNEL_5				5
#define DMA_CHANNEL_6				6
#define DMA_CHANNEL_7				7

/*
 * DMA_PRIORITIES
 */
#define DMA_PRIORITY_LOW				0
#define DMA_PRIORITY_MEDIUM				1
#define DMA_PRIORITY_HIGH				2
#define DMA_PRIORITY_VERY_HIGH			3

/*
 * DMA_MEM_SIZE
 */
#define DMA_MEM_SIZE_8_BIT				0
#define DMA_MEM_SIZE_16_BIT				1
#define DMA_MEM_SIZE_32_BIT				2

/*
 * DMA_DIRECTIONS
 */
#define DMA_READ_FROM_PERIPH			0
#define DMA_READ_FROM_MEM				1

/*
 * Function which enable DMA periph clock
 */

void DMAClockControl(uint8_t DMA_Number ,uint8_t En);

/*
*  DMA configuration function
*  @parameters should be passed throught @DMA_Handle_t
*/

void DMA_Init(DMA_Handle_t* DMA_Handler);

void DMA_IRQ_handling(DMA_RegDef_t* DMA_handler);

/*
 * @params: 	DMA_number - DMA_NUM_x,
 * 				DMA_channel - DMA_CHANNEL_x
 */
void DMA_interrupt_set(uint8_t DMA_number, uint8_t DMA_channel);

#endif /* INC_DMA_LIB_H_ */
