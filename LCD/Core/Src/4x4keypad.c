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
		'7','8','9','%',
		'4','5','6','x',
		'1','2','3','-',
		'#','0','=','+'
};

unsigned char check_row(unsigned char col){
	if(HAL_GPIO_ReadPin(GPIOB, R0_Pin) == 0 )	return KEY[col];
	else if (HAL_GPIO_ReadPin(GPIOB, R1_Pin) == 0)	return KEY[4+col];
	else if (HAL_GPIO_ReadPin(GPIOB, R2_Pin) == 0)	return KEY[8+col];
	else if (HAL_GPIO_ReadPin(GPIOB, R3_Pin) == 0)	return KEY[12+col];
	else return 0xFF;
}
unsigned char KEYPAD_Read(void){
	unsigned char key;
	HAL_GPIO_WritePin(GPIOB, C0_Pin|C1_Pin|C2_Pin|C3_Pin, GPIO_PIN_SET);

	HAL_GPIO_WritePin(GPIOB, C0_Pin, RESET);
	key = check_row(0);
	HAL_GPIO_WritePin(GPIOB, C0_Pin, RESET);
	if(key != 0xFF)	return key;

	HAL_GPIO_WritePin(GPIOB, C1_Pin, RESET);
	key = check_row(1);
	HAL_GPIO_WritePin(GPIOB, C1_Pin, RESET);
	if(key != 0xFF)	return key;

	HAL_GPIO_WritePin(GPIOB, C2_Pin, RESET);
	key = check_row(2);
	HAL_GPIO_WritePin(GPIOB, C2_Pin, RESET);
	if(key != 0xFF)	return key;

	HAL_GPIO_WritePin(GPIOB, C3_Pin, RESET);
	key = check_row(3);
	HAL_GPIO_WritePin(GPIOB, C3_Pin, RESET);
	if(key != 0xFF)	return key;

	return 0xFF;
}
//unsigned char check_clm(unsigned char pin_var){
//	unsigned char clm;
//	HAL_GPIO_WritePin(GPIOB, C0_Pin|C1_Pin|C2_Pin|C3_Pin, GPIO_PIN_SET);
//
//	HAL_GPIO_WritePin(GPIOB, C0_Pin, RESET);
//	if(HAL_GPIO_ReadPin(GPIOB, pin_var) == 0)	clm = 0;
//
//	HAL_GPIO_WritePin(GPIOB, C0_Pin, SET);
//	HAL_GPIO_WritePin(GPIOB, C1_Pin, RESET);
//	if(HAL_GPIO_ReadPin(GPIOB, pin_var) == 0)	clm = 1;
//
//	HAL_GPIO_WritePin(GPIOB, C1_Pin, SET);
//	HAL_GPIO_WritePin(GPIOB, C2_Pin, RESET);
//	if(HAL_GPIO_ReadPin(GPIOB, pin_var) == 0)	clm = 2;
//
//	HAL_GPIO_WritePin(GPIOB, C2_Pin, SET);
//	HAL_GPIO_WritePin(GPIOB, C3_Pin, RESET);
//	if(HAL_GPIO_ReadPin(GPIOB, pin_var) == 0)	clm = 3;
//
//	HAL_GPIO_WritePin(GPIOB, C0_Pin|C1_Pin|C2_Pin|C3_Pin, GPIO_PIN_RESET);
//
//	return clm;
//}


//unsigned char KEYPAD_Read(void){
//   unsigned char clm_var;
//
//   if(HAL_GPIO_ReadPin(GPIOB, R0_Pin) == 0){
//	   clm_var = check_clm(R0_Pin);
//	   return KEY[clm_var];
//   }
//   else if(HAL_GPIO_ReadPin(GPIOB, R1_Pin) == 0){
//	   clm_var = check_clm(R1_Pin);
//	   return KEY[clm_var+4];
//   }
//   else if(HAL_GPIO_ReadPin(GPIOB, R2_Pin) == 0){
//	   clm_var = check_clm(R2_Pin);
//	   return KEY[clm_var+8];
//   }
//   else if(HAL_GPIO_ReadPin(GPIOB, R3_Pin) == 0){
//	   clm_var = check_clm(R3_Pin);
//	   return KEY[clm_var+12];
//   }
//   else
//	   return 0xFF;
//
//}

void Key_Read(){
	char text = KEYPAD_Read();
	if(text != 0xFF)	LCD_add_To_String(text);
}
