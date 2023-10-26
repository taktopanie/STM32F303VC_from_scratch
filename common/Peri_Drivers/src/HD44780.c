/*
 * HD44780.c
 *
 *  Created on: Oct 25, 2023
 *      Author: maciej
 */


#include "HD44780.h"

void Set_RS(void)
{
	LCD_RS_PORT->ODR |= (LCD_RS_PIN);
}

void Set_RW (void)
{
	LCD_RW_PORT->ODR |= (LCD_RW_PIN);
}

void Set_E (void)
{
	LCD_E_PORT->ODR |= (LCD_E_PIN);
}

void Reset_RS (void)
{
	LCD_RS_PORT->ODR &= ~(LCD_RS_PIN);
}
void Reset_RW (void)
{
	LCD_RW_PORT->ODR &= ~(LCD_RW_PIN);
}
void Reset_E (void)
{
	LCD_E_PORT->ODR &= ~(LCD_E_PIN);
}


/*
 * function lcd_init
 */

void lcd_init(void){

	Set_RS();
	Set_RW();
	Set_E();
	// wyzerowanie pinow RS,RW,E
	Reset_RS();
	Reset_RW();
	Reset_E();
	HAL_Delay(50);

	lcd_sendHalf(0b0011);
	HAL_Delay(5);
	lcd_sendHalf(0b0011);
	HAL_Delay(100);
	lcd_sendHalf(0b0011);
	HAL_Delay(100);
	lcd_sendHalf(0b0010);


	// ustawienie 4bitow 2 wierszy i rozdzielczosci znakow
	lcd_send_command(FUNCTION_SET|DATA_LENGHT_4BIT|NUMBER_OF_LINES_2|CHARACTER_FONT_5x8);
	HAL_Delay(100);
	// wylaczenie wyswietlacza
	lcd_send_command(LCD_ONOFF|LCD_DISPLAY_ON|LCD_BLINKINGCOURSOR_ON);
	HAL_Delay(100);
	//wyczysczenie wyswietlacza
	lcd_send_command(LCD_CLEAR);
	HAL_Delay(100);
	// entry mode
	lcd_send_command(ENTRY_MODE|INCREMENT);
	HAL_Delay(100);
}

/*
 * function lcd_send_half
 */

void lcd_sendHalf(uint8_t data){
	if(data&(1<<0)){
		HAL_GPIO_WritePin(LCD_DATA_4_PORT, LCD_DATA_4_PIN, ENABLE);
		}else{HAL_GPIO_WritePin(LCD_DATA_4_PORT, LCD_DATA_4_PIN, DISABLE);}

	if(data&(1<<1)){
		HAL_GPIO_WritePin(LCD_DATA_5_PORT, LCD_DATA_5_PIN, ENABLE);
		}else{HAL_GPIO_WritePin(LCD_DATA_5_PORT, LCD_DATA_5_PIN, DISABLE);}

	if(data&(1<<2)){
		HAL_GPIO_WritePin(LCD_DATA_6_PORT, LCD_DATA_6_PIN, ENABLE);
		}else{HAL_GPIO_WritePin(LCD_DATA_6_PORT, LCD_DATA_6_PIN, DISABLE);}

	if(data&(1<<3)){
		HAL_GPIO_WritePin(LCD_DATA_7_PORT, LCD_DATA_7_PIN, ENABLE);
		}else{HAL_GPIO_WritePin(LCD_DATA_7_PORT, LCD_DATA_7_PIN, DISABLE);}
}

/*
 * function lcd_send_byte
 */

void lcd_send_byte(uint8_t byte)
{
	Set_E();
	lcd_sendHalf(byte>>4);
	HAL_Delay(2);
	Reset_E();

	Set_E();
	lcd_sendHalf(byte);
	HAL_Delay(2);
	Reset_E();


}

/*
 * function lcd_send_command
 */

void lcd_send_command(unsigned char command){
	Reset_RS();
	lcd_send_byte(command);
}

/*
 * function lcd_send_data
 */

void lcd_send_data(unsigned char data)
{
	Set_RS();
	lcd_send_byte(data);
}

/*
 * function lcd_send_text
 */

void lcd_send_text(char *text){
	while(*text){
		lcd_send_data(*text);
		text++;
	}
}
