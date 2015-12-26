
#include "maquina_de_estados.h"

void EjecutaAutomata(TS_AUTOMATA *elAutomata)
{
	TS_ESTADO **Indx;    /* Valor indice rastreador */

	if (elAutomata->StopCond())  return;

	for (Indx = elAutomata->estado; *Indx != NULL; ++Indx)
	{
	    if (elAutomata->id_estado_actual == (*Indx)->id)
	    {
			EjecutaEstado(*Indx , elAutomata);
			return;
	    }
	}

}


void EjecutaEstado(TS_ESTADO *elEstado , TS_AUTOMATA *elAutomata)
{
	TS_EVEACC *Indx;   /* Indice de rastreo */

	(*elEstado->controles)();

	for (Indx = elEstado->funcion; Indx->evento != NULL; ++Indx)
	{
		if (Indx->evento() == TRUE)
		{
			if (Indx->accion != NULL)
			{
				Indx->accion();
			}
			if (Indx->id != elAutomata->id_estado_actual)
			{
				elAutomata->id_estado_actual = Indx->id;
				return;
			}

		}
	}
}
