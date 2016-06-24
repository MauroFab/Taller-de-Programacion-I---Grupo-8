#ifndef _AVIONFORMACION_H_
#define _AVIONFORMACION_H_

#include "AvionEnemigo.h"
#include "Escenario.h"
class Escenario;
class AvionFormacion : public AvionEnemigo
{
public:
	Escenario * pEscenario;	
	int idFormacion;	//id de la formacion a la que pertenecen
	int puntos_formacion;
public:
	AvionFormacion();
	AvionFormacion(Escenario * escenario);
	AvionFormacion(int p_x,int p_y);
	AvionFormacion(Escenario * escenario,int p_x,int p_y);	
	virtual ~AvionFormacion();
};

#endif //_AVIONFORMACION_H_
