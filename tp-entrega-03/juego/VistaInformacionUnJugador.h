#pragma once

#include <list>
#include "EstadoJugador.h"
#include "VistaInformacion.h"

using namespace std;

class VistaInformacionUnJugador : public VistaInformacion {

public:
	VistaInformacionUnJugador(SDL_Renderer* renderer);
	virtual ~VistaInformacionUnJugador(void);
	void mostrar(std::list<EstadoJugador> estadosJugadores);
private:
	Etiqueta* nombreUsuario;
	Etiqueta* puntos;
};

