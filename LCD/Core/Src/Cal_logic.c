#include "Cal_logic.h"
#include "LCD.h"
#include <stdlib.h>
#include <stdlib.h>
#include <stdio.h>

char final[16];

int logicCal(char str1[16], char str2[16], char cal, int check2, int temp, int checkdiv, int i, int j)
{
	int num1 = 0, count1 = 0, count2 = 0, count3 = 0, check1 = 0;
	unsigned long long num2 = 0, result1 = 0;
	double result2 = 0;

	if (temp == 2)
	{
		i = 0;
		while (final[count3] != '\0')
		{
			str1[count3] = final[count3];
			final[count3] = '\0';
			i++; count3++;
		}
	}

	if (check2 == 1)
	{
		for (int l = 0; l < 16; l++) final[l] = '\0';
	}

	while (count1 < i)
	{
		if (str1[count1] == '-')
	    {
			count1++;
	        while (count1 < i)
	        {
	        	int temp1 = (int)str1[count1] - 48;
	        	num1 = num1 * 10 + temp1;
	            count1++;
	        }
	        num1 *= -1;
	        break;
	    }
	    int temp1 = (int)str1[count1] - 48;
	    num1 = num1 * 10 + temp1;
	    count1++;
	}
	while (count2 < j)
	{
		if (str2[count2] == '-')
	    {
			count2++;
	    	while (count2 < j)
	    	{
	    		int temp2 = (int)str2[count2] - 48;
	    		num2 = num2 * 10 + temp2;
	    		count2++;
	    	}
	    	num2 *= -1;
	    	break;
	    }
	    int temp2 = (int)str2[count2] - 48;
	    num2 = num2 * 10 + temp2;
	    count2++;
	}

	if (cal == '\0')
	{
		LCD_Put_Cur(1, 11);
		LCD_Send_String("error");
	    return 0;
	}
	else if (count1 == 0)
	{
		LCD_Put_Cur(1, 11);
		LCD_Send_String("error");
		return 0;
	}
	else if (count2 == 0)
	{
		LCD_Put_Cur(1, 11);
		LCD_Send_String("error");
		return 0;
	}
	else if (checkdiv > 1)
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
		return 0;
	}

	switch(cal)
	{
		case '+':
			result1 = num1+num2;
	        break;
	    case '-':
	        result1 = num1-num2;
	        break;
	    case 'x':
	        result1 = num1*num2;
	        if (num1*num2 < -2147483648 && num1*num2 > 2147483648)
	        {
	        	LCD_Put_Cur(1, 6);
	        	LCD_Send_String("math error");
	        	return 0;
	        }
	        break;
	    case '/':
	        if(num2 == 0)
	        {
	        	LCD_Put_Cur(1, 11);
	        	LCD_Send_String("error");
	        	return 0;
	        }
	        else
	        {
	        	check1 = 1;
	            result2 = (double)num1/num2;
	        }
	        break;
	}
	if (check1 == 0)
	{
		sprintf(final, "%d", result1);
	}
	else
	{
		sprintf(final, "%f", result2);
	}
	int tmpcount = 0;
	for(int z = 0; z < 16; z++)
	{
		LCD_Put_Cur(1, tmpcount);
		LCD_Send_Data('\0');
		tmpcount++;
	}
	count3 = 0;
	while (final[count3] != '\0') count3++;
	LCD_Put_Cur(1, 16 - count3);
	for(int y = 0; y < 16; y++) LCD_Send_Data(final[y]);
	return 1;
}

