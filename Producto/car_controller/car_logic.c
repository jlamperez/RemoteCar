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
#include "motor.h"


ESTADO(stopped)
/*----------------------------------------------------------------------*/
ITEM_EAC( GOING_FORWARD, E_goForward , A_goingForward),
ITEM_EAC( GOING_BACK , E_goBack , A_goingBack),
ITEM_EAC( GOING_LEFT , E_goLeft, A_goingLeft),
ITEM_EAC( GOING_RIGHT , E_goRight , A_goingRight)
FIN_ESTADO(stopped, STOPPED ,A_Do_stopped )
/*----------------------------------------------------------------------*/
ESTADO(going_forward)
/*----------------------------------------------------------------------*/
ITEM_EAC( STOPPED, E_carStop , A_stopped),
ITEM_EAC( GOING_BACK , E_goBack , A_goingBack),
ITEM_EAC( GOING_LEFT , E_goLeft, A_goingLeft),
ITEM_EAC( GOING_RIGHT , E_goRight , A_goingRight)
FIN_ESTADO(going_forward, GOING_FORWARD , A_Do_goingForward)
/*----------------------------------------------------------------------*/
ESTADO(going_back)
/*----------------------------------------------------------------------*/
ITEM_EAC( GOING_FORWARD, E_goForward , A_goingForward),
ITEM_EAC( STOPPED , E_carStop , A_stopped),
ITEM_EAC( GOING_LEFT , E_goLeft, A_goingLeft),
ITEM_EAC( GOING_RIGHT , E_goRight , A_goingRight)
FIN_ESTADO(going_back, GOING_BACK , A_Do_goingBack)
/*----------------------------------------------------------------------*/
ESTADO(going_right)
/*----------------------------------------------------------------------*/
ITEM_EAC( GOING_FORWARD, E_goForward , A_goingForward),
ITEM_EAC( GOING_BACK , E_goBack , A_goingBack),
ITEM_EAC( GOING_LEFT , E_goLeft, A_goingLeft),
ITEM_EAC( STOPPED , E_carStop , A_stopped)
FIN_ESTADO(going_right, GOING_RIGHT , A_Do_goingRight)
/*----------------------------------------------------------------------*/
ESTADO(going_left)
/*----------------------------------------------------------------------*/
ITEM_EAC( GOING_FORWARD, E_goForward , A_goingForward),
ITEM_EAC( GOING_BACK , E_goBack , A_goingBack),
ITEM_EAC( STOPPED , E_carStop, A_stopped),
ITEM_EAC( GOING_RIGHT , E_goRight , A_goingRight)
FIN_ESTADO(going_left, GOING_LEFT , A_Do_goingLeft)
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
	sprintf(str, "CAR LOGIC TRASNSITION ACTION: GOING_FORWARD \r\n");
	MOTOR_forward();

//	DISPLAY_printString(str);

}
void A_stopped(void) {
	char str[60];
	sprintf(str, "CAR LOGIC TRANSITION ACTION: STOPPED \r\n");
	MOTOR_stop();
//	DISPLAY_printString(str);
}
void A_goingBack(void) {
	char str[60];
	sprintf(str, "CAR LOGIC TRANSITION ACTION: GOING_BACK \r\n");
	MOTOR_back();

//	DISPLAY_printString(str);
}
void A_goingRight(void) {
	char str[60];
	sprintf(str, "CAR LOGIC TRANSITION ACTION GOING_RIGHT \r\n");
	MOTOR_right();

//	DISPLAY_printString(str);
}
void A_goingLeft(void) {
	char str[60];
	sprintf(str, "CAR LOGIC TRANSITION ACTION: GOING_LEFT \r\n");
	MOTOR_left();
//	DISPLAY_printString(str);
}

void A_Do_goingForward(void){
	char str[60];
	sprintf(str, "CAR LOGIC DO ACTION: GOING_FORWARD \r\n");
	MOTOR_forward();
//	DISPLAY_printString(str);
}
void A_Do_stopped(void){
	char str[60];
	sprintf(str, "CAR LOGIC DO ACTION: STOPPED \r\n");
	MOTOR_stop();
//	DISPLAY_printString(str);
}
void A_Do_goingBack(void){
	char str[60];
	sprintf(str, "CAR LOGIC DO ACTION: GOING_BACK \r\n");
	MOTOR_back();

//	DISPLAY_printString(str);
}
void A_Do_goingRight(void){
	char str[60];
	sprintf(str, "CAR LOGIC DO ACTION: GOING_RIGHT \r\n");
	MOTOR_right();

//	DISPLAY_printString(str);
}
void A_Do_goingLeft(void){
	char str[60];
	sprintf(str, "CAR LOGIC DO ACTION: GOING_LEFT \r\n");
	MOTOR_left();
//	DISPLAY_printString(str);
}

/*****************************************************************/
/************************* EVENTOS ******************************/
/*****************************************************************/
BOOLEAN E_goForward(void) {
	BOOLEAN ret = FALSE;
	if (CAR_isForward(car)) {
		ret = TRUE;
	}
	return ret;
}

BOOLEAN E_goBack(void) {
	BOOLEAN ret = FALSE;
	if (CAR_isBackward(car)) {
		ret = TRUE;
	}
	return ret;
}

BOOLEAN E_goLeft(void) {
	BOOLEAN ret = FALSE;
	if (CAR_isLeft(car)) {
		ret = TRUE;
	}
	return ret;
}

BOOLEAN E_goRight(void) {
	BOOLEAN ret = FALSE;
	if (CAR_isRight(car)) {
		ret = TRUE;
	}
	return ret;
}

BOOLEAN E_carStop(void) {
	BOOLEAN ret = FALSE;
	if (CAR_isStop(car)) {
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
