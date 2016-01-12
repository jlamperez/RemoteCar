/*
 * car.c
 *
 *  Created on: 16/12/2015
 *      Author: Jorge
 */

#include "car.h"

void CAR_init(CAR *car, unsigned char id) {
	car->car_cmd = NOTHING;
	car->id = id;
}
void CAR_update(CAR *car) {

}
void CAR_removeCMD(CAR *car) {
	car->car_cmd = NOTHING;
}

int CAR_isForward(CAR car) {
	int ret = 0;

	if (car.car_cmd == FORWARD) {
		ret = 1;
	}
	return ret;
}

int CAR_isBackward(CAR car) {
	int ret = 0;

	if (car.car_cmd == BACKWARD) {
		ret = 1;
	}
	return ret;
}

int CAR_isLeft(CAR car) {
	int ret = 0;

	if (car.car_cmd == LEFT) {
		ret = 1;
	}
	return ret;
}

int CAR_isRight(CAR car) {
	int ret = 0;

	if (car.car_cmd == RIGHT) {
		ret = 1;
	}
	return ret;
}

int CAR_isStop(CAR car) {
	int ret = 0;

	if (car.car_cmd == STOP) {
		ret = 1;
	}
	return ret;
}
