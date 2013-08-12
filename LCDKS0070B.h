#ifndef LCDKS0070B_H_
#define LCDKS0070B_H_

/*
Title: Library for KS0070B LCD Controller 
Author: Alfredo Stefano
Date: 18/12/2012
Version: 1.1

===		Changelog	===
*ver. 1.1
- Added shifting left and shifting right
- Improved the port and pin definitions
- Added the printing method for string in Program Memory 
  by printToDisplay_P(char *message)
- Changed the library name in LCDKS0070B.h

*ver. 1.0
- Starting version
=======================


The Library is written for KS0070B Samsung LCD Controller. It is also compatible for 
HD44780 Hitachi LCD Controller.

Default Pinout is referenced to an Atmel ATmega 40-pin MCU series.
So feel free to redefine pins in your main.c. 
It follows a list with the default controller pins:

- RS: 	Default 5
- RW: 	Default 6
- E: 	Default 7
- DB0:	Default 0
- DB1:	Default 1
- DB2:	Default 2
- DB3: 	Default 3
- DB4:	Default 4
- DB5:	Default 5
- DB6:	Default 6
- DB7:	Default 7

=====	WARNING:	======
Before including this library, you have to specify your F_CPU below here, e.g.
#define F_CPU 3686400UL // CPU = 3.6864 MHz. You have also to specify the 
DATA_OUT port and the CONTROL_FN port and pins.

It's not needed to include delay.h in your main.c. It is already included here.

*/

#include <stdio.h>
#include <avr/io.h>
#include <avr/pgmspace.h>

#ifndef F_CPU
#define F_CPU 4000000UL	// Set Here your CPU Frequency in MHz
#endif

/* Defining of the  Data Port */
#define DATA_OUT PORTD

/* Defining of the  Function Port (for RS, RW and E pins)*/
#define CONTROL_FN PORTB

/* Defining of the  RS Pin */
#define RS	5

/* Defining of the  RW Pin */
#define RW	6

/* Defining of the  E Pin */
#define E	7

/* Defining of the  Data Bit 0 */
#define DB0 0

/* Defining of the  Data Bit 1 */
#define DB1 1

/* Defining of the  Data Bit 2 */
#define DB2 2

/* Defining of the  Data Bit 3 */
#define DB3 3

/* Defining of the  Data Bit 4 */
#define DB4 4

/* Defining of the  Data Bit 5 */
#define DB5 5

/* Defining of the  Data Bit 6 */
#define DB6 6

/* Defining of the  Data Bit 7 */
#define DB7 7

#include <util/delay.h>

#define INIT_LCD (1<<DB5)|(1<<DB4)
#define MAX_LENGTH 32

// int function_mode
#define FUNC_DEFAULT 	(0b00111000 << DB0) //2-LINE DISPLAY | 8-bit Interface | 5x7 dots
#define FUNC_1_LINE 	(0b00110000 << DB0) //1-LINE DISPLAY | 8-bit Interface | 5x7 dots

// display_mode
#define DISPLAY_OFF		(0b000010 << DB2)
#define DISPLAY_CLEAR	(0b00000001<<DB0)
#define DISPLAY_ON		(0b000011 << DB2)
#define DISPLAY_HOME	(0b00000010<<DB0)

// cursor_mode
#define CURSOR_ON		(1<<DB3)|(1<<DB1)
#define CURSOR_OFF		(1<<DB3)|(0<<DB1)

// blink_mode
#define BLINK_ON		(1<<DB3)|(1<<DB0)
#define BLINK_OFF		(1<<DB3)|(0<<DB0)

// shift_mode
#define DISPLAY_SHIFT	(1<<DB4)|(1<<DB3)
#define CURSOR_MOVE		(1<<DB4)|(0<<DB3)
#define SHIFT_RIGHT		(1<<DB4)|(1<<DB2)
#define SHIFT_LEFT		(1<<DB4)|(0<<DB2)

// entry_mode
#define CURSOR_INCREASE	(1<<DB2)|(1<<DB1)
#define CURSOR_DECREASE	(1<<DB2)|(0<<DB1)
#define DISPLAY_SHIFTED	(1<<DB2)|(1<<DB0)
#define DISPLAY_NOT_SHIFTED (1<<DB2)|(0<<DB0) 

//Line definitions
#define FIRST_LINE (1<<DB7)|(0x00<<DB0)
#define SECOND_LINE (1<<DB7)|(0x40<<DB0)

void InitLCD(int function_mode);

void clearDisplay();

void printChar(char item);

void goToSecondLine();

void printToDisplay(char *message);

void printToDisplay_P(char *message); //for Pprogram Memory Strings PSTR("stringa")

char numberToCharASCII(char number);

void positioning(char line, char offset);
//In positioning use (for line var) FIRST_LINE or SECOND_LINE
//offset would start from 0

int calcCent(int number);

int calcDecin(int number);

int calcUnit(int number);

void shiftLeft();

void shiftRight();

#endif /* LCDKS0070B.h */
