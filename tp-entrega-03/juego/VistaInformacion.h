#pragma once

#include <SDL2\SDL.h>
#include <list>
#include "EstadoJugador.h"

using namespace std;

class VistaInformacion {

public:
	VistaInformacion(void);
	virtual ~VistaInformacion(void);
	virtual void mostrar(std::list<EstadoJugador> estadosJugadores);
};

