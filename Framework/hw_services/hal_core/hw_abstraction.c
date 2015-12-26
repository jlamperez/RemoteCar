/*

 	 	 	 	 	 	 	 *******************************
*******************************    	  C SOURCE FILE       ********************************
** 	 	 	 	 	 	 	 *******************************                    		**
** 																						**
** 	project  : 	simpleWatch																**
** 	filename :	hw_abstraction.c														**
** 	version  :	1																		**
** 	date     :	29/10/2015																**
** 																						**
******************************************************************************************
** 																						**
** 	Copyright (c) 2015, Jorge Lampérez													**
** 	All rights reserved.																**
** 																						**
******************************************************************************************

VERSION HISTORY:
----------------

Version       : 1
Date          :	29/10/2015
Revised by    :	Jorge Lampérez
Description   :	Implementación de las funciones del módulo hw_abstraction.
				Gestionar el código dependiente de plataforma HW.


*/



/*************************************************************************************/
/** 																			 	**/
/** 						MODULES USED					 						**/
/** 														 						**/
/** 																			 	**/
/*************************************************************************************/
#include "config.h"
#ifdef ZYNQ_7000
#include "platform.h"
#include "xil_printf.h"
#include "xscutimer.h"
#include "xscugic.h"

#endif

#include "hw_abstraction.h"
#include "scheduler.h"

/*************************************************************************************/
/** 																			 	**/
/** 						DEFINITIONS AND MACROS					 				**/
/** 														 						**/
/** 																			 	**/
/*************************************************************************************/
#define INTC_DEVICE_ID		XPAR_SCUGIC_SINGLE_DEVICE_ID
#define TIMER_DEVICE_ID		XPAR_SCUTIMER_DEVICE_ID
#define INTC_BASE_ADDR		XPAR_SCUGIC_CPU_BASEADDR
#define INTC_DIST_BASE_ADDR	XPAR_SCUGIC_DIST_BASEADDR
#define TIMER_IRPT_INTR		XPAR_SCUTIMER_INTR


/*************************************************************************************/
/** 																			 	**/
/** 						TYPEDEFS AND STRUCTURES					 				**/
/** 														 						**/
/** 																			 	**/
/*************************************************************************************/

/*************************************************************************************/
/** 																			 	**/
/** 						PROTOTYPES OF LOCAL FUNCTIONS					 		**/
/** 														 						**/
/** 																			 	**/
/*************************************************************************************/
static void HW_ABSTRACTION_enable_interrupts();
static void HW_ABSTRACTION_setup_interrupts();
static void HW_ABSTRACTION_setup_timer(int msecs);
void HW_ABSTRACTION_timer_callback(XScuTimer * TimerInstance);


/*************************************************************************************/
/** 																			 	**/
/** 						EXPORTED VARIABLES					 					**/
/** 														 						**/
/** 																			 	**/
/*************************************************************************************/
/*************************************************************************************/
/** 																			 	**/
/** 						GLOBAL VARIABLES						 				**/
/** 														 						**/
/** 																			 	**/
/*************************************************************************************/
static unsigned int count=0;
static float step = 0;
static XScuTimer TimerInstance;//Que elemento es el que se mete en la interrupcion podría haber más de uno



/*************************************************************************************/
/** 																			 	**/
/** 						EXPORTED FUNCTIONS								 		**/
/** 														 						**/
/** 																			 	**/
/*************************************************************************************/

/*************************************************************************************/
/** 																			 	**/
/** 						LOCAL FUNCTIONS						 					**/
/** 														 						**/
/** 																			 	**/
/*************************************************************************************/


/*****************************************************************************/
/*
*
* Esta función inicializa el UART
*
* @return	None.
*
* @note		None.
*
******************************************************************************/
void HW_ABSTRACTION_initUART(){
	 init_platform();
}
/*****************************************************************************/
/*
*
* Esta función inicializa el Timer
*
* @return	None.
*
* @note		None.
*
******************************************************************************/
void HW_ABSTRACTION_initTimer(unsigned int msecs) {
	// 3 pasos: inicializar timer, inicializar interrupciones, activar interrupciones
	HW_ABSTRACTION_setup_timer(msecs);
	HW_ABSTRACTION_setup_interrupts();
	HW_ABSTRACTION_enable_interrupts();
}

/*****************************************************************************/
/*
*
* Esta función obtiene el contador del Timer
*
* @return	count Timer.
*
* @note		None.
*
******************************************************************************/
unsigned int HW_ABSTRACTION_getTimerCount(){
	return count;
}
/*****************************************************************************/
/*
*
* Esta función obtiene el step que es el valor 1000/msecs inicializados por el Timer.
*
* @return	step.
*
* @note		None.
*
******************************************************************************/
unsigned int HW_ABSTRACTION_getStep(){
	return step;
}
/*****************************************************************************/
/*
*
* Esta funcion activa las interrupciones
*
* @return	None.
*
* @note		None.
*
******************************************************************************/
static void HW_ABSTRACTION_enable_interrupts(){
	/* Enable non-critical exceptions.*/
	Xil_ExceptionEnableMask(XIL_EXCEPTION_IRQ);
	XScuTimer_EnableInterrupt(&TimerInstance);
	XScuTimer_Start(&TimerInstance);

}
/*****************************************************************************/
/*
*
* Esta función inicializa las interrupciones
*
* @return	count Timer.
*
* @note		None.
*
******************************************************************************/
static void HW_ABSTRACTION_setup_interrupts(){
#ifdef  ZYNQ_7000
	Xil_ExceptionInit();

	XScuGic_DeviceInitialize(INTC_DEVICE_ID);

	/*Connect the interrupt controller interrupt handler to the hardware interrupt handling logic in the processor*/
	Xil_ExceptionRegisterHandler(XIL_EXCEPTION_ID_IRQ_INT,
			(Xil_ExceptionHandler)XScuGic_DeviceInterruptHandler,
			(void *)INTC_DEVICE_ID);
	/* Connect the device driver handler that will be called when an interrupt for the device occurs, the handler defined above performs the specific interrupt processing for the device.*/
	XScuGic_RegisterHandler(INTC_BASE_ADDR, TIMER_IRPT_INTR,
			(Xil_ExceptionHandler)HW_ABSTRACTION_timer_callback,
			(void *)&TimerInstance);
	/*Enable the interrupt for scu timer.*/
	XScuGic_EnableIntr(INTC_DIST_BASE_ADDR, TIMER_IRPT_INTR);
#endif
	return;


}
/*****************************************************************************/
/*
*
* Esta función inicializa el timer en msecs
*
* @return	None.
*
* @note		None.
*
******************************************************************************/
static void HW_ABSTRACTION_setup_timer(int msecs) {

	int Status = XST_SUCCESS;

	XScuTimer_Config *ConfigPtr;

	int TimerLoadValue = 0;

	step = 1000/msecs;

	ConfigPtr = XScuTimer_LookupConfig(TIMER_DEVICE_ID);
	Status = XScuTimer_CfgInitialize(&TimerInstance, ConfigPtr,ConfigPtr->BaseAddr);

	if (Status != XST_SUCCESS) {
		xil_printf("In %s: Scutimer Cfg initialization failed...\r\n", __func__);
	return;
	}

	Status = XScuTimer_SelfTest(&TimerInstance);
	if (Status != XST_SUCCESS) {
		xil_printf("In %s: Scutimer Self test failed...\r\n", __func__);
	return;
	}

	XScuTimer_EnableAutoReload(&TimerInstance);

	/*El dos es debido  que el clock del timer va a la mitad del de la cpu*/
	TimerLoadValue = XPAR_CPU_CORTEXA9_0_CPU_CLK_FREQ_HZ / (step*2);

	XScuTimer_LoadTimer(&TimerInstance, TimerLoadValue);

	return;

}

/*****************************************************************************/
/*
*
* Es la función Callback del timer, actua cuando se da una interrupción del timer.
*
* @return	count Timer.
*
* @note		None.
*
******************************************************************************/
void HW_ABSTRACTION_timer_callback(XScuTimer * TimerInstance) {
	count++;
	SCHEDULER_update();
	//desactivar interrupcion
	XScuTimer_ClearInterruptStatus(TimerInstance);

}



/*************************************************************************************/
/** 																			 	**/
/** 						EOF					 								 	**/
/** 														 						**/
/** 																			 	**/
/*************************************************************************************/
