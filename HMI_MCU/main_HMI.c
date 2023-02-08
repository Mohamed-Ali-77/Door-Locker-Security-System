 /******************************************************************************
 *
 * Module: LCD
 *
 * File Name: main_HMI.c
 *
 * Description: main file for HMI
 *
 * Author: Mohamed Ali
 *
 *******************************************************************************/
#include "lcd.h"
#include "keypad.h"
#include "TimerOne.h"
#include "uart.h"
#include "std_types.h"
#include "util/delay.h"
#include <stdlib.h>
#include "avr/io.h"

uint32 password=0,re_password=0;
uint8 read_number_from_keypad=0;
void enter_pass(void){
	LCD_sendCommand(LCD_CLEAR_COMMAND);
	LCD_displayString("plz enter pass:");
	LCD_moveCursor(1,0);
	password=0;
	uint8 read_number_from_keypad=0;
	for(;read_number_from_keypad!=13;){
		read_number_from_keypad=KEYPAD_getPressedKey();
		if((read_number_from_keypad >= 0) && (read_number_from_keypad <= 9)){
			password*=10;
			password+=read_number_from_keypad;
			LCD_displayCharacter('*');
		}
	}
}
void re_enter_pass(void){
	LCD_sendCommand( LCD_CLEAR_COMMAND );
	LCD_displayString("plz re-enter the");
	LCD_moveCursor(1,0);
	LCD_displayString("same pass:");
	re_password=0;
	uint8 read_number_from_keypad=0;
	for(;read_number_from_keypad!=13;){
		read_number_from_keypad=KEYPAD_getPressedKey();
		if((read_number_from_keypad >= 0) && (read_number_from_keypad <= 9)){
			re_password*=10;
			re_password+=read_number_from_keypad;
			LCD_displayCharacter('*');
		}
	}
}
void take_pass_rePass_and_send_them(void){
	enter_pass();
	re_enter_pass();
	/*transfer*/
	char buff_password[6];
	itoa(password,buff_password,10);
	UART_sendString(buff_password);

	char buff_re_password[6];
	itoa(re_password,buff_re_password,10);
	UART_sendString(buff_re_password);
}

void lcd_pluse_timer_one(void){
	tick++;
}
void lcd_error(void){
	tick++;
}
void step_three(void){
	UART_sendByte(3);
	tick=0;
	Timer1_ConfigType  Config_Ptr_timer;
	Config_Ptr_timer.prescaler=clk_8;
	Config_Ptr_timer.compare_value=0;
	Config_Ptr_timer.initial_value=0;
	Config_Ptr_timer.mode=normal;
	Timer1_init(&Config_Ptr_timer);
	Timer1_setCallBack(&lcd_pluse_timer_one);
}
void step_four(void){
	UART_sendByte(4);
}
uint8 step_two(void){
	LCD_sendCommand(LCD_CLEAR_COMMAND);
	LCD_displayString("+ : Open Door");
	LCD_moveCursor(1,0);
	LCD_displayString("- : Change Pass");
	read_number_from_keypad=KEYPAD_getPressedKey();
	return read_number_from_keypad;
}
void step_one(void){
	uint8 step=1;
	while(step==1){
		take_pass_rePass_and_send_them();
		step=UART_recieveByte();
	}
}

int main(){
	/*enable global interrupt*/
	SREG|=(1<<7);
	/*led init*/
	LCD_init();
	/*UART INIT*/
	UART_ConfigType  Config_Ptr_UART;
	Config_Ptr_UART.baud_rate=9600;
	Config_Ptr_UART.bit_data=eight_bit;
	Config_Ptr_UART.stop_bit=one_bit;
	Config_Ptr_UART.parity=disable_parity;
	UART_init(&Config_Ptr_UART);
	uint8 step_number=0;
	uint8 make_step_one=1;
	uint8 display_flag=1;
	/*while one*/

	while(1){
		if(make_step_one==1){
			step_one();
		}
		make_step_one=1;
		/*take which operation is next*/
		step_number=step_two();
		enter_pass();
		char buff_password[6];
		itoa(password,buff_password,10);
		UART_sendString(buff_password);
		/*checking if matched or not*/
		uint8 match_or_unmatch= UART_recieveByte();
		if(match_or_unmatch==1){
			if(step_number==43){          //"+"
				make_step_one=0;
				step_three();
				LCD_sendCommand(LCD_CLEAR_COMMAND);
				LCD_displayString("Door's Unlocking");
				while(tick<274){
				}
				tick=0;
				LCD_sendCommand(LCD_CLEAR_COMMAND);
				LCD_displayString("Door is Locking");
				while(tick<228){
				}
				Timer1_deInit();
			}
			else if(step_number==45){
				step_four();
			}
		}
		/*second time*/
		else if(match_or_unmatch==0){
			/*another chance*/
			enter_pass();
			char buff_password[6];
			itoa(password,buff_password,10);
			UART_sendString(buff_password);
			/*another check*/
			match_or_unmatch= UART_recieveByte();
			if(match_or_unmatch==1){
				if(step_number==43){          //"+"
					make_step_one=0;
					step_three();
					LCD_sendCommand(LCD_CLEAR_COMMAND);
					LCD_displayString("Door's Unlocking");
					while(tick<274){
					}
					tick=0;
					LCD_sendCommand(LCD_CLEAR_COMMAND);
					LCD_displayString("Door is Locking");
					while(tick<228){
					}
					Timer1_deInit();
				}
				else if(step_number==45){
					step_four();
				}
			}
			/*third time*/
			else if(match_or_unmatch==0){
				enter_pass();
				char buff_password[6];
				itoa(password,buff_password,10);
				UART_sendString(buff_password);
				/*third check*/
				match_or_unmatch= UART_recieveByte();
				if(match_or_unmatch==1){
					if(step_number==43){          //"+"
						make_step_one=0;
						step_three();
						LCD_sendCommand(LCD_CLEAR_COMMAND);
						LCD_displayString("Door's Unlocking");
						while(tick<274){
						}
						tick=0;
						LCD_sendCommand(LCD_CLEAR_COMMAND);
						LCD_displayString("Door is Locking");
						while(tick<228){
						}
						Timer1_deInit();
					}
					else if(step_number==45){
						step_four();
					}
				}
				else if(match_or_unmatch==0){
					make_step_one=0;
					tick=0;
					Timer1_ConfigType  Config_Ptr_timer;
					Config_Ptr_timer.prescaler=clk_8;
					Config_Ptr_timer.compare_value=0;
					Config_Ptr_timer.initial_value=0;
					Config_Ptr_timer.mode=normal;
					Timer1_init(&Config_Ptr_timer);
					Timer1_setCallBack(&lcd_error);

					/*delay*/
					LCD_sendCommand(LCD_CLEAR_COMMAND);
					LCD_displayString("Error");
					while(tick<915){
					}
				}
			}
		}
	}
	return 0;
}

