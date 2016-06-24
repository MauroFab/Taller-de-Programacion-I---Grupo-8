#ifndef _AVIONJUGADOR_H_
#define _AVIONJUGADOR_H_

#include <iostream>

#include "ObjetoItem.h"
#include "BalaJugador.h"
using namespace std;

class AvionJugador : public ObjetoItem
{
public:
	int idEquipo;
	int puntaje;
	int energia;
	bool bUnaVez;
public:
	AvionJugador();
	AvionJugador(int p_x,int p_y);
	virtual ~AvionJugador();
	bool sinEquipo();
	BalaJugador * aumentarBala();
	void takePuntaje(int puntaje);
	void morir();
	void update();
};

#endif //_AVIONJUGADOR_H_
