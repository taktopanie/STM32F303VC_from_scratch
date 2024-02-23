/*
 * LSM303DLHC.h
 *
 *  Created on: Feb 23, 2024
 *      Author: maciej
 */

#ifndef INC_LSM303DLHC_H_
#define INC_LSM303DLHC_H_

#include "stm32f3xx.h"

/*
 * memory addresses
 *
 * memory should be accesses in the sequence => CHECK THE DATASHEET
 *
 */
#define MAGNETIC_TEMP_HIGH_REG		0x31
#define MAGNETIC_TEMP_LOW_REG		0x32

#define MAGNETIC_X_HIGH_REG			0x03
#define MAGNETIC_X_LOW_REG			0x04

#define MAGNETIC_Z_HIGH_REG			0x05
#define MAGNETIC_Z_LOW_REG			0x06

#define MAGNETIC_Y_HIGH_REG			0x07
#define MAGNETIC_Y_LOW_REG			0x08

// Struct to gather the data
typedef struct
{
	int8_t X_H;
	int8_t X_L;
	int8_t Z_H;
	int8_t Z_L;
	int8_t Y_H;
	int8_t Y_L;

}position_t;

position_t MAGNETIC_get_field(uint8_t * _RAW_DATA);
float MAGNETIC_get_temp(uint16_t _TEMP_H_L);


#endif /* INC_LSM303DLHC_H_ */
