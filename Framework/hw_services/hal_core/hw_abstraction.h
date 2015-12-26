 /*

 	 	 	 	 	 	 	 *******************************
*******************************    	  C HEADER FILE       ********************************
** 	 	 	 	 	 	 	 *******************************                    		**
** 																						**
** 	project  : 	simpleWatch																**
** 	filename :	hw_abstraction															**
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
Revised by    : Jorge Lampérez
Description   : Implementación pública de las funciones del módulo hw_abstraction.
				Gestionar el código dependiente de plataforma HW.

*/


#ifndef HW_ABSTRACTION_H_
#define HW_ABSTRACTION_H_

/*************************************************************************************/
/** 																			 	**/
/** 						MODULES USED					 						**/
/** 														 						**/
/** 																			 	**/
/*************************************************************************************/
#include "config.h"

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
/** 						EXPORTED VARIABLES					 					**/
/** 														 						**/
/** 																			 	**/
/*************************************************************************************/

/*************************************************************************************/
/** 																			 	**/
/** 						EXPORTED FUNCTIONS					 					**/
/**																					**/
/*************************************************************************************/

/*
 * Función de inicialización del UART
 */
void HW_ABSTRACTION_initUART();
/*
 * Función de inicialización del Timer
 */
void HW_ABSTRACTION_initTimer(unsigned int msecs);
/*
 * Función para obtener el contador del Timer
 */
unsigned int HW_ABSTRACTION_getTimerCount();
/*
 * Función para obtener el Step del Timer
 */
unsigned int HW_ABSTRACTION_getStep();
/*
 * Función de inicialización del GPIO
 */
void HW_ABSTRACTION_initGPIO();
/*
 * Función de lectura del Btn Gpio
 */
int HW_ABSTRACTION_readGpioBtnPin();

#endif /* HW_ABSTRACTION_H_ */

/*************************************************************************************/
/** 																			 	**/
/** 						EOF					 								 	**/
/** 														 						**/
/** 																			 	**/
/*************************************************************************************/
