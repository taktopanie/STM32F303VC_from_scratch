/*
 * DS3231.c
 *
 *  Created on: Dec 21, 2023
 *      Author: maciej
 */

#include "DS3231.h"

/*
 * function converting decimal number to hexadecimal
 */

uint8_t _dec_2_hex(uint8_t dec)
{
	return( (dec / 10) << 4 | (dec % 10));
}

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

	tmp_data.time_hr = (BUFFER[0] & 0xF) + 10*((BUFFER[0] >> 4) & 0x3);

	return tmp_data;
}

uint8_t DS3231_set_time(I2C_HandleTypeDef * I2C_PERI, DS3231_Time_t TIME){
		uint8_t data_to_send [2];

		//SET SECONDS
		//address
		data_to_send[0] = 0x0;
		//data
		data_to_send[1] = _dec_2_hex(TIME.time_sec) & 0x7F;
		HAL_I2C_Master_Transmit(I2C_PERI, 0b11010001, data_to_send , 2, 1000);

		//SET MINUTES
		//address
		data_to_send[0] = 0x1;
		//data
		data_to_send[1] = _dec_2_hex(TIME.time_min) & 0x7F;
		HAL_I2C_Master_Transmit(I2C_PERI, 0b11010001, data_to_send , 2, 1000);

		//SET HOURS
		//address
		data_to_send[0] = 0x2;
		//data
		data_to_send[1] = _dec_2_hex(TIME.time_hr) & 0x3F;

		HAL_I2C_Master_Transmit(I2C_PERI, 0b11010001, data_to_send , 2, 1000);


	return 0;
}

void DS3231_set_alarm(I2C_HandleTypeDef * I2C_PERI , uint8_t Alarm_No){

	uint8_t data_to_send [2];

	//TODO rest options == NOW ONLY ONCE PER SECOND
	if(Alarm_No == ALARM_1)
	{

		//address A1M1
		data_to_send[0] = 0x7;
		//data
		data_to_send[1] = 0x80;
		HAL_I2C_Master_Transmit(I2C_PERI, 0b11010001, data_to_send , 2, 1000);

		//address A1M2
		data_to_send[0] = 0x8;
		//data
		data_to_send[1] = 0x80;
		HAL_I2C_Master_Transmit(I2C_PERI, 0b11010001, data_to_send , 2, 1000);

		//address A1M3
		data_to_send[0] = 0x9;
		//data
		data_to_send[1] = 0x80;
		HAL_I2C_Master_Transmit(I2C_PERI, 0b11010001, data_to_send , 2, 1000);

		//address A1M4
		data_to_send[0] = 0xA;
		//data
		data_to_send[1] = 0x80;
		HAL_I2C_Master_Transmit(I2C_PERI, 0b11010001, data_to_send , 2, 1000);


	}else if(Alarm_No == ALARM_2)
	{

	}
}

uint8_t DS3231_get_alarm(I2C_HandleTypeDef * I2C_PERI , uint8_t Alarm_No)
{
	uint8_t BUFFER;

	//Status register address 0xF
	uint8_t data_to_send = 0xF;

	HAL_I2C_Master_Transmit(I2C_PERI, 0b11010000, &data_to_send , 1, 1000);
	HAL_I2C_Master_Receive(I2C_PERI, 0b11010000, &BUFFER, 1, 100);

	return(BUFFER & Alarm_No);

}

void DS3231_clear_alarm(I2C_HandleTypeDef * I2C_PERI , uint8_t Alarm_No)
{
	uint8_t data_to_send [2];
	//address of the status register
	data_to_send[0] = 0xF;

	//Clear all the flags
	data_to_send[1] = 0x00;

	HAL_I2C_Master_Transmit(I2C_PERI, 0b11010001, &data_to_send[0] , 2, 1000);
}

/*TODO FUNCTION TO WRITE DATA IN DS3231
 *
 *
 *		data_to_send[0] = address;
 *		data_to_send[1] = data;
 *		HAL_I2C_Master_Transmit(I2C_PERI, 0b11010001, data_to_send , 2, 1000);
 *
*/
