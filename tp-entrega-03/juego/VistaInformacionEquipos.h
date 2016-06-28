#pragma once

#include <list>
#include "EstadoJugador.h"
#include "VistaInformacion.h"

using namespace std;

class VistaInformacionEquipos : public VistaInformacion {

public:
	VistaInformacionEquipos(SDL_Renderer* renderer);
	virtual ~VistaInformacionEquipos(void);
	void mostrar(std::list<EstadoJugador> estadosJugadores);
};

