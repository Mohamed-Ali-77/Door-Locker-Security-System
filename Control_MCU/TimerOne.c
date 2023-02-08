 /******************************************************************************
 *
 * Module: TimerOne
 *
 * File Name:TimerOne.c
 *
 * Description: Source file for the AVR TimerOne driver
 *
 * Author: Mohamed Ali
 *
 *******************************************************************************/
#include "TimerOne.h"
#include "avr/io.h"
#include "common_macros.h"
#include "avr/interrupt.h"
static volatile Timer1_ConfigType* Config_Ptr_static;
static volatile void(*g_Timer1_Call_Back_Ptr)(void);
volatile uint32 tick=0;
ISR(TIMER1_COMPA_vect){
	TCNT1=Config_Ptr_static->initial_value;
	(*g_Timer1_Call_Back_Ptr)();
}
ISR(TIMER1_COMPB_vect){
	TCNT1=Config_Ptr_static->initial_value;
	(*g_Timer1_Call_Back_Ptr)();
}
ISR(TIMER1_OVF_vect){
	TCNT1=Config_Ptr_static->initial_value;
	(*g_Timer1_Call_Back_Ptr)();

}
void Timer1_init(const Timer1_ConfigType * Config_Ptr){
	Config_Ptr_static=Config_Ptr;
	TCCR1A=(1<<FOC1A)|(1<<FOC1B);
	if(Config_Ptr->mode==CTC_TOP_OCR1A){
		TCCR1B|=(1<<WGM12);
	}
	if(Config_Ptr->mode==CTC_ICR1){
		TCCR1B|=(1<<WGM12);
		TCCR1B|=(1<<WGM13);
	}
	TCCR1B=Config_Ptr->prescaler;
	TCNT1=Config_Ptr->initial_value;
	if(Config_Ptr->mode==CTC_TOP_OCR1A){
		OCR1A=Config_Ptr->compare_value;
	}
	if(Config_Ptr->mode==CTC_ICR1){
		ICR1=Config_Ptr->compare_value;
	}
	if(Config_Ptr->mode==CTC_ICR1||Config_Ptr->mode==CTC_TOP_OCR1A){
		TIMSK|=(1<<OCIE1A);
	}
	else{
		TIMSK|=(1<<TOIE1);
	}

}
void Timer1_deInit(void){
	TCCR1B=0;
	TCNT1=0;

}
void Timer1_setCallBack(void(*a_ptr)(void)){
	g_Timer1_Call_Back_Ptr=a_ptr;
}


