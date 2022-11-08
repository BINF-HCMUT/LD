/*
 * LCD.c
 *
 *  Created on: Oct 20, 2022
 *      Author: admin
 */


#include"LCD.h"
char operand[16];

void LCD_add_To_String(char data){
	for(int i = 0;i<15;i++){
		operand[i] = operand[i+1];
	}
	operand[15] = data;
	LCD_Put_Cur(0,0);
	for(int i = 0; i<16;i++)	LCD_Send_Data(operand[i]);
}

void send8bitstoLCD(char vee){
	int b0,b1,b2,b3,b4,b5,b6,b7;

	b0 = vee & 1;
	b1 = vee & 2;
	b2 = vee & 4;
	b3 = vee & 8;
	b4 = vee & 16;
	b5 = vee & 32;
	b6 = vee & 64;
	b7 = vee & 128;

	HAL_GPIO_WritePin(GPIOA, D0_Pin, b0);
	HAL_GPIO_WritePin(GPIOA, D1_Pin, b1);
	HAL_GPIO_WritePin(GPIOA, D2_Pin, b2);
	HAL_GPIO_WritePin(GPIOA, D3_Pin, b3);
	HAL_GPIO_WritePin(GPIOA, D4_Pin, b4);
	HAL_GPIO_WritePin(GPIOA, D5_Pin, b5);
	HAL_GPIO_WritePin(GPIOA, D6_Pin, b6);
	HAL_GPIO_WritePin(GPIOA, D7_Pin, b7);

}

void LCD_Init(){
	// HAL_Delay(20);
	LCD_Send_CMD(0x38);		/* Initialization of 16X2 LCD in 8bit mode */
	LCD_Send_CMD(0x0C);		/* Display ON Cursor OFF */
	LCD_Send_CMD(0x06);		/* Auto Increment cursor */
	LCD_Send_CMD(0x01);		/* Clear display */
	LCD_Send_CMD(0x80);		/* Cursor at home position */
}

void LCD_Send_CMD(char cmd){
	HAL_GPIO_WritePin(GPIOA, RS_Pin, 0);
	send8bitstoLCD(cmd);
	HAL_GPIO_WritePin(GPIOA, EN_Pin, 0);
	HAL_GPIO_WritePin(GPIOA, EN_Pin, 1);
}

void LCD_Send_Data(char data){
	HAL_GPIO_WritePin(GPIOA, RS_Pin, 1);
	send8bitstoLCD(data);
	HAL_GPIO_WritePin(GPIOA, EN_Pin, 0);
	HAL_GPIO_WritePin(GPIOA, EN_Pin, 1);
}

void LCD_Send_String(char *str){
	for (int i = 0; str[i] != '\0'; i++){
		LCD_Send_Data(str[i]);
	}
}

void LCD_Put_Cur(int row,int col){
	LCD_Send_CMD(0x3C);		//Activate second line
	switch(row){
	case 0:
		col |= 0x80;
		break;
	case 1:
		col |= 0xC0;
		break;
	}
	LCD_Send_CMD(col);
}

void LCD_Clear(){
	LCD_Send_CMD(0x01);
}
