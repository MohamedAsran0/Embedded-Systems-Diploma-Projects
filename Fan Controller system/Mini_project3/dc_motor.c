 /******************************************************************************
 *
 * Module: DC_MOTOR
 *
 * File Name: dc_motor.c
 *
 * Description: Source file for the DC_MOTOR driver
 *
 * Author: Mohamed Asran
 *
 *******************************************************************************/

#include "dc_motor.h"
#include "gpio.h"
#include "pwm.h"
#include "common_macros.h" /* To use the macros like SET_BIT */

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/
/*
 * Description :
 * The Function responsible for setup the direction for the two
 * motor pins through the GPIO driver.
 */
void DcMotor_Init(void)
{
	/* Configure the direction for IN1, IN2 and EN1 pins as output pins */
	GPIO_setupPinDirection(DcMOTOR_PORT_ID, DcMOTOR_IN1_ID, PIN_OUTPUT);
	GPIO_setupPinDirection(DcMOTOR_PORT_ID, DcMOTOR_IN2_ID, PIN_OUTPUT);
	GPIO_setupPinDirection(DcMOTOR_EN1_PORT_ID, DcMOTOR_EN1_PIN_ID, PIN_OUTPUT);

	/* Stop the DC-Motor at the beginning */
	GPIO_writePin(DcMOTOR_PORT_ID, DcMOTOR_IN1_ID, LOGIC_LOW);
	GPIO_writePin(DcMOTOR_PORT_ID, DcMOTOR_IN2_ID, LOGIC_LOW);
}

/*
 * Description :
 * The function responsible for rotate the DC Motor CW/ or A-CW or
 * stop the motor based on the state input state value.
 */
void DcMotor_Rotate(DcMotor_State state,uint8 speed)
{
	GPIO_writePin(DcMOTOR_PORT_ID, DcMOTOR_IN1_ID, (state & 0x01)); /* Write the first bit of state in IN1 */
	GPIO_writePin(DcMOTOR_PORT_ID, DcMOTOR_IN2_ID, ((state & 0x02) >> 1)); /* Write the second bit of state in IN2 */
	PWM_Timer0_Start(speed);
}

