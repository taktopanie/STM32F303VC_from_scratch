/*
 * SPI_lib.c
 *
 *  Created on: Dec 27, 2022
 *      Author: root
 */

#include <SPI_lib.h>
#include <stm32f3xx.h>

static void SPI_txe_IT_handle(SPI_Handle_t * pSPI_Handler);
static void SPI_rxe_IT_handle(SPI_Handle_t * pSPI_Handler);
static void SPI_ovr_IT_handle(SPI_Handle_t * pSPI_Handler);

/*
 * @fn					- SPI_PeriClockControl
 *
 * @brief				- Configure the SPI clock
 *
 * @param[in]			- pSPI address
 * @param[in]			- Clock_State (ENABLE/DISABLE)
 *
 * @return				- void
 */
void SPI_PeriClockControl(SPI_RegDef_t * pSPI, uint8_t Clock_State){
	if( Clock_State == ENABLE){

		if (pSPI == SPI1){
			SPI1_PCLK_EN();
		}else if (pSPI == SPI2){
			SPI2_PCLK_EN();
		}else if (pSPI == SPI3){
			SPI3_PCLK_EN();
		}

	}else{
		//TODO
	}
}

/*
 * @fn					- SPI_Init
 *
 * @brief				- initialize the SPI interface
 *
 * @param[in]			- pSPI_Handler - handler to SPI structure
 *
 * @return				- void
 */
void SPI_Init(SPI_Handle_t * pSPI_Handler){
	uint32_t tempreg1 = 0;
	uint32_t tempreg2 = 0;

	SPI_PeriClockControl(pSPI_Handler->pSPIx, ENABLE);

	//1. CONFIGURE THE DEVICE MODE
	tempreg1 |= pSPI_Handler->SPIConfig.SPI_DeviceMode << SPI_CR1_MSTR;

	//2. CONFIGURE THE BUS CONFIG
	if(pSPI_Handler->SPIConfig.SPI_BusConfig == SPI_BUS_CONFIG_FD){
		//BIDI MODE SHOULD BE CLEARED
		tempreg1 &= ~(1 << SPI_CR1_BIDIMODE);
	}else if(pSPI_Handler->SPIConfig.SPI_BusConfig == SPI_BUS_CONFIG_HD){
		//BIDI MODE SHOULD BE SET
		tempreg1 |= (1 << SPI_CR1_BIDIMODE);
	}else if(pSPI_Handler->SPIConfig.SPI_BusConfig == SPI_BUS_CONFIG_SIMPLEX_RXONLY){
		//BIDI MODE SHOULD BE CLEARED
		tempreg1 &= ~(1 << SPI_CR1_BIDIMODE);
		//tempreg1 $= ~(1 << 14);
		//RXONLY BIT MUST BE SET
		tempreg1 |= (1 << SPI_CR1_RXONLY);
 	}

	//3. CONFIGURE THE SPI SERIAL CLOCK SPEED
	tempreg1 |= (pSPI_Handler->SPIConfig.SPI_SclkSpeed << SPI_CR1_BR);

	//4. CONFIGURE THE DFF
	tempreg2 |= (pSPI_Handler->SPIConfig.SPI_DFF << SPI_CR2_DS);

	//5. CONFIGURE THE CPOL
	tempreg1 |= (pSPI_Handler->SPIConfig.SPI_CPOL << SPI_CR1_CPOL);

	//6. CONFIGURE THE CPHA
	tempreg1 |= (pSPI_Handler->SPIConfig.SPI_CPHA << SPI_CR1_CPHA);

	//7. CONFIGURE THE SSM
	tempreg1 |= (pSPI_Handler->SPIConfig.SPI_SSM << SPI_CR1_SSM);

	//8. CONFIGURE INTERRUPT SIZE 8BIT/16BIT
	if(pSPI_Handler->SPIConfig.SPI_DFF < 8){
		//8bit frame
		tempreg2 |= (1 << SPI_CR2_FRXT_H);
		//pSPIx->SPIx_CR2 |= (1<< SPI_CR2_FRXT_H);
	}else{
		//16bit frame
		tempreg2 &= ~(1 << SPI_CR2_FRXT_H);
		//pSPIx->SPIx_CR2 &= ~(1<< SPI_CR2_FRXT_H);
	}

	pSPI_Handler->pSPIx->SPIx_CR1 = tempreg1;
	pSPI_Handler->pSPIx->SPIx_CR2 = tempreg2;
}

/*
 * @fn					- SPI_DeInit
 *
 * @brief				- deinitialize the SPI --> TODO
 *
 * @param[in]			-
 * @param[in]			-
 *
 * @return				-
 */
void SPI_DeInit(SPI_RegDef_t * pSPI_Reg){
	//TODO
}

/*
 * @fn					- SPI_GetFlagStatus
 *
 * @brief				- returns the status of the given flag
 *
 * @param[in]			- pSPIx adress of the given SPI
 * @param[in]			- FlagName - name of the flag (see SPI FLAGS in stm32f3xx.h)
 *
 * @return				- FLAG_SET/FLAG_RESET
 */
uint8_t SPI_GetFlagStatus(SPI_RegDef_t *pSPIx, uint32_t FlagName){
	if(pSPIx->SPIx_SR & FlagName){
		return FLAG_SET;
	}
	return FLAG_RESET;
}

/*
 * @fn					- SPI_Enable
 *
 * @brief				- enable the SPI interface
 *
 * @param[in]			- pSPIx adress of the given SPI
 * @param[in]			- EN_OR_DIS status to achieve (ENABLE/DISABLE)
 *
 * @return				- void
 */
void SPI_Enable (SPI_RegDef_t *pSPIx, uint8_t EN_OR_DIS){

	if(EN_OR_DIS == ENABLE){
		pSPIx->SPIx_CR1 |= (1 << SPI_CR1_SPE);
	}else{
		pSPIx->SPIx_CR1 &= ~(1 << SPI_CR1_SPE);
	}

}

void SPI_SSIConfig(SPI_RegDef_t *pSPIx, uint8_t ENORDIS){
	if(ENORDIS == ENABLE){
		pSPIx->SPIx_CR1 |= (1<< SPI_CR1_SSI);
	}else{
		pSPIx->SPIx_CR1 &= ~(1<< SPI_CR1_SSI);
	}
}

void SPI_SSOEConfig(SPI_RegDef_t *pSPIx, uint8_t ENORDIS){
	if(ENORDIS == ENABLE){
		pSPIx->SPIx_CR2 |= (1<< SPI_CR2_SSOE);
	}else{
		pSPIx->SPIx_CR1 &= ~(1<< SPI_CR2_SSOE);
	}
}

/*
 * @fn					-
 *
 * @brief				-
 *
 * @param[in]			-
 * @param[in]			-
 *
 * @return				-
 * @Note				- THIS IS BLOCKING MODE call
 */
void SPI_SendData(SPI_RegDef_t *pSPIx, uint8_t *pTxBuffer, uint32_t Len){

	//THIS IS BLOCKING MODE == UNTILL LEN BYTES WILL BE TRANSFERED THE MICROCONTROLER IS BLOCKED
	while(Len > 0) {
		//1. wait until TXE is set
		while(SPI_GetFlagStatus(pSPIx, SPI_TXE_FLAG) == FLAG_RESET);
		if( ((pSPIx->SPIx_CR2 >> SPI_CR2_DS) & 0xFUL) == (SPI_DFF_16BITS)  ){
			// 16bit mode

			pSPIx->SPIx_DR = *((uint16_t*)pTxBuffer);
			Len--;
			Len--;
			(uint16_t*)pTxBuffer++;

		}else if( ((pSPIx->SPIx_CR2 >> SPI_CR2_DS) & 0xFUL) == (SPI_DFF_8BITS)  ){
			// 8 bit mode
			*((__vo uint8_t*)&pSPIx->SPIx_DR) = *(pTxBuffer);
			Len--;
			pTxBuffer++;

		}
	}
}

/*
 * @fn					-
 *
 * @brief				-
 *
 * @param[in]			-
 * @param[in]			-
 *
 * @return				-
 */
void SPI_ReceiveData(SPI_RegDef_t *pSPIx, uint8_t *pRxBuffer, uint32_t Len){

	while(Len > 0) {
		//1. wait untill RXNE is set
		while(SPI_GetFlagStatus(pSPIx, SPI_RXNE_FLAG) == (uint8_t) FLAG_RESET);

		//2. check the DFF bit in CR1
		if( ((pSPIx->SPIx_CR2 >> SPI_CR2_DS) & 0xFUL) == (SPI_DFF_16BITS)  ){
			//16bit mode
			//1. Load the data from DR RXbuffer
			*((uint16_t*)pRxBuffer) = pSPIx->SPIx_DR;
			Len--;
			Len--;
			(uint16_t*)pRxBuffer++;

		}else if( ((pSPIx->SPIx_CR2 >> SPI_CR2_DS) & 0xFUL) == (SPI_DFF_8BITS) ){
			//8 bit mode
			*(pRxBuffer) = pSPIx->SPIx_DR;
			Len--;
			pRxBuffer++;
		}
	}
}


/*
 * @fn					- SPI_IRQITConfig
 *
 * @brief				- function turn on/off the NVIC interrupts
 *
 * @param[in]			-
 * @param[in]			-
 *
 * @return				-
 */
void SPI_IRQITConfig(uint8_t IRQNumber, uint8_t EnorDi){
	if(EnorDi == ENABLE){
			if(IRQNumber <=31){
				//program ISER0 register
				*NVIC_ISER0 |= (1 << IRQNumber);
			}else if(IRQNumber > 31 && IRQNumber < 64){
				//program ISER1 register
				*NVIC_ISER1 |= (1 << IRQNumber % 32);
			}else if(IRQNumber >= 64 && IRQNumber < 96){
				//program ISER2 register
				*NVIC_ISER3 |= (1 << IRQNumber % 64);
			}
		}else{
			if(IRQNumber <=31){
				//program ICER0 register
				*NVIC_ICER0 |= (1 << IRQNumber);
			}else if(IRQNumber > 31 && IRQNumber < 64){
				//program ICER1 register
				*NVIC_ICER1 |= (1 << IRQNumber % 32);
			}else if(IRQNumber >= 64 && IRQNumber < 96){
				//program ICER2 register
				*NVIC_ICER3 |= (1 << IRQNumber % 64);
			}
		}
}

/*
 * @fn					- SPI_ReceiveData_IT
 *
 * @brief				- function to receive data in IT mode
 *
 * @param[in]			-
 * @param[in]			-
 *
 * @return				-
 */
uint8_t SPI_ReceiveData_IT(SPI_Handle_t *pSPI_handle, uint8_t *pRxBuffer, uint32_t Len){

	uint8_t state = pSPI_handle->RxState;

	if(state != SPI_BUSY_IN_RX){
		//1. SAVE THE TX BUFFER ADDRESS AND LEN INFORMATION IN SOME GLOBAL VARIABLES
		pSPI_handle->pRxBuffer = pRxBuffer;
		pSPI_handle->RxLen = Len;

		//2. MARK THE SPI STATE AS BUSY IN TRANSMISSION SO THAT NO OTHER CODE CAN
		//   TAKE OVER SAME SPI PERIPHERAL UNTIL TRANSMISSION IS OVER
		pSPI_handle->RxState = SPI_BUSY_IN_RX;

		//3. ENABLE THE TXEIE CONTROL BIT TO GET INTERRUPT WHENEVER TXE FLAG IS SET IN SR
		pSPI_handle->pSPIx->SPIx_CR2 |= (1 << SPI_CR2_RXNEIE);

		//4. DATA TRANSMISSION WILL BE HANDLED DBY THE ISR CODE --> TODO
	}

	return state;
}

/*
 * @fn					- SPI_SendData_IT
 *
 * @brief				- function to receive data in IT mode
 *
 * @param[in]			-
 * @param[in]			-
 *
 * @return				-
 */
uint8_t SPI_SendData_IT(SPI_Handle_t *pSPI_handle, uint8_t *pTxBuffer, uint32_t Len){

	uint8_t state = pSPI_handle->TxState;

	if(state != SPI_BUSY_IN_TX){
		//1. SAVE THE TX BUFFER ADDRESS AND LEN INFORMATION IN SOME GLOBAL VARIABLES
		pSPI_handle->pTxBuffer = pTxBuffer;
		pSPI_handle->TxLen = Len;

		//2. MARK THE SPI STATE AS BUSY IN TRANSMISSION SO THAT NO OTHER CODE CAN
		//   TAKE OVER SAME SPI PERIPHERAL UNTIL TRANSMISSION IS OVER
		pSPI_handle->TxState = SPI_BUSY_IN_TX;

		//3. ENABLE THE TXEIE CONTROL BIT TO GET INTERRUPT WHENEVER TXE FLAG IS SET IN SR
		pSPI_handle->pSPIx->SPIx_CR2 |= (1 << SPI_CR2_TXEIE);

		//4. DATA TRANSMISSION WILL BE HANDLED BY THE ISR CODE --> TODO
	}

	return state;
}

/*
 * @fn					-
 *
 * @brief				-
 *
 * @param[in]			-
 * @param[in]			-
 *
 * @return				-
 */
void SPI_IRQPriorityConfig(uint8_t IRQNumber, uint32_t IRQPriority){
	//1. figure out the ipr reg
	uint8_t iprx = IRQNumber / 4;
	uint8_t iprx_section = IRQNumber % 4;

	uint8_t shift_ammount = (8 * iprx_section) + (8 - NO_PR_BITS_IMPLEMENTED);
	*(NVIC_PR_BASE_ADDR + iprx) |= ( IRQPriority << shift_ammount );
}

/*
 * @fn					-
 *
 * @brief				-
 *
 * @param[in]			-
 * @param[in]			-
 *
 * @return				-
 */
void SPI_IRQHandling(SPI_Handle_t *pHandle){

	uint8_t temp1, temp2;

	//checks for TXE
	temp1 = pHandle->pSPIx->SPIx_SR & (1 << SPI_SR_TXE);
	temp2 = pHandle->pSPIx->SPIx_CR2 & (1 << SPI_CR2_TXEIE);

	if(temp1 && temp2){
		SPI_txe_IT_handle(pHandle);
	}

	//checks for RXE
	temp1 = pHandle->pSPIx->SPIx_SR & (1 << SPI_SR_RXNE);
	temp2 = pHandle->pSPIx->SPIx_CR2 & (1 << SPI_CR2_RXNEIE);

	if(temp1 && temp2){
		SPI_rxe_IT_handle(pHandle);
	}

	//checks for OVR flag
	temp1 = pHandle->pSPIx->SPIx_SR & (1 << SPI_SR_OVR);
	temp2 = pHandle->pSPIx->SPIx_CR2 & (1 << SPI_CR2_ERRIE);

	if(temp1 && temp2){
		SPI_ovr_IT_handle(pHandle);
	}
}

static void SPI_txe_IT_handle(SPI_Handle_t * pSPI_Handler){
	if( ((pSPI_Handler->pSPIx->SPIx_CR2 >> SPI_CR2_DS) & 0xFUL) == (SPI_DFF_16BITS)  ){

		// 16bit mode
		pSPI_Handler->pSPIx->SPIx_DR = *((uint16_t*)pSPI_Handler->pTxBuffer);
		pSPI_Handler->TxLen--;
		pSPI_Handler->TxLen--;
		(uint16_t*)pSPI_Handler->pTxBuffer++;

	}else if( ((pSPI_Handler->pSPIx->SPIx_CR2 >> SPI_CR2_DS) & 0xFUL) == (SPI_DFF_8BITS)  ){
		// 8 bit mode
		*((__vo uint8_t*)&pSPI_Handler->pSPIx->SPIx_DR) = *(pSPI_Handler->pTxBuffer);
		pSPI_Handler->TxLen--;
		pSPI_Handler->pTxBuffer++;

	}

	if( !pSPI_Handler->TxLen){
		//TXLen is zero
		//CLOSE SPI TRANSMISSION

		SPI_CloseTransmission(pSPI_Handler);
		SPI_ApplicationEventCallback(pSPI_Handler, SPI_EVENT_TX_CMPLT);
	}
}

static void SPI_rxe_IT_handle(SPI_Handle_t * pSPI_Handler){
	//2. check the DFF bit in CR1
	if( ((pSPI_Handler->pSPIx->SPIx_CR2 >> SPI_CR2_DS) & 0xFUL) == (SPI_DFF_16BITS)  ){
		//16bit mode
		//1. Load the data from DR RXbuffer
		*((uint16_t*)pSPI_Handler->pRxBuffer) = pSPI_Handler->pSPIx->SPIx_DR;
		pSPI_Handler->RxLen--;
		pSPI_Handler->RxLen--;
		(uint16_t*)pSPI_Handler->pRxBuffer++;

	}else if( ((pSPI_Handler->pSPIx->SPIx_CR2 >> SPI_CR2_DS) & 0xFUL) == (SPI_DFF_8BITS) ){
		//8 bit mode
		*(pSPI_Handler->pRxBuffer) = pSPI_Handler->pSPIx->SPIx_DR;
		pSPI_Handler->RxLen--;
		pSPI_Handler->pRxBuffer++;
	}


	if( !pSPI_Handler->RxLen){
		//RXLen is zero
		//CLOSE SPI TRANSMISSION

		SPI_CloseReception(pSPI_Handler);
		SPI_ApplicationEventCallback(pSPI_Handler, SPI_EVENT_RX_CMPLT);
	}
}

static void SPI_ovr_IT_handle(SPI_Handle_t * pSPI_Handler){

	uint8_t temp;
	if(pSPI_Handler->TxState != SPI_BUSY_IN_TX){
		temp = pSPI_Handler->pSPIx->SPIx_DR;
		temp = pSPI_Handler->pSPIx->SPIx_SR;
	}
	(void)temp;

	SPI_ApplicationEventCallback(pSPI_Handler, SPI_EVENT_OVR_ERR);
}

void SPI_CloseTransmission(SPI_Handle_t* pSPI_Handler){
	//clear the IT setting
	pSPI_Handler->pSPIx->SPIx_CR2 &= ~(1 << SPI_CR2_TXEIE);
	pSPI_Handler->pTxBuffer = NULL;
	pSPI_Handler->TxLen = 0;
	pSPI_Handler->TxState = SPI_READY;
}

void SPI_CloseReception(SPI_Handle_t* pSPI_Handler){
	//clear the IT setting
	pSPI_Handler->pSPIx->SPIx_CR2 &= ~(1 << SPI_CR2_RXNEIE);
	pSPI_Handler->pRxBuffer = NULL;
	pSPI_Handler->RxLen = 0;
	pSPI_Handler->RxState = SPI_READY;
}

void SPI_ClearOVRFlag(SPI_RegDef_t * pSPIx){
	uint8_t temp;
	temp = pSPIx->SPIx_DR;
	temp = pSPIx->SPIx_SR;
	(void)temp;
}

__weak void SPI_ApplicationEventCallback(SPI_Handle_t* pSPI_Handler, uint8_t AppEv){
	// this is a weak implementation. The application may override this function.

}
