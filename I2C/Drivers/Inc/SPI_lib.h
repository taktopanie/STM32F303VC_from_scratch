/*
 * SPI_lib.h
 *
 *  Created on: Dec 27, 2022
 *      Author: root
 */

#ifndef INC_SPI_LIB_H_
#define INC_SPI_LIB_H_

#include <stdint.h>
#include <stm32f3xx.h>

typedef  struct{
	uint8_t SPI_DeviceMode;
	uint8_t SPI_BusConfig;
	uint8_t SPI_SclkSpeed;
	uint8_t SPI_DFF;
	uint8_t SPI_CPOL;
	uint8_t SPI_CPHA;
	uint8_t SPI_SSM;

}SPI_Config_t;

typedef struct{
	SPI_RegDef_t		*pSPIx;
	SPI_Config_t		SPIConfig;
	uint8_t 			*pTxBuffer;				/* !< To store the app. Tx buffer address 	> */
	uint8_t				*pRxBuffer;				/* !< To store the app. Rx buffer address 	> */
	uint32_t			TxLen;					/* !< To store Tx len 						> */
	uint32_t			RxLen;					/* !< To store Rx len 						> */
	uint8_t				TxState;				/* !< To store Tx state 					> */
	uint8_t				RxState;				/* !< To store Rx state 					> */
}SPI_Handle_t;

/*
 * @SPI_Application_States
 */
#define SPI_READY								0
#define SPI_BUSY_IN_RX							1
#define SPI_BUSY_IN_TX							2

/*
 * Possible SPI application events
 */
#define SPI_EVENT_TX_CMPLT 						1
#define SPI_EVENT_RX_CMPLT 						2
#define SPI_EVENT_OVR_ERR 						3
#define SPI_EVENT_CRC_ERR						4

/*
 * @SPI_DeviceModes
 */
#define SPI_DEVICE_MODE_MASTER					1
#define SPI_DEVICE_MODE_SLAVE					0

/*
 * @SPI_BusConfig
 */
#define SPI_BUS_CONFIG_FD						1
#define SPI_BUS_CONFIG_HD						2
#define SPI_BUS_CONFIG_SIMPLEX_RXONLY			3

/*
 * @spi_SclkSpeed
 */
#define SPI_SCLK_SPEED_DIV2						0
#define SPI_SCLK_SPEED_DIV4						1
#define SPI_SCLK_SPEED_DIV8						2
#define SPI_SCLK_SPEED_DIV16					3
#define SPI_SCLK_SPEED_DIV32					4
#define SPI_SCLK_SPEED_DIV64					5
#define SPI_SCLK_SPEED_DIV128					6
#define SPI_SCLK_SPEED_DIV256					7

/*
 * @SPI_DFF
 */
#define SPI_DFF_4BITS							3
#define SPI_DFF_5BITS							4
#define SPI_DFF_6BITS							5
#define SPI_DFF_7BITS							6
#define SPI_DFF_8BITS							7
#define SPI_DFF_9BITS							8
#define SPI_DFF_10BITS							9
#define SPI_DFF_11BITS							10
#define SPI_DFF_12BITS							11
#define SPI_DFF_13BITS							12
#define SPI_DFF_14BITS							13
#define SPI_DFF_15BITS							14
#define SPI_DFF_16BITS							15

/*
 * @CPOL
 */
#define SPI_CPOL_HIGH							1
#define SPI_CPOL_LOW							0

/*
 * @CPHA
 */
#define SPI_CPHA_HIGH							1
#define SPI_CPHA_LOW							0

/*
 * @SPI_SSM
 */
#define SPI_SSM_EN								1
#define SPI_SSM_DI								0



/***************************************************************************
 * 					APIs Supported by this driver
 *
 ***************************************************************************
 */

/*
 * Peripheral Clock Setup
 */
void SPI_PeriClockControl(SPI_RegDef_t * pSPI, uint8_t En);

/*
 * Init and De-init
 */
void SPI_Init(SPI_Handle_t * pSPI_Handler);
void SPI_DeInit(SPI_RegDef_t * pSPI_Reg);

/*
 * Data Send and Receive
 */
void SPI_SendData(SPI_RegDef_t *pSPIx, uint8_t *pTxBuffer, uint32_t Len);
void SPI_ReceiveData(SPI_RegDef_t *pSPIx, uint8_t *pRxBuffer, uint32_t Len);

//interrupt mode
uint8_t SPI_SendData_IT(SPI_Handle_t *pSPI_handle, uint8_t *pTxBuffer, uint32_t Len);
uint8_t SPI_ReceiveData_IT(SPI_Handle_t *pSPI_handle, uint8_t *pRxBuffer, uint32_t Len);

/*
 * IRQ Configuration and ISR handling
 */
void SPI_IRQITConfig(uint8_t IRQNumber, uint8_t EnorDi);
void SPI_IRQPriorityConfig(uint8_t IRQNumber, uint32_t IRQPriority);
void SPI_IRQHandling(SPI_Handle_t *pHandle);

/*
 * OTHER API
 */

void SPI_Enable (SPI_RegDef_t *pSPIx, uint8_t EN_OR_DIS);
void SPI_SSIConfig(SPI_RegDef_t *pSPIx, uint8_t ENORDIS);
void SPI_SSOEConfig(SPI_RegDef_t *pSPIx, uint8_t ENORDIS);
uint8_t SPI_GetFlagStatus(SPI_RegDef_t *pSPIx, uint32_t FlagName);

void SPI_ClearOVRFlag(SPI_RegDef_t * pSPIx);
void SPI_CloseTransmission(SPI_Handle_t* pSPIHandle);
void SPI_CloseReception(SPI_Handle_t* pSPIHandle);

/*
 * Application callback
 */
void SPI_ApplicationEventCallback(SPI_Handle_t* pSPI_Handler, uint8_t AppEv);

#endif /* INC_SPI_LIB_H_ */
