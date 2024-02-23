/*
 * LSM303DLHC.c
 *
 *  Created on: Feb 23, 2024
 *      Author: maciej
 */

#include "LSM303DLHC.h"

position_t MAGNETIC_get_field(uint8_t* _RAW_DATA)
{
	position_t tmp_pos;

	tmp_pos.X_H = (int8_t)_RAW_DATA[0];
	tmp_pos.X_L = (int8_t)_RAW_DATA[1];
	tmp_pos.Z_H = (int8_t)_RAW_DATA[2];
	tmp_pos.Z_L = (int8_t)_RAW_DATA[3];
	tmp_pos.Y_H = (int8_t)_RAW_DATA[4];
	tmp_pos.Y_L = (int8_t)_RAW_DATA[5];

	return tmp_pos;
}
float MAGNETIC_get_temp(uint16_t _TEMP_H_L)
{
	uint16_t tmp;
	tmp = ((_TEMP_H_L & 0xFF) << 8) | (_TEMP_H_L >> 8);
	return((float)(tmp >> 4)/8 + 25);
}

