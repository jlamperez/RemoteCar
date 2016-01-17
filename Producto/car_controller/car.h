/*
 * car.h
 *
 *  Created on: 16/12/2015
 *      Author: Jorge
 */

#ifndef CAR_H_
#define CAR_H_

#include "../car_lib/car_cmd.h"

typedef unsigned char BOOLEAN;

typedef struct{
	CAR_CMD car_cmd;
	unsigned char id;
	BOOLEAN front_sensor;
	BOOLEAN back_sensor;
	BOOLEAN right_sensor;
	BOOLEAN left_sensor;
}CAR;

void CAR_init(CAR *car, unsigned char id);
void CAR_update(CAR *car);
void CAR_removeCMD(CAR *car);
int CAR_isForward(CAR car);
int CAR_isBackward(CAR car);
int CAR_isLeft(CAR car);
int CAR_isRight(CAR car);
int CAR_isStop(CAR car);

#endif /* CAR_H_ */
