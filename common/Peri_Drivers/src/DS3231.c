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
	uint8_t BUFFOR [200];


	/// GET SECONDS
	DS3231_data_read(I2C_PERI, DS3231_address, DS3231_seconds_addr, BUFFOR, 1);

	tmp_data.time_sec = (BUFFOR[0] & 0xF) + 10*((BUFFOR[0] >> 4) & 0x7);

	/// GET MINUTES
	DS3231_data_read(I2C_PERI, DS3231_address, DS3231_minutes_addr, BUFFOR, 1);

	tmp_data.time_min = (BUFFOR[0] & 0xF) + 10*((BUFFOR[0] >> 4) & 0x7);

	/// GET HOURS
	DS3231_data_read(I2C_PERI, DS3231_address, DS3231_hours_addr, BUFFOR, 1);

	tmp_data.time_hr = (BUFFOR[0] & 0xF) + 10*((BUFFOR[0] >> 4) & 0x3);

	return tmp_data;
}

uint8_t DS3231_set_time(I2C_HandleTypeDef * I2C_PERI, DS3231_Time_t TIME){
	uint8_t data_to_send;

	//SET SECONDS
	data_to_send = _dec_2_hex(TIME.time_sec) & 0x7F;
	DS3231_data_write(I2C_PERI, DS3231_address, DS3231_seconds_addr, &data_to_send , 1);

	//SET MINUTES
	data_to_send = _dec_2_hex(TIME.time_min) & 0x7F;
	DS3231_data_write(I2C_PERI, DS3231_address, DS3231_minutes_addr, &data_to_send , 1);

	//SET HOURS
	data_to_send = _dec_2_hex(TIME.time_hr) & 0x3F;
	DS3231_data_write(I2C_PERI, DS3231_address, DS3231_hours_addr, &data_to_send , 1);

	return 0;
}

void DS3231_set_alarm(I2C_HandleTypeDef * I2C_PERI , uint8_t Alarm_No){

	uint8_t data_to_send;

	//TODO rest options == NOW ONLY ONCE PER SECOND
	if(Alarm_No == ALARM_1)
	{
		data_to_send = 0x80;

		//address A1M1 = 0x7
		DS3231_data_write(I2C_PERI, DS3231_address, DS3231_alarm1m1_addr, &data_to_send , 1);

		data_to_send = 0x80;
		//address A1M2 = 0x8
		DS3231_data_write(I2C_PERI, DS3231_address, DS3231_alarm1m2_addr, &data_to_send , 1);

		data_to_send = 0x80;
		//address A1M3 = 0x9
		DS3231_data_write(I2C_PERI, DS3231_address, DS3231_alarm1m3_addr, &data_to_send , 1);

		data_to_send = 0x80;
		//address A1M4 = 0xA
		DS3231_data_write(I2C_PERI, DS3231_address, DS3231_alarm1m4_addr, &data_to_send , 1);


	}else if(Alarm_No == ALARM_2)
	{
		//TODO:
	}
}

uint8_t DS3231_get_alarm(I2C_HandleTypeDef * I2C_PERI , uint8_t Alarm_No)
{
	uint8_t BUFFOR;

	//Status register address 0xF
	DS3231_data_read(I2C_PERI, DS3231_address, DS3231_status_addr, &BUFFOR, 1);

	return(BUFFOR & Alarm_No);

}

void DS3231_clear_alarm(I2C_HandleTypeDef * I2C_PERI , uint8_t Alarm_No)
{
	//Clear all the flags
	uint8_t data_to_send = 0x0;

	DS3231_data_write(I2C_PERI, DS3231_address, 0xF, &data_to_send , 1);

	//HAL_I2C_Master_Transmit(I2C_PERI, 0b11010001, &data_to_send[0] , 2, 1000);
}

/*
 * DS3231_data_write - send the data to DS3231
 *
 * @params:
 * 	I2C_PERI				- BUS address pointer (I2C)
 * 	peri_address			- address of peripheral (device)
 * 	mem_address				- memory address
 * 	data_to_send			- pointer to data which will be send
 * 	data_length				- number of data which will be send
 *
 */
void DS3231_data_write(I2C_HandleTypeDef * I2C_PERI, uint8_t peri_address, uint8_t mem_address, uint8_t* data_to_send, uint8_t data_length)
{
	uint8_t data_buff[100];

	//first send memory address
	data_buff[0] = mem_address;

	//fill the buffor with data
	for(int i = 0; i < data_length; i++)
	{
		data_buff[i+1] = data_to_send[i];
	}

	//transmit the buffor
	HAL_I2C_Master_Transmit(I2C_PERI, peri_address, data_buff , (data_length + 1), 1000);
}

/*
 * DS3231_data_read - read the data from DS3231
 *
 * @params:
 * 	I2C_PERI				- BUS address pointer (I2C)
 * 	peri_address			- address of peripheral (device)
 * 	mem_address				- memory address
 * 	read_buffor				- buffor which will be refiled with the read data
 * 	data_length				- number of data which will be received
 *
 */
void DS3231_data_read(I2C_HandleTypeDef * I2C_PERI, uint8_t peri_address, uint8_t mem_address, uint8_t* read_buffor, uint8_t data_length)
{
	HAL_I2C_Master_Transmit(I2C_PERI, peri_address, &mem_address , 1, 1000);
	HAL_I2C_Master_Receive(I2C_PERI, peri_address, read_buffor, data_length, 100);

}
