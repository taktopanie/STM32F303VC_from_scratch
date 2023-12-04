/*
 * my_GPS.c
 *
 *  Created on: Nov 30, 2023
 *      Author: maciej
 */

#include <my_GPS.h>


GPS_Position_Data_t GPS_get_position(uint8_t * phrase, uint8_t size)
{
	GPS_Position_Data_t _tmp = {0,0,0,0};

	//char char_cmp [5];

	//strncpy(char_cmp, (char*)phrase, 5);

	if(!(strncmp((char*)phrase, "GPGGA", 5)))
	{
		uint32_t data_length = data_get(phrase, size, 6);

	_tmp.Latitude = data_length;
	_tmp.Longtitude = 1;
	_tmp.E_W_ind = 1;
	_tmp.N_S_ind = 1;
	}
//	else{
//		_tmp.Latitude = 0;
//		_tmp.Longtitude = 0;
//		_tmp.E_W_ind = 0;
//		_tmp.N_S_ind = 0;
//	}
	return _tmp;

}

uint32_t data_get(uint8_t* wsk, int size, int data_ID)
{
//	//GET data size
//	int size = 0;
//	while(*(wsk + size) != '\n')
//	{
//		size++;
//	}

	//make copy of data
	char table [size];
	for(int i =0; i < size; i++)
	{
		table[i] = *(wsk + i);
	}

	char * tmp = NULL;

	// DELETE prev ',' signs
	for (int i = 0; i < data_ID; i ++){
		tmp = strchr(table, ',');
		*tmp = '/';
	}
	tmp = NULL;

	//GET HEAD and TAIL of msg with data_ID which will be returned
	char * head;
	char * tail;

	head = strchr(table, ',');
	*head = '/';
	tail = strchr(table, ',');

	//No. of data available
	return ((tail-head) - 1);


}

uint32_t get_value_from_datastring(uint8_t* wsk, int data_ID){
 return 0;
}
