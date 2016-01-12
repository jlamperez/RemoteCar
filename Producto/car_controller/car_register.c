/*
 * car_register.c
 *
 *  Created on: 10/01/2016
 *      Author: jorge
 */
#include "car_register.h"
#include "car_logic.h"

#include <string.h>

uint16 registers[CAR_REGISTER_COUNT];

void CAR_REGISTERS_init() {
	// Initialize all registers to zero.
	memset(&registers[0], 0, CAR_REGISTER_COUNT);
}
void CAR_REGISTERS_default() {
	CAR_REGISTERS_init();
}
