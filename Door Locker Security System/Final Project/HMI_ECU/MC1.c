/*
 ================================================================================================
 Name        : MC1.c
 Author      : Mohamed Asran
 Description : MC1 code in Door Locker Security System project
 ================================================================================================
 */

#include "timer.h"
#include "lcd.h"
#include "keypad.h"
#include "uart.h"
#include <avr/io.h> /* To use the SREG register */
#include <util/delay.h> /* For the delay functions */

/****************************** Definitions ******************************/
#define pass_true     0x01
#define pass_false    0x02

/**************************** Global Variables ****************************/
volatile uint8 g_tick = 0;

/************************** Functions Prototypes **************************/
void Recieve_password();
void Door_processing();
void Buzzer_processing();

/******************************** Main ********************************/
int main()
{
	uint8 error_counter=0, mainOptionsKey, password_status;

	/* Create configuration structure for UART driver */
	UART_ConfigType UART_Config = {UART_8_BIT_PER_FRAME,UART_DISABLE_PARITY,UART_1_STOP_BIT,9600};

	/* Create configuration structure for TIMER driver with
	 * initial value = 0 & compare value = 7813
	 * which generates an interrupt every one second
	 */
	TIMER_ConfigType TIMER_Config = {TIMER1,TIMER_COMPARE_MODE,F_CPU_1024,0,7813};

	/* Initialize the UART driver */
	UART_init(&UART_Config);

	/* Initialize the LCD Driver */
	LCD_init();

	/* Enable Global Interrupt I-Bit */
	SREG |= (1<<7);


	while(1)
	{
/****************************** Step 1 ******************************/

		if(error_counter != 3)
		{
			/* Stay in this loop until the password is correct */
			do{
				LCD_clearScreen();

				LCD_displayString("Please enter new password :");
				LCD_moveCursor(1, 0);

				Recieve_password();

				LCD_clearScreen();

				LCD_displayString("Please re-enter password :");
				LCD_moveCursor(1, 0);

				Recieve_password();

				/* Recieve the password status if it's
				 * right or wrong password
				 */
				password_status = UART_recieveByte();

			}while(password_status == pass_false);
		}

/****************************** Step 2 ******************************/

		error_counter = 0;

		/* Go to Main options */
		LCD_clearScreen();

		LCD_displayString("+ : Open Door");
		LCD_moveCursor(1, 0);
		LCD_displayString("- : Change Password");

		/* Take the pressed key until it's equal to '+' or '-' */
		do{
			mainOptionsKey = KEYPAD_getPressedKey();

			/* Press time */
			_delay_ms(500);

		}while((mainOptionsKey != '+') && (mainOptionsKey != '-'));

		/* Send the key number to the second MC */
		UART_sendByte(mainOptionsKey);

		/* Take the password */
		do{
			/* If the password entered is wrong */
			if(error_counter > 0)
			{
				LCD_clearScreen();
				LCD_displayString("Wrong Password");
				_delay_ms(700);
			}
			LCD_clearScreen();

			LCD_displayString("Please enter password :");
			LCD_moveCursor(1, 0);

			Recieve_password();

			password_status = UART_recieveByte();

			error_counter++;

		}while((password_status == pass_false) && (error_counter < 3));

		/* Send any default data to MC2 to initialize the
		 * timer with it at the same time
		 */
		UART_sendByte(mainOptionsKey);

/****************************** Step 3 ******************************/

		/* If the input password is wrong for three trials */
		if(error_counter == 3)
		{
			/* Set the call back function */
			TIMER_setCallBack(Buzzer_processing);

			/* Initialize the TIMER Driver */
			TIMER_Init(&TIMER_Config);

			/* Waiting for one minute */
			while(g_tick != 60){}

			g_tick = 0;
		}

		/* If the chosen key is to open the door */
		if((mainOptionsKey == '+') && (error_counter < 3))
		{

			/* Set the call back function */
			TIMER_setCallBack(Door_processing);

			/* Initialize the TIMER Driver */
			TIMER_Init(&TIMER_Config);

			/* Wait Until the door is unlocked then locked again */
			while(g_tick != 33){}

			g_tick = 0;

			/* Make the error counter equals 3
			 * to jump into the main options
			 */
			error_counter = 3;
		}

	}
}

/************************** Functions Definitions **************************/
/* Function of recieving the password from the keypad */
void Recieve_password()
{
	uint8 i=0, key;
	for(i=0; i<5; i++)
	{
		/* Get the pressed key */
		key = KEYPAD_getPressedKey();

		/* Send the key number to the second MC */
		UART_sendByte(key);

		/* Show '*' on the LCD */
		LCD_displayCharacter('*');

		/* Press time */
		_delay_ms(500);
	}

	/* Waiting for the "Enter" key which is '=' */
	do{
		key = KEYPAD_getPressedKey();

		/* Press time */
		_delay_ms(500);

	}while(key != '=');
}

/* Call back function of door processing */
void Door_processing()
{
	g_tick++;

	/* After one second */
	if(g_tick == 1)
	{
		LCD_clearScreen();
		/* Display on the LCD "The Door is Unlocking" */
		LCD_displayString("The Door is Unlocking...");
	}

	/* After 18 seconds */
	else if(g_tick == 18)
	{
		LCD_clearScreen();
		/* Display on the LCD "The Door is Locking" */
		LCD_displayString("The Door is Locking...");
	}

	/*After 33 seconds */
	else if(g_tick == 33)
	{
		/* Clear the Screen */
		LCD_clearScreen();

		/*Stop the timer again */
		TIMER_DeInit();

	}
}

/* Call back function of buzzer processing */
void Buzzer_processing()
{
	g_tick++;

	/* After one second */
	if(g_tick == 1)
	{
		LCD_clearScreen();
		/* Display an error message on the LCD */
		LCD_displayString("Error!!!");
		LCD_moveCursor(1, 0);
		LCD_displayString("Calling 911...");
	}

	/* After one minute */
	if(g_tick == 60)
	{
		/* Clear the Screen */
		LCD_clearScreen();

		/*Stop the timer */
		TIMER_DeInit();
	}
}
