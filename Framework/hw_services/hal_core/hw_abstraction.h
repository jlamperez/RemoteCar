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
** 	Copyright (c) 2015, Jorge Lamp�rez													**
** 	All rights reserved.																**
** 																						**
******************************************************************************************

VERSION HISTORY:
----------------

Version       : 1
Date          :	29/10/2015
Revised by    : Jorge Lamp�rez
Description   : Implementaci�n p�blica de las funciones del m�dulo hw_abstraction.
				Gestionar el c�digo dependiente de plataforma HW.

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
 * Funci�n de inicializaci�n del UART
 */
void HW_ABSTRACTION_initUART();
/*
 * Funci�n de inicializaci�n del Timer
 */
void HW_ABSTRACTION_initTimer(unsigned int msecs);
/*
 * Funci�n para obtener el contador del Timer
 */
unsigned int HW_ABSTRACTION_getTimerCount();
/*
 * Funci�n para obtener el Step del Timer
 */
unsigned int HW_ABSTRACTION_getStep();
/*
 * Funci�n de inicializaci�n del GPIO
 */
void HW_ABSTRACTION_initGPIO();
/*
 * Funci�n de lectura del Btn Gpio
 */
int HW_ABSTRACTION_readGpioBtnPin();

#endif /* HW_ABSTRACTION_H_ */

/*************************************************************************************/
/** 																			 	**/
/** 						EOF					 								 	**/
/** 														 						**/
/** 																			 	**/
/*************************************************************************************/
