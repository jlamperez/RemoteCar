/*
 * helloworld.c
 *
 *  Created on: 17/11/2015
 *      Author: Jorge
 */

#include <stdio.h>
#include "hw_abstraction.h"
#include "scheduler.h"
#include "display.h"
#include "remote_controller.h"
#include "car_controller.h"
#include "simple_buffer.h"
#include "../libs/static_circular_buffer.h"
#include "button_services.h"

int main(void) {
	DISPLAY_init();
	DISPLAY_printString("RemoteCar");
	//Inicializacion y puesta en marcha en milisegundos del timer
	HW_ABSTRACTION_initTimer(250);
	SCHEDULER_init();
	BUTTON_SERVICES_init();

	SCHEDULER_addTask(remoteControlerTask, 100, 0);
	SCHEDULER_addTask(carControlerTask, 30, 0);

	STATIC_CIRCULAR_BUFFER_init(&one_buffer);
	while (1) {
		SCHEDULER_schedule();
	}
	return 0;
}

