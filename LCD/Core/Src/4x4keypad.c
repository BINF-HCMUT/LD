/*
 * 4x4keypad.c
 *
 *  Created on: Nov 7, 2022
 *      Author: admin
 */


#include "4x4keypad.h"
#include "main.h"
#include "LCD.h"

const char KEY[16]={
		'7','8','9','/',
		'4','5','6','x',
		'1','2','3','-',
		'#','0','=','+'
};
char operator;

unsigned char check_row(unsigned char col){
	if(HAL_GPIO_ReadPin(GPIOB, R0_Pin) == 0 )	return KEY[col];
	else if (HAL_GPIO_ReadPin(GPIOB, R1_Pin) == 0)	return KEY[4+col];
	else if (HAL_GPIO_ReadPin(GPIOB, R2_Pin) == 0)	return KEY[8+col];
	else if (HAL_GPIO_ReadPin(GPIOB, R3_Pin) == 0)	return KEY[12+col];
	else return 0xFF;
}
unsigned char KEYPAD_Read(void){
	unsigned char key;
	HAL_GPIO_WritePin(GPIOA, C0_Pin|C1_Pin|C2_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOB, C3_Pin, GPIO_PIN_SET);

	HAL_GPIO_WritePin(GPIOA, C0_Pin, RESET);
	key = check_row(0);
	HAL_GPIO_WritePin(GPIOA, C0_Pin, SET);
	if(key != 0xFF)	return key;

	HAL_GPIO_WritePin(GPIOA, C1_Pin, RESET);
	key = check_row(1);
	HAL_GPIO_WritePin(GPIOA, C1_Pin, SET);
	if(key != 0xFF)	return key;

	HAL_GPIO_WritePin(GPIOA, C2_Pin, RESET);
	key = check_row(2);
	HAL_GPIO_WritePin(GPIOA, C2_Pin, SET);
	if(key != 0xFF)	return key;

	HAL_GPIO_WritePin(GPIOB, C3_Pin, RESET);
	key = check_row(3);
	HAL_GPIO_WritePin(GPIOB, C3_Pin, SET);
	if(key != 0xFF)	return key;

	return 0xFF;
}

void Key_Read(){
	char text = KEYPAD_Read();
	if(text != 0xFF)
	{
		text = KEYPAD_Read();
		if(text != 0xFF)
		{
			LCD_add_To_String(text);
		}

	}
}
