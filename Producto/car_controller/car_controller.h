/*
 * car_controller.h
 *
 *  Created on: 17/11/2015
 *      Author: Jorge
 */

#ifndef CAR_CONTROLLER_H_
#define CAR_CONTROLLER_H_
#include "car.h"

#ifdef DOOR_CONTROLLER_C_
#define PUBLIC
#else
#define PUBLIC extern
#endif

PUBLIC CAR car;
void carControlerTask(void);

#endif /* CAR_CONTROLLER_H_ */
