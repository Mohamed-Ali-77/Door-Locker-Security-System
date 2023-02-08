/*
 * Buzzer.c
 *
 *  Created on: Nov 6, 2022
 *      Author: Mohamed Ali
 */


#include "gpio.h"
#include "Buzzer.h"
void Buzzer_init(void){
	GPIO_setupPinDirection(BUZZER_PORT, BUZZER_PIN, PIN_OUTPUT);
}
void Buzzer_on(void){
	GPIO_writePin(BUZZER_PORT, BUZZER_PIN, LOGIC_HIGH);
}
void Buzzer_off(void){
	GPIO_writePin(BUZZER_PORT, BUZZER_PIN, LOGIC_LOW);
}
