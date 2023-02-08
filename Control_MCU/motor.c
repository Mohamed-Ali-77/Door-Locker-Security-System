/* *
 * File Name: motor.c
 *
 * Description: Source file for the Motor driver
 *
 * Author: Mohamed Ali
 *
 *******************************************************************************/
#include "motor.h"
#include "gpio.h"
#include "pwm.h"
#include "TimerOne.h"
void set_motor(void){
	tick++;
}
void DcMotor_Init(void){
	/*configure three pins as output*/
	GPIO_setupPinDirection(PORT_INPUT1_ID, PIN_INPUT1_ID,PIN_OUTPUT);
	GPIO_setupPinDirection(PORT_INPUT2_ID,PIN_INPUT2_ID,PIN_OUTPUT);
	/*STOP DC motor*/
	GPIO_writePin(PORT_INPUT1_ID,  PIN_INPUT1_ID, LOGIC_LOW);
	GPIO_writePin(PORT_INPUT2_ID,  PIN_INPUT2_ID, LOGIC_LOW);

	/*set timmer one*/
	tick=0;
	Timer1_ConfigType  Config_Ptr_timer;
	Config_Ptr_timer.prescaler=clk_8;
	Config_Ptr_timer.compare_value=0;
	Config_Ptr_timer.initial_value=0;
	Config_Ptr_timer.mode=normal;
	Timer1_setCallBack(&set_motor);
	Timer1_init(&Config_Ptr_timer);

}
void DcMotor_Rotate(DcMotor_State state,uint8 speed){
	switch(state){
		case STOP:
				GPIO_writePin(PORT_INPUT1_ID,  PIN_INPUT1_ID, LOGIC_LOW);
				GPIO_writePin(PORT_INPUT2_ID,  PIN_INPUT2_ID, LOGIC_LOW);
				break;
		case CLOCK_WISE:
				GPIO_writePin(PORT_INPUT1_ID,  PIN_INPUT1_ID, LOGIC_LOW);
				GPIO_writePin(PORT_INPUT2_ID,  PIN_INPUT2_ID, LOGIC_HIGH);
				break;
		case ANTI_ClOCK_WISE:
				GPIO_writePin(PORT_INPUT1_ID,  PIN_INPUT1_ID, LOGIC_HIGH);
				GPIO_writePin(PORT_INPUT2_ID,  PIN_INPUT2_ID, LOGIC_LOW);
				break;
	}
	PWM_Timer0_Start(speed);
}



