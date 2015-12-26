/*
 * button_services.h
 *
 *  Created on: 19/11/2015
 *      Author: Jorge
 */

#ifndef BUTTON_SERVICES_H_
#define BUTTON_SERVICES_H_

typedef unsigned char BOOLEAN;
typedef unsigned char BUTTONS;

int BUTTON_SERVICES_init(void);
void BUTTON_SERVICES_update(void);
BUTTONS BUTTON_SERVICES_getStates();
BOOLEAN BUTTON_SERVICES_getState(unsigned char switch_number);

#endif /* BUTTON_SERVICES_H_ */
