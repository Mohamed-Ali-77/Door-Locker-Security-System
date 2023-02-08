 /******************************************************************************
 *
 * Module: GPIO
 *
 * File Name: TimerOne.c
 *
 * Description:Header file for the AVR Timer_ONE driver
 *
 * Author: Mohamed Ali
 *
 *******************************************************************************/
#ifndef TIMERONE_H_
#define TIMERONE_H_

#include "std_types.h"
extern volatile uint32 tick;
typedef enum{
	No_clk,clk_1,clk_8,clk_64,clk_256,clk_1024,External_clk_T1_failing_edge,External_clk_T1_rising_edge
}Timer1_Prescaler;

typedef enum{
	normal,PWM_Phase_Correct_8,PWM_Phase_Correct_9,PWM_Phase_Correct_10,CTC_TOP_OCR1A,FAST_PWM_8,FAST_PWM_9,FAST_PWM_10,
	PWM_Phase_Frequency_Correct_ICR1,PWM_Phase_Frequency_Correct_OCR1A,PWMP_hase_Correct_ICR1,PWMP_hase_Correct_OCR1A,
	CTC_ICR1,FAST_PWM_ICR1,FAST_PWM_OCR1A
}Timer1_Mode;

typedef struct {
 uint16 initial_value;
 uint16 compare_value;      // it will be used in compare mode only.
 Timer1_Prescaler prescaler;
 Timer1_Mode mode;
} Timer1_ConfigType;

void Timer1_init(const Timer1_ConfigType * Config_Ptr);
void Timer1_deInit(void);
void Timer1_setCallBack(void(*a_ptr)(void));



#endif /* TIMERONE_H_ */
