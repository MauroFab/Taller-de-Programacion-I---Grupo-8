#pragma once

#include <list>
#include "EstadoJugador.h"
#include "VistaInformacion.h"

using namespace std;

class VistaInformacionDosJugadores : public VistaInformacion {

public:
	VistaInformacionDosJugadores(SDL_Renderer* renderer);
	virtual ~VistaInformacionDosJugadores(void);
	void mostrar(std::list<EstadoJugador> estadosJugadores);
};

