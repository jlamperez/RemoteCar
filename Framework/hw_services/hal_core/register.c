/*
 * car_register.c
 *
 *  Created on: 10/01/2016
 *      Author: jorge
 */
#include "register.h"


#include <string.h>

uint16 registers[REGISTER_COUNT];

void REGISTER_init() {
	// Initialize all registers to zero.
	memset(&registers[0], 0, REGISTER_COUNT);
}
void REGISTER_default() {
	REGISTER_init();
}
