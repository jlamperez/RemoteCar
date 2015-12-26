#ifndef MAQUINA_DE_ESTADO_
#define MAQUINA_DE_ESTADO_

/************************************************************************
*                                                                       *
*       Tipos de datos,                                                 *
*                                                                       *
************************************************************************/
#define NULL 0
#define TRUE 1
#define FALSE 0

typedef unsigned char BOOLEAN;
typedef unsigned char BYTE;

/*Definicion del tipo Accion y Evento*/
typedef void            (*TPFN_ACC)(void); /* Puntero a una funci¢n acci¢n */
typedef BOOLEAN         (*TPFN_EVE)(void); /* Puntero a una funci¢n evento */

/**** NOTA sobre el define DEBUG ****************************************
*                                                                       *
*       Seg£n est‚ definida o n¢ la variable DEBUG, los tipos           *
*       de datos que soportan las estructuras de los aut¢matas,         *
*       contendr n una serie de identificadores de texto para poder     *
*       depurar con m s facilidad. Si se utlizan las macros ITEM_EAC    *
*       este cambio de estruturas es totalmente transparente a la       *
*       programaci¢n.                                                   *
*                                                                       *
*       Cada estado contiene un campo llamado 'ultimo_evento',          *
*       siendo ‚ste un puntero al £ltimo par evento-acci¢n              *
*       que se produjo en ese estado. Si es nulo, es por que se ejecut¢ *
*       el automata, entr¢ en ese estado y no se cumpli¢ ning£n evento  *
*                                                                       *
*       Tambi‚n las rutinas del programa son modificadas, de manera que *
*       se permiten forzar ejecuciones de determinados eventos          *
*       y/o estados.                                                    *
*                                                                       *
************************************************************************/



/************************************************************************
*                                                                       *
*       Uso de la macro ITEM_EAC                                        *
*                                                                       *
*       ITEM_EAC( ESTADO_DESTINO, Evento,  Accion);                     *
*                                                                       *
************************************************************************/



#define ITEM_EAC(ident,event,acci) { ident, #event, event, acci } 

#define ESTADO(nombre)                             \
        const TS_EVEACC x##nombre[] = {
   
#define FIN_ESTADO(nombre, ident, control)         \
	,{0,NULL,NULL,NULL} };                     \
       const TS_ESTADO nombre =            \
      {ident, #ident, control, (TS_EVEACC *) x##nombre};


#define AUTOMATA(nombre)                           \
	const TS_ESTADO * const (x##nombre[]) = {
   
#define FIN_AUTOMATA(nombre,ident, StopC)          \
	   ,NULL };                                \
	 const TS_AUTOMATA nombre =          \
      {ident, 0 ,#nombre, StopC, (TS_ESTADO **) x##nombre};

/*Definicion del tipo de dato que representa una transicion*/
typedef struct {
	  BYTE          id;             /* Identificador del estado destino */
	  char        * nombre;         /* Nombre identificativo de depuraci¢n */
	  TPFN_EVE      evento;         /* Puntero a la funci¢n evento */
	  TPFN_ACC      accion;         /* Puntero a la funci¢n acci¢n */
} TS_EVEACC;

/*Definicion del tipo estado*/
typedef struct {
	  BYTE          id;             /* Identificador del estado */
	  char        * nombre;         /* Nombre identificativo de depuraci¢n */
/*	  TS_EVEACC   * ultimo_evento;   Puntero al £ltimo estado ejecutado */
	  TPFN_ACC      controles;      /* Funci¢n de control del estado */
	  TS_EVEACC   * funcion;        /* Punteros las funciones del estado */
} TS_ESTADO;

/*Definicion del tipo Maquina de Estados*/
typedef struct {
	  BYTE          id;             /* Identificador del automata */
	  BYTE 			id_estado_actual;
	  char        * nombre;         /* Nombre identificativo de depuraci¢n */
	  TPFN_EVE      StopCond;       /* Condici¢n necesaria para la ejecuci¢n */
	  TS_ESTADO   **estado;         /* Matriz de punteros a los ESTADOS */
} TS_AUTOMATA; 





/* Para la ejecuci¢n de automatas del movimiento vertical*/
void EjecutaAutomata( TS_AUTOMATA *elAutomata);
void EjecutaEstado( TS_ESTADO   *elEstado , TS_AUTOMATA *elAutomata);


#endif   /* _AUTOMATA_H entry. */
