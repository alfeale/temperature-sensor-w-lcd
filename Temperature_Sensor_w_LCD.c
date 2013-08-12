#include <avr/interrupt.h>
#include <avr/io.h>
#include "LCDKS0070B.h"


#define F_CPU		4000000UL

char degree;
char cent_degree;


void printTemperature()
{
	int cents = calcCent((int) degree);
	int decins = calcDecin((int) degree);
	int units = calcUnit((int) degree);

	positioning(FIRST_LINE,6);

	if(cents!=0)
	{
		printChar(numberToCharASCII((char)cents));
	}
	else
	{
		printChar(' ');
	}

	if(decins!=0)
	{
		printChar(numberToCharASCII((char)decins));
	}
	else
	{
		printChar(' ');
	}

	printChar(numberToCharASCII((char)units));

	printChar('.');

	switch(cent_degree)
	{
		case 0x00:
			printToDisplay_P(PSTR("0 "));
			break;

		case 0x40:
			printToDisplay_P(PSTR("25"));
			break;
		
		case 0x80:
			printToDisplay_P(PSTR("5 "));
			break;

		case 0xC0:
			printToDisplay_P(PSTR("75"));
			break;

		default:
			printToDisplay_P(PSTR("0 "));
			break;
	}
}


ISR(ADC_vect)
{
	cent_degree = ADCL;
	degree = ADCH;

	ADCSRA |= (1<<ADSC);
}


ISR(TIMER1_COMPA_vect)
{

	printTemperature();

}


void reset()
{
	// Set PORTA as input for the ADC peripheral
	DDRA = 0x00;

	// Set PORTD as output to send characters/commands to the LCD display
	DDRD = 0xFF;

	// Set PB7, PB6 and PB5 pins as output to send control commands to the LCD display
	DDRB = (1<<PB7)|(1<<PB6)|(1<<PB5);

	// The ADC peripheral is initialized in Free Running mode with ADC clock = fclk/128 (ADPS = 7)
	// The ADC result is left adjusted (ADLAR = 1); the sampling channel is AD0
	// The reference voltage is internally set at 2.56V
	ADCSRA = (1<<ADEN)|(1<<ADIE)|(7<<ADPS0);
	ADMUX = (3<<REFS0)|(1<<ADLAR)|(0<<MUX0);

	// Set Timer/Counter1 peripheral in CTC mode.
	// The T/C prescaler is set to fclk/256.
	// - OCR1A = 15625 T/C will count about 1 sec.
	// - OCR1A = 7812 T/C will count about 0.5 sec.
	// - OCR1A = 3906 T/C will count about 0.25 sec.
	// - OCR1A = 31250 T/C will count about 2 sec.
	OCR1A = 7812;
	TCNT1 = 0;
	TCCR1B = (1<<WGM12)|(0<<CS10);
	TIMSK = (1<<OCIE1A);


	InitLCD(FUNC_DEFAULT);
	
	printToDisplay_P(PSTR("  Sensore di  "));
	goToSecondLine();
	printToDisplay_P(PSTR("temperatura v1.1"));
	_delay_ms(2000);
	clearDisplay();
	printToDisplay_P(PSTR("   powered by   "));
	goToSecondLine();
	printToDisplay_P(PSTR("Alfredo Stefano"));
	_delay_ms(2000);
	clearDisplay();
	printToDisplay_P(PSTR("   Loading...   "));
	goToSecondLine();
	printToDisplay_P(PSTR("5 sec. remaining"));
	_delay_ms(1000);
	goToSecondLine();
	printToDisplay_P(PSTR("4 sec. remaining"));
	_delay_ms(1000);
	goToSecondLine();
	printToDisplay_P(PSTR("3 sec. remaining"));
	_delay_ms(1000);
	goToSecondLine();
	printToDisplay_P(PSTR("2 sec. remaining"));
	_delay_ms(1000);
	goToSecondLine();
	printToDisplay_P(PSTR("1 sec. remaining"));
	_delay_ms(1000);
	goToSecondLine();
	printToDisplay_P(PSTR("0 sec. remaining"));
	_delay_ms(200); 	
	clearDisplay();
	printToDisplay_P(PSTR("Temp.       "));
	printChar(223); // Corresponds to the character °
	printChar('C');
	goToSecondLine();
	printToDisplay_P(PSTR("-missing clock-"));

	ADCSRA |= (1<<ADSC);
	TCCR1B |= (4<<CS10);

	sei();

}


int main(void)
{

	reset();


	while(1);


	return 0;
}
