/*
 ============================================================================
 Name        : Mini_Project2.c
 Author      : Mohamed Asran
 Description : Stop Watch System
 ============================================================================
 */

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

unsigned char sec1 = 0;
unsigned char sec2 = 0;
unsigned char min1 = 0;
unsigned char min2 = 0;
unsigned char hou1 = 0;
unsigned char hou2 = 0;

void Timer1_CTC_Init()
{
	/** Enable Timer1 at CTC mode with Prescaler 1024 **/

	TCCR1A = (1<<FOC1A);
	TCCR1B = (1<<WGM12) | (1<<CS10) | (1<<CS12);
	TCNT1 = 0;
	OCR1A = 1000;
	TIMSK |= (1<<OCIE1A); // Enable Compare Interrupt

	/** Timer1 Will Make an Interrupt Every 1sec. **/
}

void INT0_Init()
{
	GICR |= (1<<INT0); // Enable INT0
	MCUCR |= (1<<ISC01); //Generate Interrupt with falling edge
	MCUCR &= ~(1<<ISC00);
	DDRD &= ~(1<<PD2); // Configure pin 2 in PORTD as input pin
	PORTD |= (1<<PD2); // Activate the internal pull up resistor at PD2
}

void INT1_Init()
{
	GICR |= (1<<INT1); // Enable INT1
	MCUCR |= (1<<ISC10) | (1<<ISC11); //Generate Interrupt with rising edge
	DDRD &= ~(1<<PD3); // Configure pin 3 in PORTD as input pin
}

void INT2_Init()
{
	GICR |= (1<<INT2); // Enable INT2
	MCUCSR &= ~(1<<ISC2); //Generate Interrupt with falling edge
	DDRB &= ~(1<<PB2); // Configure pin 2 in PORTB as input pin
	PORTB |= (1<<PB2); // Activate the internal pull up resistor at PB2
}

int main()
{
	SREG |= (1<<7); // Enable the Global Interrupt

	DDRC |= 0x0F; // Configure first 4 pins in PORTC as output pins
	PORTC &= 0xF0; // Initialize the OUTPUT of First 4 PINS in PORTC with ZERO

	DDRA |= 0x3F; //  Configure first 6 pins in PORTA as output pins
	PORTA &= 0xC0; // Initialize the OUTPUT of First 6 PINS in PORTA with ZERO

	INT0_Init();
	INT1_Init();
	INT2_Init();
	Timer1_CTC_Init();

	while(1)
	{
		/** Display First Digit Only **/
		PORTA = (1<<PA0);
		PORTC = (PORTC & 0xF0) | (sec1 & 0x0F);
		_delay_ms(3);

		/** Display Second Digit Only **/
		PORTA = (1<<PA1);
		PORTC = (PORTC & 0xF0) | (sec2 & 0x0F);
		_delay_ms(3);

		/** Display Third Digit Only **/
		PORTA = (1<<PA2);
		PORTC = (PORTC & 0xF0) | (min1 & 0x0F);
		_delay_ms(3);

		/** Display Fourth Digit Only **/
		PORTA = (1<<PA3);
		PORTC = (PORTC & 0xF0) | (min2 & 0x0F);
		_delay_ms(3);

		/** Display Fifth Digit Only **/
		PORTA = (1<<PA4);
		PORTC = (PORTC & 0xF0) | (hou1 & 0x0F);
		_delay_ms(3);

		/** Display Sixth Digit Only **/
		PORTA = (1<<PA5);
		PORTC = (PORTC & 0xF0) | (hou2 & 0x0F);
		_delay_ms(3);
	}
}

ISR(TIMER1_COMPA_vect)
{
	sec1++;
	if(sec1 == 10)
	{
		sec1 = 0;
		sec2++;
	}
	if(sec2 == 6)
	{
		sec2 = 0;
		min1++;
	}
	if(min1 == 10)
	{
		min1 = 0;
		min2++;
	}
	if(min2 == 6)
	{
		min2 = 0;
		hou1++;
	}
	if(hou1 == 10)
	{
		hou1 = 0;
		hou2++;
	}
	if(hou2 == 6)
	{
		sec1 = 0;
		sec2 = 0;
		min1 = 0;
		min2 = 0;
		hou1 = 0;
		hou2 = 0;
	}
}

ISR(INT0_vect)
{
	sec1 = 0;
	sec2 = 0;
	min1 = 0;
	min2 = 0;
	hou1 = 0;
	hou2 = 0;
}

ISR(INT1_vect)
{
	TCCR1B &= ~(1<<CS10) & ~(1<<CS12); // Stop the Clock
}

ISR(INT2_vect)
{
	TCCR1B |= (1<<CS10) | (1<<CS12); // Enable the Clock With Prescaler 1024
}
