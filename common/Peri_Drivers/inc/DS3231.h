/*
 * DS3231.h
 *
 *  Created on: Dec 21, 2023
 *      Author: maciej
 */

#ifndef PERI_DRIVERS_INC_DS3231_H_
#define PERI_DRIVERS_INC_DS3231_H_

#include "stm32f3xx_hal.h"


#define DS3231_address 			0b11010001

/*
 * @ALARM_NUMBERS
 */
#define ALARM_1					1
#define ALARM_2					2



/*
 * DS3231 registers
 */

#define DS3231_seconds_addr		0x0
#define DS3231_minutes_addr		0x1
#define DS3231_hours_addr		0x2
#define DS3231_days_addr		0x3
#define DS3231_date_addr		0x4
#define DS3231_month_addr		0x5
#define DS3231_year_addr		0x6
#define DS3231_alarm1m1_addr	0x7
#define DS3231_alarm1m2_addr	0x8
#define DS3231_alarm1m3_addr	0x9
#define DS3231_alarm1m4_addr	0xA
#define DS3231_alarm2m2_addr	0xB
#define DS3231_alarm2m3_addr	0xC
#define DS3231_alarm2m4_addr	0xD

#define DS3231_control_addr		0xE
#define DS3231_status_addr		0xF
#define DS3231_aging_addr		0x10
#define DS3231_msbTemp_addr		0x11
#define DS3231_lsbTemp_addr		0x12


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

void DS3231_data_write(I2C_HandleTypeDef * I2C_PERI, uint8_t peri_address, uint8_t mem_address, uint8_t* data_to_send, uint8_t data_length);
void DS3231_data_read(I2C_HandleTypeDef * I2C_PERI, uint8_t peri_address, uint8_t mem_address, uint8_t* read_buffor, uint8_t data_length);

#endif /* PERI_DRIVERS_INC_DS3231_H_ */
