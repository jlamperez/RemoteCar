/*
 * simple_buffer.h
 *
 *  Created on: 17/11/2015
 *      Author: Jorge
 */

#ifndef SIMPLE_BUFFER_H_
#define SIMPLE_BUFFER_H_

#ifndef SIMPLE_BUFFER_C_
#define PUBLIC 	extern
#else
#define PUBLIC
#endif


#include "../libs/static_circular_buffer.h"

PUBLIC int buffer;
PUBLIC STATIC_CIRCULAR_BUFFER one_buffer;


#endif /* SIMPLE_BUFFER_H_ */

