#pragma once

#include <list>
#include "EstadoJugador.h"
#include "VistaInformacion.h"

using namespace std;

class VistaInformacionCuatroJugadores : public VistaInformacion {

public:
	VistaInformacionCuatroJugadores(SDL_Renderer* renderer);
	virtual ~VistaInformacionCuatroJugadores(void);
	void mostrar(std::list<EstadoJugador> estadosJugadores);
};

