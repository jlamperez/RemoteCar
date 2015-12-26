/*
 * car.c
 *
 *  Created on: 16/12/2015
 *      Author: Jorge
 */

#include "car.h"

void CAR_init(CAR *car, unsigned char id ){
	car ->car_cmd = NOTHING;
	car ->id = id;
}
void CAR_update(CAR *car){

}
void CAR_removeCMD(CAR *car){
	car ->car_cmd =NOTHING;
}
