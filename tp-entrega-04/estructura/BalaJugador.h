#ifndef _BALAJUGADOR_H_
#define _BALAJUGADOR_H_

#include "Bala.h"

class BalaJugador : public Bala
{
public:
	int idOwner;
public:
	BalaJugador();
	virtual ~BalaJugador();
};

#endif //_BALAJUGADOR_H_
