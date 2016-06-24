#ifndef _AVIONMIDDLE_H_
#define _AVIONMIDDLE_H_

#include "AvionEnemigo.h"
#include "Escenario.h"
class Escenario;
class AvionMiddle : public AvionEnemigo
{
public:
	Escenario * pEscenario;
	int puntos_derribo;
	int puntos_solo;
public:
	AvionMiddle();
	AvionMiddle(Escenario * escenario);
	AvionMiddle(int p_x,int p_y);
	AvionMiddle(Escenario * escenario,int p_x,int p_y);	
	virtual ~AvionMiddle();
};

#endif //_AVIONMIDDLE_H_
