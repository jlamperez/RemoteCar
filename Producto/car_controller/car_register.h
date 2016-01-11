/*
 * car_register.h
 *
 *  Created on: 10/01/2016
 *      Author: jorge
 */

#ifndef CAR_REGISTER_H_
#define CAR_REGISTER_H_

#define REGISTER_POS_X 0x00
#define REGISTER_POS_Y 0x01
#define REGISTERS_COUNT 2

extern int registers[REGISTERS_COUNT];

void registers_init();
void registers_default();

inline static int registers_read(int address)
{
	return registers[address];
}

inline static void registers_write(int address, int value)
{
	registers[address]=value;
}


#endif /* CAR_REGISTER_H_ */
