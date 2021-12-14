 /******************************************************************************
 *
 * Module: DC_MOTOR
 *
 * File Name: dc_motor.h
 *
 * Description: Header file for the DC_MOTOR driver
 *
 * Author: Mohamed Asran
 *
 *******************************************************************************/

#ifndef DC_MOTOR_H_
#define DC_MOTOR_H_

#include "std_types.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
#define DC_MOTOR_PORT_ID            PORTB_ID

#define DC_MOTOR_IN1_PIN_ID         PIN0_ID
#define DC_MOTOR_IN2_PIN_ID         PIN1_ID

#define DC_MOTOR_EN1_PORT_ID        PORTB_ID
#define DC_MOTOR_EN1_PIN_ID         PIN2_ID

/*******************************************************************************
 *                         Types Declaration                                   *
 *******************************************************************************/
typedef enum
{
	DC_MOTOR_STOP,DC_MOTOR_CW,DC_MOTOR_ACW
}DcMotor_State;

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description :
 * The Function responsible for setup the direction for the two
 * motor pins through the GPIO driver.
 */
void DcMotor_Init(void);

/*
 * Description :
 * The function responsible for rotate the DC Motor CW , A-CW or
 * stop the motor based on the input state value.
 */
void DcMotor_Rotate(DcMotor_State state);

#endif /* DC_MOTOR_H_ */
