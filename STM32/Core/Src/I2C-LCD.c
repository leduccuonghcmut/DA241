/*
 * I2c_lcd.c
 *
 *  Created on: Oct 31, 2024
 *      Author: Duy
 */

#include "I2C-LCD.h"
#include "dht20.h"

//extern I2C_HandleTypeDef hi2c1;  // change your handler here accordingly
//
//#define addr_pcf8574 0x21<<1
//
//void LCD_I2C_Write_CMD(uint8_t cmd)
//{
//    char data_u, data_l;
//    uint8_t data_t[4];
//
//    data_u = (cmd & 0xF0);
//    data_l = ((cmd << 4) & 0xF0);
//
//    data_t[0] = data_u | 0x0C;  // EN=1, RS=0
//    data_t[1] = data_u | 0x08;  // EN=0, RS=0
//    data_t[2] = data_l | 0x0C;  // EN=1, RS=0
//    data_t[3] = data_l | 0x08;  // EN=0, RS=0
//
//    HAL_I2C_Master_Transmit(&hi2c1, addr_pcf8574, data_t, 4, HAL_MAX_DELAY);
//}
//
//void LCD_I2C_Write_DATA(uint8_t data)
//{
//    char data_u, data_l;
//    uint8_t data_t[4];
//
//    data_u = (data & 0xF0);
//    data_l = ((data << 4) & 0xF0);
//
//    data_t[0] = data_u | 0x0D;  // EN=1, RS=1
//    data_t[1] = data_u | 0x09;  // EN=0, RS=1
//    data_t[2] = data_l | 0x0D;  // EN=1, RS=1
//    data_t[3] = data_l | 0x09;  // EN=0, RS=1
//
//    HAL_I2C_Master_Transmit(&hi2c1, addr_pcf8574, data_t, 4, HAL_MAX_DELAY);
//}
//void LCD_I2C_Init()
//{
//	LCD_I2C_Write_CMD(0x33);
//	LCD_I2C_Write_CMD(0x32);
//	HAL_Delay(50);
//	LCD_I2C_Write_CMD(0x28);
//	HAL_Delay(50);
//	LCD_I2C_Write_CMD(0x01);
//	HAL_Delay(50);
//	LCD_I2C_Write_CMD(0x06);
//	HAL_Delay(50);
//	LCD_I2C_Write_CMD(0x0C);
//	HAL_Delay(50);
//	LCD_I2C_Write_CMD (0x02); /* move cursor to home and set data address to 0 */
//	HAL_Delay(50);
//	LCD_I2C_Write_CMD (0x80);
//
//}
//void LCD_I2C_Clear()
//{
//	LCD_I2C_Write_CMD(0x01);
//	HAL_Delay(50);
//}
//void LCD_I2C_Location(uint8_t x, uint8_t y)
//{
//	if(x==0)
//	{
//		LCD_I2C_Write_CMD(0x80+y);
//	}
//	else if(x==1)
//	{
//		LCD_I2C_Write_CMD(0xC0+y);
//	}
//}
//void LCD_I2C_Write_String(char* string)
//{
//	for(uint8_t i=0;i<strlen(string); i++)
//	{
//		LCD_I2C_Write_DATA(string[i]);
//	}
//}
//void LCD_I2C_Write_Number(int number)
//{
//	char buffer[8];
//    sprintf(buffer,"%d",number);
//    LCD_I2C_Write_String(buffer);
//}

extern I2C_HandleTypeDef hi2c1;  // change your handler here accordingly
//
#define SLAVE_ADDRESS_LCD (0x21 << 1) // change this according to ur setup

void lcd_send_cmd (char cmd)
{
  char data_u, data_l;
	uint8_t data_t[4];
	data_u = (cmd&0xf0);
	data_l = ((cmd<<4)&0xf0);
	data_t[0] = data_u|0x0C;  //en=1, rs=0
	data_t[1] = data_u|0x08;  //en=0, rs=0
	data_t[2] = data_l|0x0C;  //en=1, rs=0
	data_t[3] = data_l|0x08;  //en=0, rs=0
	HAL_I2C_Master_Transmit (&hi2c1, SLAVE_ADDRESS_LCD,(uint8_t *) data_t, 4, 100);
}

void lcd_send_data (char data)
{
	char data_u, data_l;
	uint8_t data_t[4];
	data_u = (data&0xf0);
	data_l = ((data<<4)&0xf0);
	data_t[0] = data_u|0x0D;  //en=1, rs=0
	data_t[1] = data_u|0x09;  //en=0, rs=0
	data_t[2] = data_l|0x0D;  //en=1, rs=0
	data_t[3] = data_l|0x09;  //en=0, rs=0
	HAL_I2C_Master_Transmit (&hi2c1, SLAVE_ADDRESS_LCD,(uint8_t *) data_t, 4, 100);
}

void lcd_init (void) {
	lcd_send_cmd (0x33); /* set 4-bits interface */
	lcd_send_cmd (0x32);
	HAL_Delay(50);
	lcd_send_cmd (0x28); /* start to set LCD function */
	HAL_Delay(50);
	lcd_send_cmd (0x01); /* clear display */
	HAL_Delay(50);
	lcd_send_cmd (0x06); /* set entry mode */
	HAL_Delay(50);
	lcd_send_cmd (0x0c); /* set display to on */
	HAL_Delay(50);
	lcd_send_cmd (0x02); /* move cursor to home and set data address to 0 */
	HAL_Delay(50);
	lcd_send_cmd (0x80);
}

void lcd_send_string (char *str)
{
	while (*str) lcd_send_data (*str++);
}

void lcd_clear_display (void)
{
	lcd_send_cmd (0x01); //clear display
}

void lcd_goto_XY (int row, int col)
{
	uint8_t pos_Addr;
	if(row == 1)
	{
		pos_Addr = 0x80 + row - 1 + col;
	}
	else
	{
		pos_Addr = 0xC0+ col;
	}
	lcd_send_cmd(pos_Addr);
}

void lcd_show_value(){
	  lcd_goto_XY(0, 0);
	  lcd_send_string("HUMID: ");
	  lcd_goto_XY(0, 8);
	  lcd_send_string(humid);
	  lcd_goto_XY(1, 0);
	  lcd_send_string("TEMP: ");
	  lcd_goto_XY(1, 8);
	  lcd_send_string(temp);
}
