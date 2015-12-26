/*
 * car_controller.c
 *
 *  Created on: 17/11/2015
 *      Author: Jorge
 */

#include "car_controller.h"
#include "display.h"
#include <stdio.h>
#include "simple_buffer.h"
#include <string.h>
#include "car_cmd.h"
#include "car.h"
#include "maquina_de_estados.h"
#include "config.h"
#include "car_logic.h"

CAR_CMD CAR_CONTROLLER_getCMDfromMSG(MSG msg);
void CAR_CONTROLLER_executeCMD(CAR_CMD cmd);
void CAR_CONTROLLER_updateCar();
void CAR_CONTROLLER_executeLogic();
void CAR_CONTROLLER_monitor();

CAR car;
extern TS_AUTOMATA car_logic;

void carControlerTask(void) {

	MSG msg;
	CAR_CMD cmd = NOTHING;

	CAR_init(&car, 1);

	//leemos del buffer

	msg = STATIC_CIRCULAR_BUFFER_readMSG(&one_buffer);
	cmd = CAR_CONTROLLER_getCMDfromMSG(msg);
	/***********************************************/
	CAR_CONTROLLER_executeCMD(cmd);
	CAR_CONTROLLER_updateCar();
	CAR_CONTROLLER_executeLogic();
	CAR_CONTROLLER_monitor();

}

CAR_CMD CAR_CONTROLLER_getCMDfromMSG(MSG msg) {
	CAR_CMD cmd = NOTHING;
	int aux;
	if (strstr(msg.text, "CMD") > 0) {
		sscanf(msg.text, "CMD:%d", &aux);
		cmd = (CAR_CMD) aux;
	}
	return cmd;
}

void CAR_CONTROLLER_executeCMD(CAR_CMD cmd) {
	car.car_cmd = cmd;
#ifdef DEBUG
	if (cmd == NOTHING)
		DISPLAY_printString("CAR CMD NOTHING\r\n");
	if (cmd == FORWARD)
		DISPLAY_printString("CAR CMD FORWARD\n");
	if (cmd == BACKWARD)
		DISPLAY_printString("CAR CMD BACKWARD\n");
	if (cmd == RIGHT)
		DISPLAY_printString("CAR CMD RIGHT\n");
	if (cmd == LEFT)
		DISPLAY_printString("CAR CMD LEFT\n");
	if (cmd == STOP)
		DISPLAY_printString("CAR CMD STOP\n");
#endif
}

void CAR_CONTROLLER_updateCar() {
	CAR_update(&car);
}

void CAR_CONTROLLER_executeLogic() {
	DISPLAY_printString("CAR EXECUTE LOGIC\n");
	EjecutaAutomata(&car_logic);
}
void CAR_CONTROLLER_monitor() {
	char str[60];
	switch (car_logic.id_estado_actual) {
	case STOPPED:
		strcpy(str, "CAR MONITOR ESTADO : STOPPED\n");
		break;
	case GOING_FORWARD:
		strcpy(str, "CAR MONITOR ESTADO : GOING FORWARD\n");
		break;
	case GOING_BACK:
		strcpy(str, "CAR MONITOR ESTADO : GOING BACK\n");
		break;
	case GOING_RIGHT:
		strcpy(str, "CAR MONITOR ESTADO : GOING RIGHT\n");
		break;
	case GOING_LEFT:
		strcpy(str, "CAR MONITOR ESTADO : GOING LEFT\n");
		break;
	}
	DISPLAY_printString(str);
}
