/*
 * DS3231.h
 *
 *  Created on: Dec 21, 2023
 *      Author: maciej
 */

#ifndef PERI_DRIVERS_INC_DS3231_H_
#define PERI_DRIVERS_INC_DS3231_H_

#include "stm32f3xx_hal.h"

/*
 * @ALARM_NUMBERS
 */
#define ALARM_1			1
#define ALARM_2			2

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

/*
 * DS3231_set_time - function which sets RTC by DS3231_Time_t format time
 */
uint8_t DS3231_set_time(I2C_HandleTypeDef * I2C_PERI, DS3231_Time_t TIME);

/*
 * DS3231_get_alarm - function which checks given Alarm IRQ number
 *
 * # params:
 * 	I2C_PERI - pointer to I2C peripheral
 * 	Alarm_No - number of the given alarm 		SEE @ALARM_NUMBERS
 *
 * # returns:
 * 	status of the alarm IRQ bit
 */
uint8_t DS3231_get_alarm(I2C_HandleTypeDef * I2C_PERI, uint8_t Alarm_No);

void DS3231_set_alarm(I2C_HandleTypeDef * I2C_PERI , uint8_t Alarm_No);
void DS3231_clear_alarm(I2C_HandleTypeDef * I2C_PERI , uint8_t Alarm_No);

#endif /* PERI_DRIVERS_INC_DS3231_H_ */
