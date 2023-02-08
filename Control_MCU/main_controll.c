/*
 * main_ECU.c
 *
 *  Created on: Nov 6, 2022
 *      Author: Mohamed Ali
 */
#include "uart.h"
#include "string.h"
#include"std_types.h"
#include "avr/io.h"
#include <stdlib.h>
#include "twi.h"
#include "external_eeprom.h"
#include "util/delay.h"
#include "TimerOne.h"
#include "motor.h"
#include "Buzzer.h"

uint8 pass[6];
uint8 re_pass[6];
uint8 pass_from_memory[6];
void buzzer_timer(void){
	tick++;
}
void read_pass_from_memory(void){
	uint8 u8data;
	EEPROM_readByte(100, &u8data);
	pass_from_memory[0]=u8data;
	EEPROM_readByte(101, &u8data);
	_delay_ms(10);
	pass_from_memory[1]=u8data;
	EEPROM_readByte(102, &u8data);
	_delay_ms(10);
	pass_from_memory[2]=u8data;
	EEPROM_readByte(103, &u8data);
	_delay_ms(10);
	pass_from_memory[3]=u8data;
	EEPROM_readByte(104, &u8data);
	_delay_ms(10);
	pass_from_memory[4]=u8data;
	EEPROM_readByte(105, &u8data);
	_delay_ms(10);
	pass_from_memory[5]=u8data;
}
void write_pass_in_memory(void){
	uint8 u8data=pass[0];
	EEPROM_writeByte(100,u8data);
	_delay_ms(10);
	u8data=pass[1];
	EEPROM_writeByte(101,u8data);
	_delay_ms(10);
	u8data=pass[2];
	EEPROM_writeByte(102,u8data);
	_delay_ms(10);
	u8data=pass[3];
	EEPROM_writeByte(103,u8data);
	_delay_ms(10);
	u8data=pass[4];
	EEPROM_writeByte(104,u8data);
	_delay_ms(10);
	u8data=pass[5];
	EEPROM_writeByte(105,u8data);
	_delay_ms(10);
}
void step_three(void){
	DcMotor_Init();
}
void step_one(void){
	uint8 flag=1;
	uint8 step=0;
	UART_receiveString(pass);
	UART_receiveString(re_pass);
	flag=strcmp(pass,re_pass);
	while(flag!=0){
		step=1;
		UART_sendByte(step);
		UART_receiveString(pass);
		UART_receiveString(re_pass);
		flag=strcmp(pass,re_pass);
	}
	step=2;
	UART_sendByte(step);
	write_pass_in_memory();
}
int main(){
	SREG|=(1<<7);
	/*init UART*/
	UART_ConfigType  Config_Ptr_UART;
	Config_Ptr_UART.baud_rate=9600;
	Config_Ptr_UART.bit_data=eight_bit;
	Config_Ptr_UART.stop_bit=one_bit;
	Config_Ptr_UART.parity=disable_parity;
	UART_init(&Config_Ptr_UART);
	/*init TWI*/
	TWI_ConfigType Config_Ptr_twi;
	Config_Ptr_twi.address=1;
	Config_Ptr_twi.bit_rate=400000;
	TWI_init(&Config_Ptr_twi);
	uint8 match=1;
	uint8 make_step_one=1;
	while(1){
		if(make_step_one==1){
			step_one();
		}
		make_step_one=1;
		/*take string to compare with one in memory*/
		read_pass_from_memory();
		UART_receiveString(pass);
		uint8 flag=strcmp(pass,pass_from_memory);
		if(flag==0){
			match=1;
			UART_sendByte(match);
			uint8 number_of_step =UART_recieveByte();
			if(number_of_step==3){
				step_three();
				make_step_one=0;
				tick=0;
				DcMotor_Rotate(CLOCK_WISE,100);
				while(tick<229){
				}
				tick=0;
				DcMotor_Rotate(STOP,99);
				while(tick <46){
				}
				tick=0;
				DcMotor_Rotate(ANTI_ClOCK_WISE,99);
				while(tick<229){
				}
				Timer1_deInit();
				DcMotor_Rotate(STOP,99);
			}
		}
		else{
			match=0;
			UART_sendByte(match);
			UART_receiveString(pass);
			flag=strcmp(pass,pass_from_memory);
			if(flag==0){
				match=1;
				UART_sendByte(match);
				uint8 number_of_step =UART_recieveByte();
				if(number_of_step==3){
					step_three();
					make_step_one=0;
					tick=0;
					DcMotor_Rotate(CLOCK_WISE,99);
					while(tick<229){
					}
					tick=0;
					DcMotor_Rotate(STOP,99);
					while(tick <46){
					}
					tick=0;
					DcMotor_Rotate(ANTI_ClOCK_WISE,99);
					while(tick<229){
					}
					Timer1_deInit();
					DcMotor_Rotate(STOP,100);
				}
			}
			else{
				match=0;
				UART_sendByte(match);
				UART_receiveString(pass);
				flag=strcmp(pass,pass_from_memory);
				if(flag==0){
					match=1;
					UART_sendByte(match);
					uint8 number_of_step =UART_recieveByte();
					if(number_of_step==3){
						step_three();
						make_step_one=0;
						tick=0;
						DcMotor_Rotate(CLOCK_WISE,99);
						while(tick<229){
						}
						tick=0;
						DcMotor_Rotate(STOP,100);
						while(tick <46){
						}
						tick=0;
						DcMotor_Rotate(ANTI_ClOCK_WISE,99);
						while(tick<229){
						}
						Timer1_deInit();
						DcMotor_Rotate(STOP,99);
					}
				}
				else{
					match=0;
					UART_sendByte(match);
					make_step_one=0;
					Buzzer_init();
					tick=0;
					Timer1_ConfigType  Config_Ptr_timer;
					Config_Ptr_timer.prescaler=clk_8;
					Config_Ptr_timer.compare_value=0;
					Config_Ptr_timer.initial_value=0;
					Config_Ptr_timer.mode=normal;
					Timer1_setCallBack(&buzzer_timer);
					Timer1_init(&Config_Ptr_timer);
					Buzzer_on();
					while(tick<915){
					}
					Buzzer_off();
					Timer1_deInit();
				}
			}
		}
	}
	return 0;
}
