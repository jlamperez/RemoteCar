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
}CAR;

void CAR_init(CAR *car, unsigned char id );
void CAR_update(CAR *car);
void CAR_removeCMD(CAR *car);

#endif /* CAR_H_ */
