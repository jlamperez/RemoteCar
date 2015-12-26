/*

 	 	 	 	 	 	 	 *******************************
*******************************    	  C SOURCE FILE       ********************************
** 	 	 	 	 	 	 	 *******************************                    		**
** 																						**
** 	project  : 	simpleWatch																**
** 	filename :	display.c																**
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
Date          : 29/10/2015
Revised by    : Jorge Lampérez
Description   : Implementación de las funciones del módulo Display.

*/


/*************************************************************************************/
/** 																			 	**/
/** 						MODULES USED					 						**/
/** 														 						**/
/** 																			 	**/
/*************************************************************************************/
#include <stdio.h>
#include "hw_abstraction.h"
#include "config.h"

#if defined(ZYNQ_7000) && defined(UART_DISPLAY)
#include "xil_printf.h"
#include "xuartps.h"
#include "xparameters.h"
#define UART_BASEADDR XPAR_PS7_UART_1_BASEADDR

#include "display.h"


/*************************************************************************************/
/** 																			 	**/
/** 						DEFINITIONS AND MACROS					 				**/
/** 														 						**/
/** 																			 	**/
/*************************************************************************************/

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
* Esta función inicializa tanto el UART como los GPIO.
*
* @return	None.
*
* @note		None.
*
******************************************************************************/
void DISPLAY_init(){

	#if defined(ZYNQ_7000) && defined(UART_DISPLAY)
		HW_ABSTRACTION_initUART();

	#endif

}
/*****************************************************************************/
/*
*
* Esta función sirve para imprimir por pantalla una cadena de caracteres.
*
* @param	str es una array de caracteres.
*
* @return	None.
*
* @note		None.
*
******************************************************************************/
void DISPLAY_printString(char str[]){

		#if defined(ZYNQ_7000) && defined(UART_DISPLAY)
			xil_printf("\x1B[H"); //Set cursor to top left of terminal
			xil_printf("\x1B[2J"); //Clear terminal
			xil_printf(str);
		#endif

}

/*****************************************************************************/
/*
*
* Esta función lee desde el UART carácter a carácter lo escrito hasta que el
* usuario pulse return. Según se lee un carácter
*este se escribe en la UART para que el carácter aparezca en la consola (echo).
*Este se utiliza para ir creando el string con el numero tecleado por el usuario.
*Finalmente utilizando sscanf se convierte el string en numero entero
*
*
* @return	ret.
*
* @note		None.
*
******************************************************************************/
int DISPLAY_readInteger(){
	char userInput[30];
	char kar;
	int i =0;
	int ret = 0;
#if defined(ZYNQ_7000) && defined(UART_DISPLAY)
	/* Wait for data on UART */
	while(kar !='\r'){
		while(!XUartPs_IsReceiveData(UART_BASEADDR))
		{}
		/*Store the first character in the UART receive FIFO and echo it*/
		kar = XUartPs_ReadReg(UART_BASEADDR, XUARTPS_FIFO_OFFSET);
		xil_printf("%c", kar);
		userInput[i]=kar;
		i++;
	}
	userInput[i]='\0';

#endif
	sscanf(userInput , "%i", &ret);
	return ret;

}

/*************************************************************************************/
/** 																			 	**/
/** 						EOF					 								 	**/
/** 														 						**/
/** 																			 	**/
/*************************************************************************************/

#endif
