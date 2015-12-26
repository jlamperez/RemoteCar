/*
 * TIMER_SERVICES.c
 *
 *  Created on: 04/10/2014
 *      Author: jaagirre
 */
#include "config.h"
#ifdef ZYNQ_7000

#include "xil_printf.h"
#include "xscutimer.h"
#include "xscugic.h"
#endif

//#include "scheduler.h"
#include "timer_services.h"
/**********************************************
 * module private definitions
 ***********************************************/
#define INTC_DEVICE_ID		XPAR_SCUGIC_SINGLE_DEVICE_ID
#define TIMER_DEVICE_ID		XPAR_SCUTIMER_DEVICE_ID
#define INTC_BASE_ADDR		XPAR_SCUGIC_CPU_BASEADDR
#define INTC_DIST_BASE_ADDR	XPAR_SCUGIC_DIST_BASEADDR
#define TIMER_IRPT_INTR		XPAR_SCUTIMER_INTR
/***************************************
 * module private variables
 ************************************/
static unsigned int count=0;
static float step = 0;
static XScuTimer TimerInstance;

/**********************************************************
 * MODULE pRIVATE FUNCTIONS
 *********************************************************/
static void TIMER_SERVICES_enable_interrupts();
static void TIMER_SERVICES_setup_interrupts();
static void TIMER_SERVICES_setup_timer(int msecs);
void TIMER_SERVICES_timer_callback(XScuTimer * TimerInstance);



void TIMER_SERVICES_initTimer(unsigned int msecs){
	TIMER_SERVICES_setup_timer(msecs);
	TIMER_SERVICES_setup_interrupts();
	TIMER_SERVICES_enable_interrupts();

}
unsigned int TIMER_SERVICES_getStep(){
	return step;
}
unsigned int TIMER_SERVICES_getTimerCount(){
	return count;
}
static void TIMER_SERVICES_enable_interrupts(){
	/* Enable non-critical exceptions.*/
	Xil_ExceptionEnableMask(XIL_EXCEPTION_IRQ);
	XScuTimer_EnableInterrupt(&TimerInstance);
	XScuTimer_Start(&TimerInstance);
	return;
}

static void TIMER_SERVICES_setup_interrupts(){
#ifdef ZYNQ_7000
	Xil_ExceptionInit();

	XScuGic_DeviceInitialize(INTC_DEVICE_ID);

	/*Connect the interrupt controller interrupt handler to the hardware interrupt handling logic in the processor*/
	Xil_ExceptionRegisterHandler(XIL_EXCEPTION_ID_IRQ_INT,
			(Xil_ExceptionHandler)XScuGic_DeviceInterruptHandler,
			(void *)INTC_DEVICE_ID);
	/*Connect the device driver handler that will be called when an interrupt for the device occurs, the handler defined above performs
	the specific interrupt processing for the device.*/
	XScuGic_RegisterHandler(INTC_BASE_ADDR, TIMER_IRPT_INTR,
			(Xil_ExceptionHandler)TIMER_SERVICES_timer_callback,
			(void *)&TimerInstance);
	/*Enable the interrupt for scu timer.*/
	XScuGic_EnableIntr(INTC_DIST_BASE_ADDR, TIMER_IRPT_INTR);
#endif
	return;
}
static void TIMER_SERVICES_setup_timer(int msecs){
	int Status = XST_SUCCESS;
	XScuTimer_Config *ConfigPtr;
	int TimerLoadValue = 0;
	step = 1000/msecs;

	ConfigPtr = XScuTimer_LookupConfig(TIMER_DEVICE_ID);
	Status = XScuTimer_CfgInitialize(&TimerInstance, ConfigPtr,
			ConfigPtr->BaseAddr);
	if (Status != XST_SUCCESS) {
		xil_printf("In %s: Scutimer Cfg initialization failed...\r\n",
		__func__);
		return;
	}

	Status = XScuTimer_SelfTest(&TimerInstance);
	if (Status != XST_SUCCESS) {
		xil_printf("In %s: Scutimer Self test failed...\r\n",
		__func__);
		return;
	}

	XScuTimer_EnableAutoReload(&TimerInstance);
	/*El dos es debido  que el clock del timer va a la mitad del de la cpu*/
	TimerLoadValue = XPAR_CPU_CORTEXA9_0_CPU_CLK_FREQ_HZ / (step*2);
	XScuTimer_LoadTimer(&TimerInstance, TimerLoadValue);
	return;
}



void TIMER_SERVICES_timer_callback(XScuTimer * TimerInstance){
	count++;
	//SCHEDULER_update();
	XScuTimer_ClearInterruptStatus(TimerInstance);
}
