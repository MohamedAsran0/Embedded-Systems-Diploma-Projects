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
#include "timer.h"

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
	GPIO_setupPinDirection(DC_MOTOR_PORT_ID, DC_MOTOR_IN1_PIN_ID, PIN_OUTPUT);
	GPIO_setupPinDirection(DC_MOTOR_PORT_ID, DC_MOTOR_IN2_PIN_ID, PIN_OUTPUT);
	GPIO_setupPinDirection(DC_MOTOR_EN1_PORT_ID, DC_MOTOR_EN1_PIN_ID, PIN_OUTPUT);

	/* Stop the DC-Motor at the beginning */
	GPIO_writePin(DC_MOTOR_PORT_ID, DC_MOTOR_IN1_PIN_ID, LOGIC_LOW);
	GPIO_writePin(DC_MOTOR_PORT_ID, DC_MOTOR_IN2_PIN_ID, LOGIC_LOW);
}

/*
 * Description :
 * The function responsible for rotate the DC Motor CW , A-CW or
 * stop the motor based on the input state value.
 */
void DcMotor_Rotate(DcMotor_State state)
{
	GPIO_writePin(DC_MOTOR_PORT_ID, DC_MOTOR_IN1_PIN_ID, (state & 0x01)); /* Write the first bit of state in IN1 */
	GPIO_writePin(DC_MOTOR_PORT_ID, DC_MOTOR_IN2_PIN_ID, ((state & 0x02) >> 1)); /* Write the second bit of state in IN2 */

	/* Rotate the motor with its maximum speed */
	GPIO_writePin(DC_MOTOR_EN1_PORT_ID, DC_MOTOR_EN1_PIN_ID, LOGIC_HIGH);
}

