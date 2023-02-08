/*
 * Buzzer.h
 *
 *  Created on: Nov 4, 2022
 *      Author: Mohamed Ali
 */

#ifndef BUZZER_H_
#define BUZZER_H_

#define BUZZER_PIN  PIN3_ID
#define BUZZER_PORT PORTA_ID

void Buzzer_init(void);
void Buzzer_on(void);
void Buzzer_off(void);


#endif /* BUZZER_H_ */
