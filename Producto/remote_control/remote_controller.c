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
 * Mirar este metodo mas detenidamente porque si tengo los tres primeros switches encendidos
 * el primer if lo pasara cambiando a FORWARD pero el segundo tmb y el tercero tmb
 * retornando RIGHT -> CMD:3 habría que hacer que si hay 2 o más switches en on que retorna
 * NOTHING.
 */
CAR_CMD REMOTE_CONTROLLER_parseCmd(unsigned char buttons){
	CAR_CMD ret = NOTHING;
	if (buttons == 0x01) ret = FORWARD;
	if (buttons == 0x02) ret = BACKWARD;
	if (buttons == 0x04) ret = RIGHT;
	if (buttons == 0x08) ret = LEFT;
	if (buttons == 0x0) ret = STOP; //Cuando haces el & con 0 siempre es 0 por lo que el if de STOP no saltará

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
