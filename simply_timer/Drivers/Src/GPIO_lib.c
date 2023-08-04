#include <stdint.h>
#include <GPIO_lib.h>


/*
 * @fn					- PeriClockControl
 *
 * @brief				- Function to Initiate GPIO port clock
 *
 * @param[in]			- pGPIO_reg 			- register address, search for @GPIOADDRESS
 * @param[in]			- Clock_State			- value of the clock status to send, search for @CLOCK_STATE
 *
 * @return				- void
 */
void PeriClockControl(GPIO_RegDef_t * pGPIO, uint8_t Clock_State){
	if( Clock_State == CLOCK_ENABLE){

		if (pGPIO == GPIOA){
			GPIOA_PCLK_EN();
		}else if (pGPIO == GPIOB){
			GPIOB_PCLK_EN();
		}else if (pGPIO == GPIOC){
			GPIOC_PCLK_EN();
		}else if (pGPIO == GPIOD){
			GPIOD_PCLK_EN();
		}else if (pGPIO == GPIOE){
			GPIOE_PCLK_EN();
		}

	}else{
		if (pGPIO == GPIOA){
			GPIOA_PCLK_DIS();
		}else if (pGPIO == GPIOB){
			GPIOB_PCLK_DIS();
		}else if (pGPIO == GPIOC){
			GPIOC_PCLK_DIS();
		}else if (pGPIO == GPIOD){
			GPIOD_PCLK_DIS();
		}else if (pGPIO == GPIOE){
			GPIOE_PCLK_DIS();
		}
	}
}


/*
 * @fn					- GPIO_Init
 *
 * @brief				- Function to Initiate GPIO port
 *
 * @param[in]			- @pGPIO_Handler - structure contains register address, and settings
 *
 * @return				- void
 */
void GPIO_Init(GPIO_Handle_t * pGPIO_Handler){

	//temporary register
	uint32_t wsk = 0;

	//Turn on the clock
	PeriClockControl(pGPIO_Handler->GPIO_Regdef , CLOCK_ENABLE);

	// 1 - Configure the mode of pin
	if(pGPIO_Handler->GPIO_config.Pin_Mode < GPIO_MODE_ANALOG){
		wsk = (pGPIO_Handler->GPIO_config.Pin_Mode << (2 * pGPIO_Handler->GPIO_config.Pin_Number));
		pGPIO_Handler->GPIO_Regdef->MODER  &= ~(0x3 << (2 * pGPIO_Handler->GPIO_config.Pin_Number));
		pGPIO_Handler->GPIO_Regdef->MODER |= wsk;

	}else{
		/*
		 * Interrupt modes
		 */

		//1.1 Configure trigger edge
		//falling trigger
		if(pGPIO_Handler->GPIO_config.Pin_Mode == GPIO_MODE_IT_FT){
			EXTI->FTSR1 |= (1 << pGPIO_Handler->GPIO_config.Pin_Number);
			EXTI->RTSR1 &= ~(1 << pGPIO_Handler->GPIO_config.Pin_Number);
		//rising trigger
		}else if(pGPIO_Handler->GPIO_config.Pin_Mode == GPIO_MODE_IT_RT){
			EXTI->FTSR1 &= ~(1 << pGPIO_Handler->GPIO_config.Pin_Number);
			EXTI->RTSR1 |= (1 << pGPIO_Handler->GPIO_config.Pin_Number);
		//rising & falling edge
		}else if(pGPIO_Handler->GPIO_config.Pin_Mode == GPIO_MODE_IT_FRT){
			EXTI->FTSR1 |= (1 << pGPIO_Handler->GPIO_config.Pin_Number);
			EXTI->RTSR1 |= (1 << pGPIO_Handler->GPIO_config.Pin_Number);
		}

		//1.2 Configuring the GPIO port selection in SYSCFG_EXtICR == MAPPING gpios is done by SYSCFG
		SYSCFG_PCLK_EN();
		uint8_t val_1 = pGPIO_Handler->GPIO_config.Pin_Number / 4;
		uint8_t val_2 = pGPIO_Handler->GPIO_config.Pin_Number % 4;
		uint8_t portcode = GPIO_BASEADDR_TO_CODE(pGPIO_Handler->GPIO_Regdef);

		SYSCFG->EXTICR[val_1] = portcode << ( val_2 << 4);

		//1.2 enable the exti interrupt delivery using IMR
			EXTI->IMR1 |= (1<< pGPIO_Handler->GPIO_config.Pin_Number);
	}

	// 2 - Configure the speed
	wsk = (pGPIO_Handler->GPIO_config.Pin_Speed << (2 * pGPIO_Handler->GPIO_config.Pin_Number));
	pGPIO_Handler->GPIO_Regdef->OSPEEDR &= ~(0x3 << (2 * pGPIO_Handler->GPIO_config.Pin_Number));		/* < CLEARING */
	pGPIO_Handler->GPIO_Regdef->OSPEEDR |= wsk;

	// 3 -  Configure the Pin_Output_Type
	wsk = (pGPIO_Handler->GPIO_config.Pin_Output_Type << (pGPIO_Handler->GPIO_config.Pin_Number));
	pGPIO_Handler->GPIO_Regdef->OTYPER &= ~(1<<(pGPIO_Handler->GPIO_config.Pin_Number));				/* < CLEARING */
	pGPIO_Handler->GPIO_Regdef->OTYPER |= wsk;

	// 4 -  Configure the Pin_pull
	wsk = (pGPIO_Handler->GPIO_config.Pin_Pull << (2 * pGPIO_Handler->GPIO_config.Pin_Number));
	pGPIO_Handler->GPIO_Regdef->PUPDR &= ~(0x3 << (2 * pGPIO_Handler->GPIO_config.Pin_Number));			/* < CLEARING */
	pGPIO_Handler->GPIO_Regdef->PUPDR |= wsk;


	// 5 - Configure alternate function
	if(pGPIO_Handler->GPIO_config.Pin_Mode == GPIO_MODE_ALTERNATE){
		uint8_t tmp1 = (pGPIO_Handler->GPIO_config.Pin_Number)/8;
		uint8_t tmp2 = (pGPIO_Handler->GPIO_config.Pin_Number % 8);
		pGPIO_Handler->GPIO_Regdef->AF[tmp1] &= ~(0xF << (4 * tmp2));
		pGPIO_Handler->GPIO_Regdef->AF[tmp1] |= (pGPIO_Handler->GPIO_config.Pin_alt_func << (4 * tmp2));
	}
}

/*
 * @fn					- GPIO_DeInit
 *
 * @brief				- Function to deinit GPIO port (reset to default values)
 *
 * @param[in]			- @pGPIO_Reg - pointer to GPIO register address
 *
 * @return				- void
 */
void GPIO_DeInit(GPIO_RegDef_t * pGPIO_Reg){
	if (pGPIO_Reg == GPIOA){
		GPIOA_DEINIT();
	}else if (pGPIO_Reg == GPIOB){
		GPIOB_DEINIT();
	}else if (pGPIO_Reg == GPIOC){
		GPIOC_DEINIT();
	}else if (pGPIO_Reg == GPIOD){
		GPIOD_DEINIT();
	}else if (pGPIO_Reg == GPIOE){
		GPIOE_DEINIT();
	}
}

/*
 * @fn					- GPIO_ReadPin
 *
 * @brief				- Function to read the value of single PIN
 *
 * @param[in]			- @pGPIO_reg - register address, search for @GPIOADDRESS
 * @param[in]			- @PIN_Number - number of pin, search for @PIN_NUMBERS
 *
 * @return				- value of the single pin
 */
uint8_t GPIO_ReadPin(GPIO_RegDef_t * pGPIO_Reg, uint8_t PIN_Number){
	return((pGPIO_Reg->IDR >> PIN_Number) & 0x1UL);
}

/*
 * @fn					- GPIO_ReadPort
 *
 * @brief				- Function to read the value of whole GPIO port
 *
 * @param[in]			- @pGPIO_reg - register address, search for @GPIOADDRESS
 *
 * @return				- value of the whole PORT
 */
uint16_t GPIO_ReadPort(GPIO_RegDef_t * pGPIO_Reg){
	return((pGPIO_Reg->IDR) & 0xFFFFUL);
}

/*
 * @fn					-
 *
 * @brief				- Function to SET/RESET all ports
 *
 * @param[in]			- @pGPIO_reg 	- register address, search for @GPIOADDRESS
 * @param[in]			- @Value 		- value of the pin to set up, search for @GPIO_PIN_States
 *
 * @return				- void
 */
void GPIO_WritePort(GPIO_RegDef_t * pGPIO_Reg, uint8_t Value){

	if(Value == GPIO_PIN_SET){
		pGPIO_Reg->ODR |= (0xFFFF);
	}else{
		pGPIO_Reg->ODR &= ~(0x0000);
	}
}

/*
 * @fn					- GPIO_WritePin
 *
 * @brief				- Function to SET/RESET single PIN
 *
 * @param[in]			- @pGPIO_reg 			- register address, search for @GPIOADDRESS
 * @param[in]			- @PIN_Number 			- number of pin, search for @PIN_NUMBERS
 * @param[in]			- @Value 				- value of the pin to set up, search for @GPIO_PIN_States
 *
 * @return				- void
 */
void GPIO_WritePin(GPIO_RegDef_t * pGPIO_Reg, uint8_t PIN_Number, uint8_t Value){
	if(Value == GPIO_PIN_SET){
		pGPIO_Reg->ODR |= (1<< PIN_Number);
	}else{
		pGPIO_Reg->ODR &= ~(1<< PIN_Number);
	}
}

/*
 * @fn					- GPIO_TogglePin
 *
 * @brief				- Function to Toggle single PIN
 *
 * @param[in]			- @pGPIO_reg 	- register address, search for @GPIOADDRESS
 * @param[in]			- @PIN_Number 	- number of pin, search for @PIN_NUMBERS
 *
 * @return				- void
 */
void GPIO_TogglePin(GPIO_RegDef_t * pGPIO_Reg, uint8_t PIN_Number){
	pGPIO_Reg->ODR ^= (1<<PIN_Number);
}

/*
 * @fn					- GPIO_IRQITConfig
 *
 * @brief				- set NVIC interrupt on processor side
 *
 * @param[in]			- @IRQNumber		- vector of the priority. SEE @IRQ_IT_NUM
 * @param[in]			- @EnorDi			- enable/disable interrupt. SEE @STATES
 *
 * @return				- void
 */
void GPIO_IRQITConfig(uint8_t IRQNumber, uint8_t EnorDi){

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
 * @fn					- GPIO_IRQPriorityConfig
 *
 * @brief				- set NVIC priority on processor side
 *
 * @param[in]			- @IRQNumber		- vector of the priority. SEE @IRQ_IT_NUM
 * @param[in]			- @IRQPriority		- priority - number 0 - 255
 *
 * @return				- void
 */
/*
 * set NVIC priority on processor side
 */
void GPIO_IRQPriorityConfig(uint8_t IRQNumber, uint32_t IRQPriority){
	//1. figure out the ipr reg
	uint8_t iprx = IRQNumber / 4;
	uint8_t iprx_section = IRQNumber % 4;

	uint8_t shift_ammount = (8 * iprx_section) + (8 - NO_PR_BITS_IMPLEMENTED);
	*(NVIC_PR_BASE_ADDR + iprx) |= ( IRQPriority << shift_ammount );
}

/*
 * @fn					- GPIO_IRQHandling
 *
 * @brief				- Function of IRQ handler
 *
 * @param[in]			- @PinNumber - number of the pin which is configured as IT
 *
 * @return				- void
 */
void GPIO_IRQHandling(uint8_t PinNumber){
	//clear the exti pr register  corresponding to the pin number
	if(EXTI->PR1 & (1 << PinNumber)){
		//clear
		EXTI->PR1 |= (1 << PinNumber);
		//FUNCTION BODY
		//GPIO_TogglePin(GPIOE, GPIO_PIN_15);

	}


}
