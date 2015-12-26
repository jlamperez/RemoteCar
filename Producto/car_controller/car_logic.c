/*
 * car_logic.c
 *
 *  Created on: 15/12/2015
 *      Author: Jorge
 */
#ifndef CAR_LOGIC_C_
#define CAR_LOGIC_C_
#include "car_controller.h"
#include "car_logic.h"
#include "maquina_de_estados.h"
#include "car.h"
#include "display.h"


ESTADO(stopped)
/*----------------------------------------------------------------------*/
ITEM_EAC( GOING_FORWARD, E_goForward , accion_nula),
ITEM_EAC( GOING_BACK , E_goBack , accion_nula),
ITEM_EAC( GOING_LEFT , E_goLeft, accion_nula),
ITEM_EAC( GOING_RIGHT , E_goRight , accion_nula)
FIN_ESTADO(stopped, STOPPED , A_stopped)
/*----------------------------------------------------------------------*/
ESTADO(going_forward)
/*----------------------------------------------------------------------*/
ITEM_EAC( STOPPED, E_carStop , accion_nula),
ITEM_EAC( GOING_BACK , E_goBack , accion_nula),
ITEM_EAC( GOING_LEFT , E_goLeft, accion_nula),
ITEM_EAC( GOING_RIGHT , E_goRight , accion_nula)
FIN_ESTADO(going_forward, GOING_FORWARD , A_goingForward)
/*----------------------------------------------------------------------*/
ESTADO(going_back)
/*----------------------------------------------------------------------*/
ITEM_EAC( GOING_FORWARD, E_goForward , accion_nula),
ITEM_EAC( STOPPED , E_carStop , accion_nula),
ITEM_EAC( GOING_LEFT , E_goLeft, accion_nula),
ITEM_EAC( GOING_RIGHT , E_goRight , accion_nula)
FIN_ESTADO(going_back, GOING_BACK , A_goingBack)
/*----------------------------------------------------------------------*/
ESTADO(going_right)
/*----------------------------------------------------------------------*/
ITEM_EAC( GOING_FORWARD, E_goForward , accion_nula),
ITEM_EAC( GOING_BACK , E_goBack , accion_nula),
ITEM_EAC( GOING_LEFT , E_goLeft, accion_nula),
ITEM_EAC( STOPPED , E_carStop , accion_nula)
FIN_ESTADO(going_right, GOING_RIGHT , A_goingRight)
/*----------------------------------------------------------------------*/
ESTADO(going_left)
/*----------------------------------------------------------------------*/
ITEM_EAC( GOING_FORWARD, E_goForward , accion_nula),
ITEM_EAC( GOING_BACK , E_goBack , accion_nula),
ITEM_EAC( STOPPED , E_carStop, accion_nula),
ITEM_EAC( GOING_RIGHT , E_goRight , accion_nula)
FIN_ESTADO(going_left, GOING_LEFT , A_goingLeft)
/*----------------------------------------------------------------------*/
AUTOMATA(car_logic)
/*======================================================================*/
& stopped,
& going_forward,
& going_back,
& going_right,
& going_left
FIN_AUTOMATA(car_logic,1,E_nulo)

/*****************************************************************/
/************************* ACCIONES ******************************/
/*****************************************************************/

void accion_nula(void) {

}
void A_goingForward(void) {
	char str[60];
	sprintf(str, "CAR LOGIC ACTION: GOING_FORWARD \r\n");
	DISPLAY_printString(str);
}
void A_stopped(void) {
	char str[60];
	sprintf(str, "CAR LOGIC ACTION: STOPPED \r\n");
	DISPLAY_printString(str);
}
void A_goingBack(void) {
	char str[60];
	sprintf(str, "CAR LOGIC ACTION: GOING_BACK \r\n");
	DISPLAY_printString(str);
}
void A_goingRight(void) {
	char str[60];
	sprintf(str, "CAR LOGIC ACTION GOING_RIGHT \r\n");
	DISPLAY_printString(str);
}
void A_goingLeft(void) {
	char str[60];
	sprintf(str, "CAR LOGIC ACTION: GOING_LEFT \r\n");
	DISPLAY_printString(str);
}

/*****************************************************************/
/************************* EVENTOS ******************************/
/*****************************************************************/
BOOLEAN E_goForward(void) {
	BOOLEAN ret = FALSE;
	if (car.car_cmd == FORWARD) {
		ret = TRUE;
	}
	return ret;
}

BOOLEAN E_goBack(void) {
	BOOLEAN ret = FALSE;
	if (car.car_cmd == BACKWARD) {
		ret = TRUE;
	}
	return ret;
}

BOOLEAN E_goLeft(void) {
	BOOLEAN ret = FALSE;
	if (car.car_cmd == LEFT) {
		ret = TRUE;
	}
	return ret;
}

BOOLEAN E_goRight(void) {
	BOOLEAN ret = FALSE;
	if (car.car_cmd == RIGHT) {
		ret = TRUE;
	}
	return ret;
}

BOOLEAN E_carStop(void) {
	BOOLEAN ret = FALSE;
	if (car.car_cmd == STOP) {
		ret = TRUE;
	}
	return ret;
}

BOOLEAN E_nulo(void) {
	BOOLEAN ret = FALSE;
	if (car.car_cmd == NOTHING) {
		ret = TRUE;
	}
	return ret;
}

#endif /* CAR_LOGIC_C_ */