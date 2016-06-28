#pragma once

#include <SDL2\SDL.h>
#include <list>
#include "EstadoJugador.h"
#include "VistaInformacion.h"
#include "VistaInformacionEquipos.h"
#include "VistaInformacionUnJugador.h"
#include "VistaInformacionDosJugadores.h"
#include "VistaInformacionTresJugadores.h"
#include "VistaInformacionCuatroJugadores.h"

#define CANTIDAD_VISTAS 4

class GraficadorInformacion {

public:
	GraficadorInformacion(SDL_Renderer* renderer);
	virtual ~GraficadorInformacion(void);

	void seleccionarVista(int numeroEquipo, int cantidadJugadores);
	void render(std::list<EstadoJugador> estadosJugadores);
private:
	SDL_Renderer* renderer;
	VistaInformacion* vistas[CANTIDAD_VISTAS];
	VistaInformacion* vistaActual;
};

