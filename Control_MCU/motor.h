/* *
 * File Name: motor.h
 *
 * Description: Header file for DC Motor
 *
 * Author: Mohamed Ali
 *
 *******************************************************************************/
#ifndef MOTOR_H_
#define MOTOR_H_
#include "std_types.h"
/* connect enable , input and input2*/
#define PORT_ENABLE      PORTB_ID
#define PIN_ENABLE       PIN3_ID
#define PORT_INPUT1_ID   PORTB_ID
#define PORT_INPUT2_ID   PORTB_ID
#define PIN_INPUT1_ID    PIN0_ID
#define PIN_INPUT2_ID    PIN1_ID
typedef enum{
	STOP,CLOCK_WISE,ANTI_ClOCK_WISE
}DcMotor_State;
void DcMotor_Init(void);
void DcMotor_Rotate(DcMotor_State state,uint8 speed);
void set_motor(void);
#endif /* MOTOR_H_ */
