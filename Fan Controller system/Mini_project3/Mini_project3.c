/*
 ================================================================================================
 Name        : Mini_Project3.c
 Author      : Mohamed Asran
 Description : Fan Controller System
 ================================================================================================
 */

#include "lcd.h"
#include "dc_motor.h"
#include "lm35_sensor.h"
#include "adc.h" /* To initialize ADC */

int main()
{
	uint8 temp;

	/* Create configuration structure for ADC driver */
	ADC_ConfigType ADC_Config = {INTERNAL_TURNON,F_CPU_8};

	LCD_init(); /* initialize LCD driver */
	DcMotor_Init(); /* initialize DC-Motor driver */
	ADC_init(&ADC_Config); /* initialize ADC driver */

	/* Display this string "Fan is OFF" only once on LCD at the first row */
	LCD_displayString("Fan is OFF");

	/* Display this string "Temp =    C" only once on LCD at the second row */
	LCD_displayStringRowColumn(1, 0, "Temp =    C");

	while(1)
	{
		/* Get the temperature from the sensor */
		temp = LM35_getTemperature();

		/* If the temperature is >= 120 */
		if(temp >= 120)
		{
			DcMotor_Rotate(CLOCKWISE, 100); /* Rotate the motor clockwise with 100% of its maximum speed */
			LCD_moveCursor(0, 7);
			LCD_displayString("ON ");
			LCD_moveCursor(1, 7);
			LCD_intgerToString(temp);
		}

		/* If the temperature is >= 90 */
		else if(temp >= 90)
		{
			DcMotor_Rotate(CLOCKWISE, 75); /* Rotate the motor clockwise with 75% of its maximum speed */
			LCD_moveCursor(0, 7);
			LCD_displayString("ON ");
			LCD_moveCursor(1, 7);

			if(temp >= 100)
			{
				LCD_intgerToString(temp);
			}
			else
			{
				LCD_intgerToString(temp);
				LCD_displayCharacter(' ');
			}
		}

		/* If the temperature is >= 60 */
		else if(temp >= 60)
		{
			DcMotor_Rotate(CLOCKWISE, 50); /* Rotate the motor clockwise with 50% of its maximum speed */
			LCD_moveCursor(0, 7);
			LCD_displayString("ON ");
			LCD_moveCursor(1, 7);
			LCD_intgerToString(temp);
		}

		/* If the temperature is >= 30 */
		else if(temp >= 30)
		{
			DcMotor_Rotate(CLOCKWISE, 25); /* Rotate the motor clockwise with 25% of its maximum speed */
			LCD_moveCursor(0, 7);
			LCD_displayString("ON ");
			LCD_moveCursor(1, 7);
			LCD_intgerToString(temp);
		}

		/* If the temperature is < 30 */
		else if(temp < 30)
		{
			DcMotor_Rotate(STOP, 0); /* Stop the motor */
			LCD_moveCursor(0, 7);
			LCD_displayString("OFF");
			LCD_moveCursor(1, 7);

			if(temp >= 10)
			{
				LCD_intgerToString(temp);
			}
			else
			{
				LCD_intgerToString(temp);
				LCD_displayCharacter(' ');
			}
		}
	}
}
