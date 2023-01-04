/*
 * LCD.h
 *
 *  Created on: Oct 20, 2022
 *      Author: admin
 */

#ifndef INC_LCD_H_
#define INC_LCD_H_

#include"main.h"

void LCD_Init();					//initialize LCD
void LCD_Send_CMD(char cmd);		//send command to LCD
void LCD_Send_Data(char data);		//send data to LCD
void LCD_Send_String(char *str);	//send string to LCD
void LCD_Put_Cur(int row,int col);	//put cursor at the position (row, col)
void LCD_Clear();					//clear LCD
void LCD_add_To_String(char data);

#endif /* INC_LCD_H_ */
