/*
 * remote_control.c
 *
 *  Created on: 17/11/2015
 *      Author: Jorge
 */

#include "remote_controller.h"
#include "display.h"
#include <stdio.h>
#include "simple_buffer.h"
#include "car_cmd.h"
#include "button_services.h"
#include <string.h>

#define SWITCH_SW0 0x01
#define SWITCH_SW1 0x02
#define SWITCH_SW2 0x04
#define SWITCH_SW3 0x08
#define NO_SWITCH 0x00

CAR_CMD REMOTE_CONTROLLER_parseCmd(unsigned char buttons);
void REMOTE_CONTROLLER_sendCmd(CAR_CMD cmd, STATIC_CIRCULAR_BUFFER *pBuffer);

void remoteControlerTask(void) {
	static int count = 0;
	char str[60]; //Cuidado! Si es de 30 se paraba la ejecución de esta tarea.
	unsigned char buttons;
	CAR_CMD cmd;

	count++;

	//leemos de los botones
	BUTTON_SERVICES_update();
	buttons = BUTTON_SERVICES_getStates();
	sprintf(str, "remoteControlerTask\t%d buttons=%d \r\n", count, buttons);
	DISPLAY_printString(str);

	//escribimos en el buffer el comando correspondiente
	cmd = REMOTE_CONTROLLER_parseCmd(buttons);
	REMOTE_CONTROLLER_sendCmd(cmd, &one_buffer);

}

/*
 *
 */
CAR_CMD REMOTE_CONTROLLER_parseCmd(unsigned char buttons){
	CAR_CMD ret = NOTHING;
	if (buttons == SWITCH_SW0) ret = FORWARD;
	if (buttons == SWITCH_SW1) ret = BACKWARD;
	if (buttons == SWITCH_SW2) ret = RIGHT;
	if (buttons == SWITCH_SW3) ret = LEFT;
	if (buttons == NO_SWITCH) ret = STOP; //Cuando haces el & con 0 siempre es 0 por lo que el if de STOP no saltará

	return ret;
}

void REMOTE_CONTROLLER_sendCmd(CAR_CMD cmd, STATIC_CIRCULAR_BUFFER *pBuffer){
	MSG msg;
	char str[30];
	if(cmd != NOTHING){
		sprintf(str , "CMD:%i", cmd);
		strcpy( msg.text , str);
		STATIC_CIRCULAR_BUFFER_insertMSG(pBuffer , msg);
	}

}
