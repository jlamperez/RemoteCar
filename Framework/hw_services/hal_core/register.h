/*
 * car_register.h
 *
 *  Created on: 10/01/2016
 *      Author: jorge
 */

#ifndef CAR_REGISTER_H_
#define CAR_REGISTER_H_

//POSITION
#define REGISTER_POS_X 0x00
#define REGISTER_POS_Y 0x01
//SENSOR
#define REGISTER_FRONT_SENSOR 0x02
#define REGISTER_BACK_SENSOR 0x03
#define REGISTER_LEFT_SENSOR 0x04
#define REGISTER_RIGHT_SENSOR 0x05

#define REGISTER_COUNT 6

typedef unsigned int uint16;

extern uint16 registers[REGISTER_COUNT];

void REGISTER_init();
void REGISTER_default();


inline static uint16 registers_read(int address)
{
	return registers[address];
}


inline static void registers_write(int address, int value)
{
	registers[address]=value;
}


#endif /* CAR_REGISTER_H_ */
