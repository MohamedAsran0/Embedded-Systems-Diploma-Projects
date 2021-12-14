 /******************************************************************************
 *
 * Module: BUZZER
 *
 * File Name: buzzer.c
 *
 * Description: Source file for BUZZER driver
 *
 * Author: Mohamed Asran
 *
 *******************************************************************************/

#include "buzzer.h"
#include "gpio.h"

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/
/*
 * Description :
 * The Function responsible for setup the direction for the buzzer
 * pin through the GPIO driver.
 */
void BUZZER_Init(void)
{
	/* Configure the direction of buzzer pin as output pin */
	GPIO_setupPinDirection(BUZZER_PORT_ID, BUZZER_PIN_ID, PIN_OUTPUT);

	/* Turn off the buzzer at the beginning */
	GPIO_writePin(BUZZER_PORT_ID, BUZZER_PIN_ID, LOGIC_LOW);
}

/*
 * Description :
 * The Function responsible for turning the buzzer on.
 */
void BUZZER_ON(void)
{
	/* Turn on the buzzer */
	GPIO_writePin(BUZZER_PORT_ID, BUZZER_PIN_ID, LOGIC_HIGH);
}

/*
 * Description :
 * The Function responsible for turning the buzzer off.
 */
void BUZZER_OFF(void)
{
	/* Turn off the buzzer */
	GPIO_writePin(BUZZER_PORT_ID, BUZZER_PIN_ID, LOGIC_LOW);
}
