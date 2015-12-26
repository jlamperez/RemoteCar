/*
 * button_services.c
 *
 *  Created on: 19/11/2015
 *      Author: Jorge
 */
#include "button_services.h"

#include "config.h"
#ifdef ZYNQ_7000
#include "platform.h"
#include "xil_printf.h"
#include "xscutimer.h"
#include "xscugic.h"
#include "xgpio.h"
#include "xparameters.h"
#endif

#ifdef ZYNQ_7000
XGpio axi_switch;
#endif

/************************** Constant Definitions *****************************/

#define SWITCH 0x0F   /* Para que la salida sea una entrada  */

/*
 * The following constant maps to the name of the hardware instances that
 * were created in the EDK XPS system.
 */
#define GPIO_SWITCH_DEVICE_ID  XPAR_SWS_4BITS_DEVICE_ID

/*
 * The following constant is used to determine which channel of the GPIO is
 * used for the SWITCH if there are 2 channels supported.
 */
#define SWITCH_CHANNEL 1

static BUTTONS buttons;

int BUTTON_SERVICES_init(void) {

	int Status;
	/*
	 * Initialize the GPIO driver
	 */
	Status = XGpio_Initialize(&axi_switch, GPIO_SWITCH_DEVICE_ID);
	if (Status != XST_SUCCESS) {
		return XST_FAILURE;
	}

	/*
	 * Set the direction for switch signals to be inputs(bits set to 1)
	 */
	XGpio_SetDataDirection(&axi_switch, SWITCH_CHANNEL, SWITCH);
	return 0;
}

void BUTTON_SERVICES_update(void) {
	unsigned int sw_check;
	sw_check = XGpio_DiscreteRead(&axi_switch, SWITCH_CHANNEL); //leemos el valor de los switch
	buttons = sw_check;
}

BUTTONS BUTTON_SERVICES_getStates() {
	return buttons;
}

BOOLEAN BUTTON_SERVICES_getState(unsigned char switch_number) {
	unsigned char value = 0x1;
	value = value << (switch_number-1); //desplazo el valor hacia donde el switch determinado tiene info
	value = buttons & value;			//me quedo con el valor del switch haciendo un and.
	value = value >> (switch_number -1);//desplazo la información hacia la derecha.
	return value;
}
