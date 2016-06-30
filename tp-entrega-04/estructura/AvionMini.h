#ifndef _AVIONMINI_H_
#define _AVIONMINI_H_

#include "AvionEnemigo.h"
#include "Escenario.h"
class Escenario;
class AvionMini : public AvionEnemigo
{
public:
	Escenario * pEscenario;	
public:
	AvionMini();
	AvionMini(Escenario * escenario);
	AvionMini(int p_x,int p_y);
	AvionMini(Escenario * escenario,int p_x,int p_y);
	virtual ~AvionMini();
	void update();
};

#endif //_AVIONMINI_H_
