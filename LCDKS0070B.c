#include "LCDKS0070b.h"

//PUBLIC METHODS

void printChar(char item)
{
	CONTROL_FN = (1<<RS)|(0<<RW);
	DATA_OUT = (item<<DB0);
	CONTROL_FN |= (1<<E);
	_delay_us(2);
	CONTROL_FN ^= (1<<E);
	_delay_us(50);
	return;
}

void goToSecondLine()
{
	CONTROL_FN = (0<<RS)|(0<<RW);
	DATA_OUT = SECOND_LINE;
	CONTROL_FN |= (1<<E);
	_delay_us(2);
	CONTROL_FN ^= (1<<E);
	_delay_us(100);
	return;
}

void InitLCD(int function_mode)
{
	_delay_ms(40);
	DATA_OUT = 0x00 | INIT_LCD;
	CONTROL_FN |= (1<<E);
	_delay_us(2);
	CONTROL_FN ^= (1<<E);

	_delay_ms(5);
	DATA_OUT = 0x00 | INIT_LCD;
	CONTROL_FN |= (1<<E);
	_delay_us(2);
	CONTROL_FN ^= (1<<E);

	_delay_us(105);
	DATA_OUT = 0x00 | INIT_LCD;
	CONTROL_FN |= (1<<E);
	_delay_us(2);
	CONTROL_FN ^= (1<<E);
	_delay_us(105);

	switch(function_mode)
	{
		case FUNC_1_LINE:
			DATA_OUT = FUNC_1_LINE;
			CONTROL_FN = (0<<RS)|(0<<RW);
			CONTROL_FN |= (1<<E);
			_delay_us(2);
			CONTROL_FN ^= (1<<E);
			_delay_us(100);

			break;

		case FUNC_DEFAULT:
			DATA_OUT = FUNC_DEFAULT;
			CONTROL_FN = (0<<RS)|(0<<RW);
			CONTROL_FN |= (1<<E);
			_delay_us(2);
			CONTROL_FN ^= (1<<E);
			_delay_us(100);
			break;

		default:
			DATA_OUT = FUNC_DEFAULT;
			CONTROL_FN = (0<<RS)|(0<<RW);
			CONTROL_FN |= (1<<E);
			_delay_us(2);
			CONTROL_FN ^= (1<<E);
			_delay_us(100);
			break;
		
	}
	
	// TURN OFF DISPLAY
	DATA_OUT = DISPLAY_OFF;
	CONTROL_FN = (0<<RS)|(0<<RW);
	CONTROL_FN |= (1<<E);
	_delay_us(2);
	CONTROL_FN ^= (1<<E);
	_delay_us(100);

	// DEFAULT SETTINGS DISPLAY
	DATA_OUT = CURSOR_OFF | BLINK_OFF;
	CONTROL_FN = (0<<RS)|(0<<RW);
	CONTROL_FN |= (1<<E);
	_delay_us(2);
	CONTROL_FN ^= (1<<E);
	_delay_us(100);

	// DISPLAY SHIFTING
	DATA_OUT = CURSOR_MOVE | SHIFT_RIGHT;
	CONTROL_FN = (0<<RS)|(0<<RW);
	CONTROL_FN |= (1<<E);
	_delay_us(2);
	CONTROL_FN ^= (1<<E);
	_delay_us(100);

	// CLEAR DISPLAY
	DATA_OUT = DISPLAY_CLEAR;
	CONTROL_FN = (0<<RS)|(0<<RW);
	CONTROL_FN |= (1<<E);
	_delay_us(2);
	CONTROL_FN ^= (1<<E);
	_delay_ms(4);

	// ENTRY MODE
	DATA_OUT = CURSOR_INCREASE | DISPLAY_NOT_SHIFTED;
	CONTROL_FN = (0<<RS)|(0<<RW);
	CONTROL_FN |= (1<<E);
	_delay_us(2);
	CONTROL_FN ^= (1<<E);
	_delay_us(100);

	// RETURN HOME
	DATA_OUT = DISPLAY_HOME;
	CONTROL_FN = (0<<RS)|(0<<RW);
	CONTROL_FN |= (1<<E);
	_delay_us(2);
	CONTROL_FN ^= (1<<E);
	_delay_ms(4);

	// TURN ON DISPLAY
	DATA_OUT = DISPLAY_ON;
	CONTROL_FN = (0<<RS)|(0<<RW);
	CONTROL_FN |= (1<<E);
	_delay_us(2);
	CONTROL_FN ^= (1<<E);
	_delay_us(100);

	return;
}

void clearDisplay()
{
	// CLEAR DISPLAY
	DATA_OUT = DISPLAY_CLEAR;
	CONTROL_FN = (0<<RS)|(0<<RW);
	CONTROL_FN |= (1<<E);
	_delay_us(2);
	CONTROL_FN ^= (1<<E);
	_delay_ms(4);

	// RETURN HOME
	DATA_OUT = DISPLAY_HOME;
	CONTROL_FN = (0<<RS)|(0<<RW);
	CONTROL_FN |= (1<<E);
	_delay_us(2);
	CONTROL_FN ^= (1<<E);
	_delay_ms(4);
	
	return;
}

char numberToCharASCII(char number)
{
	if(number >=0 && number < 10)
	{
		return number + 0x30;
	}
	else
		return 0x30;	
}

void printToDisplay(char *message)
{
	/*if(message_length > MAX_LENGTH)
	{
		message = "Message too long";
		for(int i=0; !(message[i]==0x00);i++)
		{
			printChar(message[i]);
		}
	}
	else
	{*/
		for(int i=0; !(message[i]==0x00);i++)
		{
			//PORTB = (char)i;
			if(i<15)
			{
				printChar(message[i]);
			}
			else
			if(i==15)
			{
				printChar(message[i]);
				goToSecondLine();
			}
			else
			{
				printChar(message[i]);
			}

		}
	//}
	return;
}

void printToDisplay_P(char *message)
{
	/*if(message_length > MAX_LENGTH)
	{
		message = "Message too long";
		for(int i=0; !(message[i]==0x00);i++)
		{
			printChar(message[i]);
		}
	}
	else
	{*/

		for(int i=0; pgm_read_byte(message)!=0x00;i++)
		{
			//PORTB = (char)i;
			if(i<15)
			{
				printChar(pgm_read_byte(message));
			}
			else
			if(i==15)
			{
				printChar(pgm_read_byte(message));
				goToSecondLine();
			}
			else
			{
				printChar(pgm_read_byte(message));
			}

			message++;
		}
	//}
	return;
}

void positioning(char line, char offset)
{
	if( (0b01111111&(line+offset))>0x0F && (0b01111111&(line+offset))>0x4F)
	{
		return;
	}
	else
	{
		CONTROL_FN = (0<<RS)|(0<<RW);
		DATA_OUT = line+offset;
		CONTROL_FN |= (1<<E);
		_delay_us(2);
		CONTROL_FN ^= (1<<E);
		_delay_us(100);
	}

	return;
}

int calcCent(int number)
{
	int centinaia=0;
	if(number < 100)
	{
		return centinaia;
	}
	else
	{
		while(number >= 100)
		{
			centinaia++;
			number -= 100;
		}
		return centinaia;
	}
}

int calcDecin(int number)
{
	int decine=0;
	if(number < 10)
	{
		return decine;
	}
	else
	{
		while(number >= 10)
		{
			decine++;
			number -= 10;
		}
		return decine;
	}
}

int calcUnit(int number)
{
	int centinaia = calcCent(number);
	int decine = calcDecin(number);

	return number-((centinaia*100)+(decine*10));
}

void shiftLeft()
{
	CONTROL_FN = CONTROL_FN = (0<<RS)|(0<<RW);
	DATA_OUT = DISPLAY_SHIFT | SHIFT_LEFT;
	CONTROL_FN |= (1<<E);
	_delay_us(2);
	CONTROL_FN ^= (1<<E);
	_delay_us(100);

	return;
}

void shiftRight()
{
	CONTROL_FN = CONTROL_FN = (0<<RS)|(0<<RW);
	DATA_OUT = DISPLAY_SHIFT | SHIFT_RIGHT;
	CONTROL_FN |= (1<<E);
	_delay_us(2);
	CONTROL_FN ^= (1<<E);
	_delay_us(100);

	return;
}


