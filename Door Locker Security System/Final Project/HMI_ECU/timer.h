 /******************************************************************************
 *
 * Module: TIMER
 *
 * File Name: timer.h
 *
 * Description: Header file for the TIMER AVR driver
 *
 * Author: Mohamed Asran
 *
 *******************************************************************************/

#ifndef TIMER_H_
#define TIMER_H_

#include "std_types.h"

/*******************************************************************************
 *                         Types Declaration                                   *
 *******************************************************************************/
typedef enum
{
	NO_CLOCK,F_CPU_CLOCK,F_CPU_8,F_CPU_64,F_CPU_256,F_CPU_1024
}TIMER_Prescaler;

typedef enum
{
	TIMER0,TIMER1,TIMER2
}TIMER_ID;

typedef enum
{
	TIMER_NORMAL_MODE,TIMER_COMPARE_MODE
}TIMER_MODE;

typedef struct
{
	TIMER_ID TIMER_id;
	TIMER_MODE TIMER_mode;
	TIMER_Prescaler presaler;
	uint32 TIMER_initialValue;
	uint32 TIMER_compareValue;
}TIMER_ConfigType;

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
/*
 * Description :
 * Function responsible for initializing the Timer.
 */
void TIMER_Init(const TIMER_ConfigType * Config_Ptr);

/*
 * Description :
 * Function to set the Call Back function address.
 */
void TIMER_setCallBack(void(*a_ptr)(void));

/*
 * Description :
 * Function to disable the Timer.
 */
void TIMER_DeInit(void);

#endif /* TIMER_H_ */
