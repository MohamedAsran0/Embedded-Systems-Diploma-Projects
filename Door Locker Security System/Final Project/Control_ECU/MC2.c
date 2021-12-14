/*
 ================================================================================================
 Name        : MC2.c
 Author      : Mohamed Asran
 Description : MC2 code in Door Locker Security System project
 ================================================================================================
 */

#include "uart.h"
#include "twi.h"
#include "timer.h"
#include "buzzer.h"
#include "external_eeprom.h"
#include "dc_motor.h"
#include <util/delay.h> /* For the delay functions */
#include <avr/io.h> /* To use the SREG register */

/****************************** Definitions ******************************/
#define pass_true     0x01
#define pass_false    0x02

/**************************** Global Variables ****************************/
volatile uint8 g_tick = 0;

/************************** Functions Prototypes **************************/
void Door_processing();
void Buzzer_processing();

/******************************** Main ********************************/
int main()
{
	uint8 i=0,mainOptionsKey, var, error_counter=0;
	uint8 password[5], password_check[5], password_status = pass_true;

	/* Create configuration structure for UART driver */
	UART_ConfigType UART_Config = {UART_8_BIT_PER_FRAME,UART_DISABLE_PARITY,UART_1_STOP_BIT,9600};

	/* Create configuration structure for TIMER driver with
	 * initial value = 0 & compare value = 7813
	 * which generates an interrupt every one second
	 */
	TIMER_ConfigType TIMER_Config = {TIMER1,TIMER_COMPARE_MODE,F_CPU_1024,0,7813};

	/* Initialize the UART driver */
	UART_init(&UART_Config);

	/* Initialize the twi driver with bit rate 400.000 kbps &
	 * my address = 0x01
	 */
	TWI_init(400000, 0x01);

	/* Initialize the Buzzer driver */
	BUZZER_Init();

	/* Initialize the DC-Motor driver */
	DcMotor_Init();

	/* Enable Global Interrupt I-Bit */
	SREG |= (1<<7);

	while(1)
	{
/****************************** Step 1 ******************************/

		if(error_counter != 3){
			/* Stay in this loop until the password is correct */
			do{

				/* Recieve the password from MC1 */
				for(i=0; i<5; i++)
				{
					password[i] = UART_recieveByte();
				}

				/* Recieve the password again from MC1 */
				for(i=0; i<5; i++)
				{
					password_check[i] = UART_recieveByte();
				}

				/* Check if the password is true */
				for(i=0; i<5; i++)
				{
					if(password[i] != password_check[i])
					{
						password_status = pass_false;
						break;
					}
					else
					{
						password_status = pass_true;
					}
				}

				if(password_status == pass_true)
				{
					/* Send true password to MC1 */
					UART_sendByte(pass_true);

					/* Write the password to the memory */
					for(i=0; i<5; i++)
					{
						EEPROM_writeByte(0x0302+i, password[i]);
						/* delay time as the eeprom take 10ms to make a write*/
						_delay_ms(10) ;
					}
				}
				else
				{
					/* Send false password to MC1 */
					UART_sendByte(pass_false);
				}

			}while(password_status == pass_false);

		}

/****************************** Step 2 ******************************/

		error_counter = 0;

		/* Recieve the main options key from MC1 */
		mainOptionsKey = UART_recieveByte();

		do{
			/* Recieve the password from MC1 */
			for(i=0; i<5; i++)
			{
				password[i] = UART_recieveByte();
			}

			/* Check if the password is true */
			for(i=0; i<5; i++)
			{
				/* Read the saved password from the memory
				 * and compare it with the recieved password
				 */
				EEPROM_readByte(0x0302+i, &var);
				/* delay time as the eeprom take 10ms to make a read*/
				_delay_ms(10) ;

				if(password[i] != var)
				{
					password_status = pass_false;
					break;
				}
				else
				{
					password_status = pass_true;
				}
			}

			if(password_status == pass_true)
			{
				/* Send true password to MC1 */
				UART_sendByte(pass_true);
			}
			else
			{
				/* Send false password to MC1 */
				UART_sendByte(pass_false);
				error_counter++;
			}
		}while((password_status == pass_false) && (error_counter < 3));


		/* Recieve any default data from MC1 to initialize the
		 * timer with it at the same time
		 */
		var = UART_recieveByte();

/****************************** Step 3 ******************************/

		/* If the input password is wrong for three trials */
		if(error_counter == 3)
		{
			/* Set the call back function */
			TIMER_setCallBack(Buzzer_processing);

			/* Initialize the TIMER Driver */
			TIMER_Init(&TIMER_Config);

			/* Waiting for one minute */
			while(g_tick != 60)
			{
				/* Trigger the Buzzer */
				BUZZER_ON();
				_delay_ms(500);
				BUZZER_OFF();
				_delay_ms(500);
			}

			g_tick = 0;
		}

		/* If the chosen key is to open the door */
		if((mainOptionsKey == '+') && (error_counter <3))
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
/* Call back function of door processing */
void Door_processing()
{
	g_tick++;

	/* After one second */
	if(g_tick == 1)
	{
		/* Rotate the motor CW */
		DcMotor_Rotate(DC_MOTOR_CW);
	}

	/* After 15 seconds */
	else if(g_tick == 15)
	{
		/* Stop the motor */
		DcMotor_Rotate(DC_MOTOR_STOP);
	}

	/* After 18 seconds */
	else if(g_tick == 18)
	{
		/* Rotate the motor ACW */
		DcMotor_Rotate(DC_MOTOR_ACW);
	}

	/*After 33 seconds */
	else if(g_tick == 33)
	{
		/* Stop the motor */
		DcMotor_Rotate(DC_MOTOR_STOP);

		/*Stop the timer */
		TIMER_DeInit();
	}
}

/* Call back function of buzzer processing */
void Buzzer_processing()
{
	g_tick++;

	/* After one minute */
	if(g_tick == 60)
	{
		/*Stop the timer */
		TIMER_DeInit();
	}
}
