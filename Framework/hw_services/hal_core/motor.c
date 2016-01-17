/*
 * motor.c
 *
 *  Created on: 17/01/2016
 *      Author: Jorge
 */
#include "register.h"
#include "config.h"


void MOTOR_forward(){
	uint16 value;
	value = registers_read(REGISTER_POS_Y);

#ifdef VGA_DISPLAY
	value= value -5;
#endif
	registers_write(REGISTER_POS_Y, value);
}

void MOTOR_back(){
	uint16 value;
	value = registers_read(REGISTER_POS_Y);
#ifdef VGA_DISPLAY
	value = value +5;
#endif
	registers_write(REGISTER_POS_Y, value);
}

void MOTOR_right(){
	uint16 value;
	value = registers_read(REGISTER_POS_X);
#ifdef VGA_DISPLAY
	value = value +5;
#endif
	registers_write(REGISTER_POS_X, value);
}

void MOTOR_left(){
	uint16 value;
	value = registers_read(REGISTER_POS_X);
#ifdef VGA_DISPLAY
	value = value -5;
#endif
	registers_write(REGISTER_POS_X, value);
}

void MOTOR_stop(){

}
