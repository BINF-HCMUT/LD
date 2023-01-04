/*
 * LCD.c
 *
 *  Created on: Oct 20, 2022
 *      Author: admin
 */


#include "LCD.h"
#include "Cal_logic.h"
char operator;
char operand1[16];
char operand2[16];
char operand[16];
int check = 0, check1 = 0, checkdiv = 0;
int i = 0, j = 0, temp = 0;

void ClearData()
{
	for (int l = 0; l < 16; l++)
	{
		operand1[l] = '\0';
		operand2[l] = '\0';
		operand[l] = '\0';
	}
	operator = '\0';
	i = 0; j = 0;
	check =  0; check1 = 1;
}

void LCD_add_To_String(char data)
{
	if (temp == 0 && check1 == 0)
	{
		ClearData();
		LCD_Clear();
	}
	if (data == '#')
	{
		ClearData();
		checkdiv = 0;
		LCD_Clear();
		return;
	}
	else if (data == '=')
	{
		if ((i + j + 1) > 16)
		{
			ClearData();
			LCD_Clear();
			return;
		}
		temp = logicCal(operand1, operand2, operator, check1, temp, checkdiv, i, j);
		check1 = 0;
		return;
	}
	else if (temp == 1 && check1 == 0)
	{
		for (int l = 0; l < 16; l++)
		{
			operand1[l] = '\0';
			operand2[l] = '\0';
			operand[l] = '\0';
		}
		operator = '\0';
		int tmpcount = 0;
		for(int z = 0; z < 16; z++)
		{
			LCD_Put_Cur(0, tmpcount);
			LCD_Send_Data('\0');
			tmpcount++;
		}

		for(int z = 0; z < 15; z++)
		{
			operand[z] = operand[z+1];
		}
		operand[15] = data;
		LCD_Put_Cur(0,0);
		for(int z = 0; z < 16; z++) LCD_Send_Data(operand[z]);

		operator = data;
		if (operator == '/') checkdiv++;
		i = 1; j = 0;
		temp = 2; check = 1;

		return;
	}


	if (operator != '\0')
	{
		if (data == '+' || data == 'x' || data == '/')
		{
			operator = data;
			if (data == '/') checkdiv++;
			return;
		}
	}

	if (data >= '0' && data <= '9')
	{
		if (check == 0)
		{
			operand1[i] = data;
			i++;
		}
		else
		{
			operand2[j] = data;
			j++;
		}
	}
	else if (data == '+' || data == '-' || data == 'x' || data == '/')
	{
		if (i == 0)
		{
			operand1[i] = data;
			i++;
		}
		else if (check == 0)
		{
			operator = data;
			if (data == '/') checkdiv++;
			check = 1;
		}
		else
		{
			operand2[j] = data;
		    j++;
		}
	}
	else
	{
		int tmpcount = 0;
		for(int z = 0; z < 16; z++)
		{
			LCD_Put_Cur(1, tmpcount);
			LCD_Send_Data('\0');
			tmpcount++;
		}
		LCD_Put_Cur(1, 11);
		LCD_Send_String("error");
        return;
    }

	for(int z = 0; z < 15; z++)
	{
		operand[z] = operand[z+1];
	}
	operand[15] = data;
	LCD_Put_Cur(0,0);
	for(int z = 0; z < 16; z++) LCD_Send_Data(operand[z]);
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

	HAL_GPIO_WritePin(D0_GPIO_Port, D0_Pin, b0);
	HAL_GPIO_WritePin(D1_GPIO_Port, D1_Pin, b1);
	HAL_GPIO_WritePin(D2_GPIO_Port, D2_Pin, b2);
	HAL_GPIO_WritePin(D3_GPIO_Port, D3_Pin, b3);
	HAL_GPIO_WritePin(D4_GPIO_Port, D4_Pin, b4);
	HAL_GPIO_WritePin(D5_GPIO_Port, D5_Pin, b5);
	HAL_GPIO_WritePin(D6_GPIO_Port, D6_Pin, b6);
	HAL_GPIO_WritePin(D7_GPIO_Port, D7_Pin, b7);

}

void LCD_Init(){
	HAL_Delay(20);
	LCD_Send_CMD(0x38);		/* Initialization of 16X2 LCD in 8bit mode */
	LCD_Send_CMD(0x0C);		/* Display ON Cursor OFF */
	LCD_Send_CMD(0x06);		/* Auto Increment cursor */
	LCD_Send_CMD(0x01);		/* Clear display */
	LCD_Send_CMD(0x80);		/* Cursor at home position */
}

void LCD_Send_CMD(char cmd){
	HAL_Delay(20);
	HAL_GPIO_WritePin(GPIOA, RS_Pin, 0); // RS = 0 nean send command
	send8bitstoLCD(cmd);
	HAL_GPIO_WritePin(GPIOA, EN_Pin, 0);
	HAL_GPIO_WritePin(GPIOA, EN_Pin, 1);
}

void LCD_Send_Data(char data){
	HAL_Delay(20);
	HAL_GPIO_WritePin(GPIOA, RS_Pin, 1); // RS = 1 send data
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
