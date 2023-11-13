#include <stdint.h>
#include <stm32f3xx.h>


/*
 * Systick function waits given @time_ms miliseconds
 */
void systick (int time_ms){
	typedef struct
	{
		volatile uint32_t CSR;  			/* < SysTick Control and Status Register */
		volatile uint32_t RVR;  			/* < SysTick Reload Value Register */
		volatile uint32_t CVR; 				/* < SysTick Current Value Register */
		volatile uint32_t CALIB;    		/* < SysTick Calibration Value Register */

	}SysTick_RegDef_t;

	//WSKAZNIK NA SYSTICK CSR
	SysTick_RegDef_t *pSysTick= ((SysTick_RegDef_t*)0xE000E010UL);

	pSysTick->RVR = 8000; 					/* < Sets the reload value to 8000 which means 1 overflow per milisecond */

	pSysTick->CVR= 0;						/* < Clears the SysTick current value register */

	pSysTick->CSR = (1 << 0) | (1 << 2);	/* (1 << 0) - Turn on the Counter
											   (1 << 2) - SysTick uses the processor clock
											   SEE: armv7n_arm.pdf */
	//WAIT
	for(int i=time_ms; i > 0; i--)
	{
		while(!(pSysTick->CSR & (1 << 16)));
	}
	//Disable SysTick counter in the Control Register
	pSysTick->CSR=0;
}
