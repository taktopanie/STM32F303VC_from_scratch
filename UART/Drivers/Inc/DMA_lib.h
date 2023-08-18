/*
 * DMA_lib.h
 *
 *  Created on: Aug 1, 2023
 *      Author: maciej
 */

#ifndef INC_DMA_LIB_H_
#define INC_DMA_LIB_H_

#include<stm32f3xx.h>

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

void DMAClockControl(uint8_t DMA_Number ,uint8_t En);


/*
 *  DMA configuration function
 *  @parameters which should be passed throught @DMA_Handle_t:
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
 */

void DMA_Init(DMA_Handle_t* DMA_Handler);

void DMA_IRQ_handling(DMA_RegDef_t* DMA_handler);

#endif /* INC_DMA_LIB_H_ */
