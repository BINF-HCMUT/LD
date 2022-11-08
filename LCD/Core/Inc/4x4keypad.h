/*
 * 4x4keypad.h
 *
 *  Created on: Nov 7, 2022
 *      Author: admin
 */

#ifndef INC_4X4KEYPAD_H_
#define INC_4X4KEYPAD_H_

#include"main.h"
/* Keypad NOT pressed */
#define KEYPAD_NOT_PRESSED			0xFF

void Key_Read();
unsigned char KEYPAD_Read(void);

#endif /* INC_4X4KEYPAD_H_ */
