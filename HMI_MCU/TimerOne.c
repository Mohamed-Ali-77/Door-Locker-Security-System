 /******************************************************************************
 *
 * Module: GPIO
 *
 * File Name: TimerOne.c
 *
 * Description: Source file for the AVR Timer_ONE driver
 *
 * Author: Mohamed Ali
 *
 *******************************************************************************/
#include "TimerOne.h"
#include "avr/io.h"
#include "common_macros.h"
#include "avr/interrupt.h"
//static volatile Timer1_ConfigType* Config_Ptr_static;
static volatile void(*g_Timer1_Call_Back_Ptr)(void);
volatile uint32 tick=0;

ISR(TIMER1_OVF_vect){
	(*g_Timer1_Call_Back_Ptr)();
}
void Timer1_init(const Timer1_ConfigType * Config_Ptr){
	TCCR1A=(1<<FOC1A)|(1<<FOC1B);
	TCCR1B=Config_Ptr->prescaler;
	TCNT1=Config_Ptr->initial_value;
	TIMSK|=(1<<TOIE1);
}
void Timer1_deInit(void){
	TCCR1B=0;
	TCNT1=0;
}
void Timer1_setCallBack(void(*a_ptr)(void)){
	g_Timer1_Call_Back_Ptr=a_ptr;
}


