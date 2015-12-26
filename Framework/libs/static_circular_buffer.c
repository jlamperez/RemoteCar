/*
 * static_circular_buffer.c
 *
 *  Created on: 17/11/2015
 *      Author: Jorge
 */

#include <string.h>
#include "static_circular_buffer.h"

void STATIC_CIRCULAR_BUFFER_init(STATIC_CIRCULAR_BUFFER *obj){
	obj->head = 0;
	obj->tail = 0;
	obj->writing = 0;
	obj->empty = 1;
}
unsigned int STATIC_CIRCULAR_BUFFER_insertMSG(STATIC_CIRCULAR_BUFFER *obj ,  MSG msg  ){
	int freeDataCount , ret;
	freeDataCount = STATIC_CIRCULAR_BUFFER_freeDataCount(obj);
	if (  freeDataCount > 0 ){
		strcpy( (obj->Buffer[ obj->head ]).text ,  msg.text ) ;
		obj->head++;
		if ( obj->head == MAX_BUFFER) obj->head = 0;
		obj->empty = 0;
		ret = 1;
	}else{
		ret = 0;
	}
	return ret;
}
MSG STATIC_CIRCULAR_BUFFER_readMSG(STATIC_CIRCULAR_BUFFER *obj ){
	MSG  ret;
	if ( obj->empty ){
		strcpy( ret.text , -1);
	}else{
		strcpy( ret.text ,  obj->Buffer[ obj->tail ].text);
		obj->tail++;
		if (obj->tail == MAX_BUFFER) obj->tail = 0;
		if (obj->tail == obj->head) obj->empty = 1;
	}
	return ret;
}
unsigned int STATIC_CIRCULAR_BUFFER_freeDataCount(STATIC_CIRCULAR_BUFFER *obj){
	unsigned int ret = 0;
	if ( obj->tail > obj->head ){
		ret = obj->tail-(obj->head );
	}else{
		//cuando la cola y la cabez son iguales puede estar vacio o lleno.
		if (obj->empty){
			ret = MAX_BUFFER;
		}else{
			if ( obj->head == obj->tail ){
				ret = 0;
			}else{
				ret = MAX_BUFFER-(obj->head - obj->tail);
			}
		}
	}
	return ret;
}
unsigned int STATIC_CIRCULAR_BUFFER_dataCount(STATIC_CIRCULAR_BUFFER *obj){
	unsigned int ret = 0;
	if ( obj->tail > obj->head ){
		ret = (obj->head+MAX_BUFFER)-obj->tail;
	}else{
		//cuando la cola y la cabez son iguales puede estar vacio o lleno.
		if ( obj->empty){
			ret = 0;
		}else{
			if ( obj->head == obj->tail ){
				ret = MAX_BUFFER;
			}else{
				ret = (obj->head - obj->tail);
			}
		}
	}
	return ret;
}
unsigned int STATIC_CIRCULAR_BUFFER_existChar(STATIC_CIRCULAR_BUFFER *obj, MSG msg){
	int i = 0, encontrado = 0 , cont = 0 , ret = 0, len;
	i = obj->tail;
	len =  STATIC_CIRCULAR_BUFFER_dataCount(obj);
	while ( ( cont < len ) && !( encontrado ) ){
		if ( strcmp ( (obj->Buffer[i]).text , msg.text ) ){
			encontrado = 1;
		}
		cont++;
		i++;
		if ( i == MAX_BUFFER) i=0;
	}
	if ( encontrado ){
		ret = cont;
	}
	return ret;
}


