/*
 * DS3231.c
 *
 *  Created on: Dec 21, 2023
 *      Author: maciej
 */

#include "DS3231.h"



DS3231_Time_t DS3231_get_time(I2C_HandleTypeDef * I2C_PERI)
{
	DS3231_Time_t tmp_data = {0, 0, 0};
	uint8_t data_to_send = 0;
	uint8_t BUFFER [200];


	/// GET SECONDS
	data_to_send = 0x00;

	HAL_I2C_Master_Transmit(I2C_PERI, 0b11010000, &data_to_send , 1, 1000);
	HAL_I2C_Master_Receive(I2C_PERI, 0b11010000, BUFFER, 1, 100);

	tmp_data.time_sec = (BUFFER[0] & 0xF) + 10*((BUFFER[0] >> 4) & 0x7);

	/// GET MINUTES
	data_to_send = 0x01;

	HAL_I2C_Master_Transmit(I2C_PERI, 0b11010000, &data_to_send , 1, 1000);
	HAL_I2C_Master_Receive(I2C_PERI, 0b11010000, BUFFER, 1, 100);

	tmp_data.time_min = (BUFFER[0] & 0xF) + 10*((BUFFER[0] >> 4) & 0x7);

	/// GET HOURS
	data_to_send = 0x02;

	HAL_I2C_Master_Transmit(I2C_PERI, 0b11010000, &data_to_send , 1, 1000);
	HAL_I2C_Master_Receive(I2C_PERI, 0b11010000, BUFFER, 1, 100);

	tmp_data.time_hr = (BUFFER[0] & 0xF) + 10*((BUFFER[0] >> 4) & 0x1);

	return tmp_data;
}
