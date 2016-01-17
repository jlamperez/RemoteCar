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
#include "register.h"

void displayTask();

int main(void) {
	DISPLAY_init();
	DISPLAY_printString("RemoteCar");
	//Inicializacion y puesta en marcha en milisegundos del timer
	HW_ABSTRACTION_initTimer(10);
	SCHEDULER_init();
	BUTTON_SERVICES_init();
	REGISTER_init();

	SCHEDULER_addTask(remoteControlerTask, 40, 0);
	SCHEDULER_addTask(carControlerTask, 20, 0);
	SCHEDULER_addTask(displayTask,20,0);

	STATIC_CIRCULAR_BUFFER_init(&one_buffer);
	while (1) {
		SCHEDULER_schedule();
	}
	return 0;
}

void displayTask(void) {
	DISPLAY_printString("");
}

