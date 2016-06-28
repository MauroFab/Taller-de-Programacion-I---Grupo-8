#pragma once

#include <list>
#include "EstadoJugador.h"

class VistaInformacion {

public:
	VistaInformacion(void);
	virtual ~VistaInformacion(void);
	virtual void mostrar(std::list<EstadoJugador> estadosJugadores);
};

