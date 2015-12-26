/*
 * TIMER_SERVICES.h
 *
 *  Created on: 04/09/2014
 *      Author: jaagirre
 */

#ifndef TIMER_SERVICES_H_
#define TIMER_SERVICES_H_

//#include "config.h"

/****************************************
 * Public macros
 ****************************************/

/************************************************
 *Public functions
 *************************************************/

void TIMER_SERVICES_initTimer(unsigned int msecs);
unsigned int TIMER_SERVICES_getTimerCount();
unsigned int TIMER_SERVICES_getStep();

#endif /* TIMER_SERVICES_H_ */
