#ifndef _AVIONFORMACION_H_
#define _AVIONFORMACION_H_

#include "AvionEnemigo.h"

class AvionFormacion : public AvionEnemigo
{
public:
	int idFormacion;	//id de la formacion a la que pertenecen
public:
	AvionFormacion();
	virtual ~AvionFormacion();
};

#endif //_AVIONFORMACION_H_
