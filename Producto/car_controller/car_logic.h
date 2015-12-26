/*
 * car_logic.h
 *
 *  Created on: 15/12/2015
 *      Author: Jorge
 */

#ifndef CAR_LOGIC_H_
#define CAR_LOGIC_H_

#include "car.h"

/*************************estados*******************************/

typedef enum {STOPPED, GOING_FORWARD, GOING_BACK, GOING_RIGHT, GOING_LEFT}estados;
/*************************acciones******************************/

void accion_nula(void);
void A_goingForward(void);
void A_stopped(void);
void A_goingBack(void);
void A_goingRight(void);
void A_goingLeft(void);

/*************************eventos*******************************/
BOOLEAN E_goForward(void);
BOOLEAN E_goBack(void);
BOOLEAN E_goLeft(void);
BOOLEAN E_goRight(void);
BOOLEAN  E_carStop(void);
BOOLEAN E_nulo(void);

#endif /* CAR_LOGIC_H_ */
