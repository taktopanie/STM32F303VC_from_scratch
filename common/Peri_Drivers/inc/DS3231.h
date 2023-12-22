/*
 * DS3231.h
 *
 *  Created on: Dec 21, 2023
 *      Author: maciej
 */

#ifndef PERI_DRIVERS_INC_DS3231_H_
#define PERI_DRIVERS_INC_DS3231_H_

#include "stm32f3xx_hal.h"


typedef struct{
	uint8_t time_hr;
	uint8_t time_min;
	uint8_t time_sec;

}DS3231_Time_t;


/*
 * Function prototypes
 */

/*
 * DS3231_get_time - function which returns DS3231_Time_t format time
 */
DS3231_Time_t DS3231_get_time(I2C_HandleTypeDef * I2C_PERI);

#endif /* PERI_DRIVERS_INC_DS3231_H_ */
