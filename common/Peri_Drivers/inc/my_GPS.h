/*
 * my_GPS.h
 *
 *  Created on: Nov 30, 2023
 *      Author: maciej
 */

#ifndef PERI_DRIVERS_INC_MY_GPS_H_
#define PERI_DRIVERS_INC_MY_GPS_H_

#include <stdint.h>
#include <string.h>

typedef struct {
	uint32_t Latitude;
	uint8_t N_S_ind;
	uint32_t Longtitude;
	uint8_t E_W_ind;
}GPS_Position_Data_t;

GPS_Position_Data_t GPS_get_position(uint8_t * phrase, uint8_t size);

uint32_t data_get(uint8_t* wsk, int size, int data_ID);
uint32_t get_value_from_datastring(uint8_t* wsk, int data_ID);

#endif /* PERI_DRIVERS_INC_MY_GPS_H_ */


