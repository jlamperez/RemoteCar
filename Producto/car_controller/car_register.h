/*
 * car_register.h
 *
 *  Created on: 10/01/2016
 *      Author: jorge
 */

#ifndef CAR_REGISTER_H_
#define CAR_REGISTER_H_

#define CAR_REGISTER_POS_X 0x00
#define CAR_REGISTER_POS_Y 0x01
#define CAR_REGISTER_COUNT 2

typedef unsigned int uint16;

extern uint16 registers[CAR_REGISTER_COUNT];

void CAR_REGISTERS_init();
void CAR_REGISTERS_default();


inline static uint16 CAR_registers_read(int address)
{
	return registers[address];
}


inline static void CAR_registers_write(int address, int value)
{
	registers[address]=value;
}


#endif /* CAR_REGISTER_H_ */
