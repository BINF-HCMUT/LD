#include "Cal_logic.h"
#include "LCD.h"
#include <stdlib.h>
#include <stdlib.h>
#include <stdio.h>

char final[16];

int logicCal(char str1[16], char str2[16], char cal, int check2, int i, int j)
{
	int num1 = 0, num2 = 0, count1 = 0, count2 = 0, result1 = 0, check1 = 0;
	float result2 = 0;

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
	        break;
	    case '/':
	        if(num2 == 0)
	        {
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
	LCD_Put_Cur(1,0);
	for(int i = 0; i < 16; i++) LCD_Send_Data(final[i]);
	return 0;
}

