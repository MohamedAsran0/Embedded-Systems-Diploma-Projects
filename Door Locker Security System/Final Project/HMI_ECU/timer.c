 /******************************************************************************
 *
 * Module: TIMER
 *
 * File Name: timer.c
 *
 * Description: Source file for the TIMER AVR driver
 *
 * Author: Mohamed Asran
 *
 *******************************************************************************/

#include "timer.h"
#include "avr/io.h" /* To use the TIMER Registers */
#include <avr/interrupt.h> /* For TIMER ISR */

/*******************************************************************************
 *                           Global Variables                                  *
 *******************************************************************************/

/* Global variables to hold the address of the call back function in the application */
static volatile void (*g_callBackPtr)(void) = NULL_PTR;

/*******************************************************************************
 *                       Interrupt Service Routines                            *
 *******************************************************************************/

	/************************ TIMER0 ************************/
ISR(TIMER0_OVF_vect)
{
	if(g_callBackPtr != NULL_PTR)
	{
		/* Call the Call Back function in the application */
		(*g_callBackPtr)();
	}
}

ISR(TIMER0_COMP_vect)
{
	if(g_callBackPtr != NULL_PTR)
	{
		/* Call the Call Back function in the application */
		(*g_callBackPtr)();
	}
}

	/************************ TIMER1 ************************/
ISR(TIMER1_OVF_vect)
{
	if(g_callBackPtr != NULL_PTR)
	{
		/* Call the Call Back function in the application */
		(*g_callBackPtr)();
	}
}

ISR(TIMER1_COMPA_vect)
{
	if(g_callBackPtr != NULL_PTR)
	{
		/* Call the Call Back function in the application */
		(*g_callBackPtr)();
	}
}

	/************************ TIMER2 ************************/
ISR(TIMER2_OVF_vect)
{
	if(g_callBackPtr != NULL_PTR)
	{
		/* Call the Call Back function in the application */
		(*g_callBackPtr)();
	}
}

ISR(TIMER2_COMP_vect)
{
	if(g_callBackPtr != NULL_PTR)
	{
		/* Call the Call Back function in the application */
		(*g_callBackPtr)();
	}
}

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/
/*
 * Description :
 * Function responsible for initializing the Timer.
 */
void TIMER_Init(const TIMER_ConfigType * Config_Ptr)
{
	/************************ TIMER0 ************************/
	if(Config_Ptr->TIMER_id == TIMER0)
	{
		if(Config_Ptr->TIMER_mode == TIMER_NORMAL_MODE)
		{
			/* configure the timer0 control register
			 * 1. Normal mode FOC0=1
			 * 2. Normal Mode WGM01=0 & WGM00=0
			 * 3. Normal port operation COM00=0 & COM01=0
			 */
			TCCR0 = (1<<FOC0);

			/* Enable Timer0 Overflow Interrupt */
			TIMSK |= (1<<TOIE0);
		}

		else if(Config_Ptr->TIMER_mode == TIMER_COMPARE_MODE)
		{
			/* configure the timer0 control register
			 * 1. Compare mode FOC0=1
			 * 2. Compare Mode WGM01=1 & WGM00=0
			 * 3. Normal port operation COM00=0 & COM01=0
			 */
			TCCR0 = (1<<FOC0) | (1<<WGM01);

			/* Enable Timer0 Compare Interrupt */
			TIMSK |= (1<<OCIE0);

			/* Set Timer0 Compare Value */
			OCR0 = (Config_Ptr->TIMER_compareValue);
		}

		/*
		 * Adjust the prescaler by inserting the three bits of the required prescaler
		 * value in bits ( CS00 & CS01 & CS02 ) of TCCR0 Register
		 */
		TCCR0 |= (Config_Ptr->presaler);

		/* Set Timer0 Initial Value */
		TCNT0 = (Config_Ptr->TIMER_initialValue);
	}

	/************************ TIMER1 ************************/

	if(Config_Ptr->TIMER_id == TIMER1)
	{
		if(Config_Ptr->TIMER_mode == TIMER_NORMAL_MODE)
		{
			/* configure the timer1 control register TCCR1A
			 * 1. Disconnect OC1A and OC1B  COM1A1=0 COM1A0=0 COM1B0=0 COM1B1=0
			 * 2. FOC1A=1 FOC1B=0
			 * 3. Normal Mode WGM10=1 WGM11=1
			 */
			TCCR1A = (1<<FOC1A) | (1<<WGM10) | (1<<WGM11);

			/* configure the timer1 control register TCCR1B
			 * 1. Normal Mode WGM12=0 WGM13=0
			 */
			TCCR1B = 0;

			/* Enable Timer1 Overflow Interrupt */
			TIMSK |= (1<<TOIE1);
		}

		else if(Config_Ptr->TIMER_mode == TIMER_COMPARE_MODE)
		{
			/* Configure timer1 control register TCCR1A
			 * 1. Disconnect OC1A and OC1B  COM1A1=0 COM1A0=0 COM1B0=0 COM1B1=0
			 * 2. FOC1A=1 FOC1B=0
			 * 3. CTC Mode WGM10=0 WGM11=0 (Mode Number 4)
			 */
			TCCR1A = (1<<FOC1A);

			/* Configure timer1 control register TCCR1B
			 * 1. CTC Mode WGM12=1 WGM13=0 (Mode Number 4)
			 */
			TCCR1B = (1<<WGM12);

			/* Enable Timer1 Compare Interrupt */
			TIMSK |= (1<<OCIE1A);

			/* Set Timer1 Compare Value */
			OCR1A = (Config_Ptr->TIMER_compareValue);
		}

		/*
		 * Adjust the prescaler by inserting the three bits of the required prescaler
		 * value in bits ( CS10 & CS11 & CS12 ) of TCCR1B Register
		 */
		TCCR1B |= (Config_Ptr->presaler);

		/* Set Timer1 Initial Value */
		TCNT1 = (Config_Ptr->TIMER_initialValue);
	}

	/************************ TIMER2 ************************/

	if(Config_Ptr->TIMER_id == TIMER2)
	{
		if(Config_Ptr->TIMER_mode == TIMER_NORMAL_MODE)
		{
			/* configure the timer2 control register
			 * 1. Normal mode FOC2=1
			 * 2. Normal Mode WGM21=0 & WGM20=0
			 * 3. Normal port operation COM00=0 & COM01=0
			 */
			TCCR2 = (1<<FOC2);

			/* Enable Timer2 Overflow Interrupt */
			TIMSK |= (1<<TOIE2);
		}

		else if(Config_Ptr->TIMER_mode == TIMER_COMPARE_MODE)
		{
			/* configure the timer2 control register
			 * 1. Compare mode FOC2=1
			 * 2. Compare Mode WGM21=1 & WGM20=0
			 * 3. Normal port operation COM00=0 & COM01=0
			 */
			TCCR2 = (1<<FOC2) | (1<<WGM21);

			/* Enable Timer2 Compare Interrupt */
			TIMSK |= (1<<OCIE2);

			/* Set Timer2 Compare Value */
			OCR2 = (Config_Ptr->TIMER_compareValue);
		}

		/*
		 * Adjust the prescaler by inserting the three bits of the required prescaler
		 * value in bits ( CS20 & CS21 & CS22 ) of TCCR2 Register
		 */
		TCCR2 |= (Config_Ptr->presaler);

		/* Set Timer2 Initial Value */
		TCNT2 = (Config_Ptr->TIMER_initialValue);
	}
}

/*
 * Description :
 * Function to set the Call Back function address.
 */
void TIMER_setCallBack(void(*a_ptr)(void))
{
	/* Save the address of the Call back function in a global variable */
	g_callBackPtr = a_ptr;
}

/*
 * Description :
 * Function to disable the Timer.
 */
void TIMER_DeInit(void)
{
	/************************ TIMER0 ************************/

	/* Clear All Timer0 Registers and stop the clock */
	TCCR0 = 0;
	TCNT0 = 0;

	/* Disable Timer0 Overflow Interrupt */
	TIMSK &= ~(1<<TOIE0);

	/* Disable Timer0 Compare Interrupt */
	TIMSK &= ~(1<<OCIE0);

	/************************ TIMER1 ************************/

	/* Clear All Timer1 Registers and stop the clock */
	TCCR1A = 0;
	TCCR1B = 0;
	TCNT1 = 0;

	/* Disable Timer1 Overflow Interrupt */
	TIMSK &= ~(1<<TOIE1);

	/* Disable Timer1 Compare Interrupt */
	TIMSK &= ~(1<<OCIE1A);

	/************************ TIMER2 ************************/

	/* Clear All Timer2 Registers and stop the clock */
	TCCR2 = 0;
	TCNT2 = 0;

	/* Disable Timer2 Overflow Interrupt */
	TIMSK &= ~(1<<TOIE2);

	/* Disable Timer2 Compare Interrupt */
	TIMSK &= ~(1<<OCIE2);
}
