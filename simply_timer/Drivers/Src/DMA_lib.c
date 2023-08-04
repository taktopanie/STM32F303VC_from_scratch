/*
 * DMA_lib.c
 *
 *  Created on: Aug 1, 2023
 *      Author: maciej
 */

#include<DMA_lib.h>
#include<stm32f3xx.h>

void DMAClockControl(uint8_t DMA_Number ,uint8_t En){

	if(DMA_Number == DMA_NUM_1){
		if(En == 1){
			RCC->AHBENR |= (1<<0);
		}else{
			RCC->AHBENR &= ~(1<<0);
		}
	}else if (DMA_Number == DMA_NUM_2){
		if(En == 1){
			RCC->AHBENR |= (1<<1);
		}else{
			RCC->AHBENR &= ~(1<<1);
		}
	}
}


void DMA_Init(DMA_Handle_t* DMA_Handler){

	/*
The following sequence should be followed to configure a DMA channel x (where x is the
channel number).
1. Set the peripheral register address in the DMA_CPARx register. The data will be
moved from/ to this address to/ from the memory after the peripheral event.
2. Set the memory address in the DMA_CMARx register. The data will be written to or
read from this memory after the peripheral event.
3. Configure the total number of data to be transferred in the DMA_CNDTRx register.
After each peripheral event, this value will be decremented.
4. Configure the channel priority using the PL[1:0] bits in the DMA_CCRx register
5. Configure data transfer direction, circular mode, peripheral & memory incremented
mode, peripheral & memory data size, and interrupt after half and/or full transfer in the
DMA_CCRx register
6. Activate the channel by setting the ENABLE bit in the DMA_CCRx register
	 */

	DMA_RegDef_t* DMA;
	if(DMA_Handler->DMA_NUMBER == DMA_NUM_1){
		DMA = (DMA_RegDef_t*)DMA_1_BASEADDR;
	}else if(DMA_Handler->DMA_NUMBER == DMA_NUM_2){
		DMA = (DMA_RegDef_t*)DMA_2_BASEADDR;
	}

	volatile uint32_t *CCRx;
	volatile uint32_t *CNDTRx;
	volatile uint32_t *CPARx;
	volatile uint32_t *CMARx;

	switch(DMA_Handler->CHANNEL_NUMBER){
	case 1 :
		CCRx = 		&DMA->DMA_CCR1;
		CNDTRx = 	&DMA->DMA_CNDTR1;
		CMARx = 	&DMA->DMA_CMAR1;
		CPARx = 	&DMA->DMA_CPAR1;
		break;
	case 2 :
		CCRx = 		&DMA->DMA_CCR2;
		CNDTRx = 	&DMA->DMA_CNDTR2;
		CMARx = 	&DMA->DMA_CMAR2;
		CPARx = 	&DMA->DMA_CPAR2;
		break;
	case 3 :
		CCRx = 		&DMA->DMA_CCR3;
		CNDTRx = 	&DMA->DMA_CNDTR3;
		CMARx = 	&DMA->DMA_CMAR3;
		CPARx = 	&DMA->DMA_CPAR3;
		break;
	case 4 :
		CCRx = 		&DMA->DMA_CCR4;
		CNDTRx = 	&DMA->DMA_CNDTR4;
		CMARx = 	&DMA->DMA_CMAR4;
		CPARx = 	&DMA->DMA_CPAR4;
		break;
	case 5 :
		CCRx = 		&DMA->DMA_CCR5;
		CNDTRx = 	&DMA->DMA_CNDTR5;
		CMARx = 	&DMA->DMA_CMAR5;
		CPARx = 	&DMA->DMA_CPAR5;
		break;
	case 6 :
		CCRx = 		&DMA->DMA_CCR6;
		CNDTRx = 	&DMA->DMA_CNDTR6;
		CMARx = 	&DMA->DMA_CMAR6;
		CPARx = 	&DMA->DMA_CPAR6;
		break;
	case 7 :
		CCRx = 		&DMA->DMA_CCR7;
		CNDTRx = 	&DMA->DMA_CNDTR7;
		CMARx = 	&DMA->DMA_CMAR7;
		CPARx = 	&DMA->DMA_CPAR7;
		break;
	}

	*CPARx 	= DMA_Handler->SOURCE_ADDRESS;
	*CMARx 	= DMA_Handler->DESTINATION_ADDRESS;
	*CCRx 	= (DMA_Handler->DATA_TRANSFER_DIRECTION<<4)|\
			(DMA_Handler->CIRCULAR_MODE << 5)|\
			(DMA_Handler->PERIPH_INCREMENT_MODE << 6)|\
			(DMA_Handler->MEMORY_INCREMENT_MODE << 7)|\
			(DMA_Handler->PERI_SIZE << 8)|\
			(DMA_Handler->MEM_SIZE << 10)|\
			(DMA_Handler->PRIORITY << 12)|\
			(DMA_Handler->M2M_MODE << 14);

	*CNDTRx	= DMA_Handler->NUMBER_OF_DATA_TRANSFER;

	//enable DMA channel and transfer completed interrupt
	*CCRx	|= (1 << 0) | (1 << 1);

}

void DMA_IRQ_handling(DMA_RegDef_t* DMA_handler){
	if(DMA_handler->DMA_ISR & (1<<24)){
		DMA_handler->DMA_IFCR |= (1<<24);
	}
	if(DMA_handler->DMA_ISR & (1<<25)){
		DMA_handler->DMA_IFCR |= (1<<25);
	}
	if(DMA_handler->DMA_ISR & (1<<26)){
		DMA_handler->DMA_IFCR |= (1<<26);
	}
}
