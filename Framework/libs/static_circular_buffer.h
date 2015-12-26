/*
 * static_circular_buffer.h
 *
 *  Created on: 17/11/2015
 *      Author: Jorge
 */

#ifndef STATIC_CIRCULAR_BUFFER_H_
#define STATIC_CIRCULAR_BUFFER_H_

#define MAX_BUFFER 1024

typedef struct {
	char text[30];
} MSG;

typedef struct {
	//BUFFER CIRCULAR
	MSG Buffer[MAX_BUFFER];
	unsigned int tail;
	unsigned int head;
	unsigned int length;
	unsigned char empty;
	unsigned char writing;
} STATIC_CIRCULAR_BUFFER;

void STATIC_CIRCULAR_BUFFER_init(STATIC_CIRCULAR_BUFFER *obj);
unsigned int STATIC_CIRCULAR_BUFFER_insertMSG(STATIC_CIRCULAR_BUFFER *obj,
		MSG msg);
MSG STATIC_CIRCULAR_BUFFER_readMSG(STATIC_CIRCULAR_BUFFER *obj);
unsigned int STATIC_CIRCULAR_BUFFER_freeDataCount(STATIC_CIRCULAR_BUFFER *obj);
unsigned int STATIC_CIRCULAR_BUFFER_dataCount(STATIC_CIRCULAR_BUFFER *obj);
unsigned int STATIC_CIRCULAR_BUFFER_existMSG(STATIC_CIRCULAR_BUFFER *obj,
		MSG msg);

#endif /* STATIC_CIRCULAR_BUFFER_H_ */
