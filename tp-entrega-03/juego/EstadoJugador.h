#pragma once
#include "../common/IGenericaVO.h"
#include <stdio.h>
class EstadoJugador
{
public:
	EstadoJugador(int id, int puntajeAcumulado);

	//No usar este constructor por fuera del protocolo
	EstadoJugador();

	~EstadoJugador(void);
	int getid();
	int getPuntajeAcumulado();
	void toString(TCadena1000 cadena);

private:
	int id;
	int puntajeAcumulado;
};

