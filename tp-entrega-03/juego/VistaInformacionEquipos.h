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
private:
	Etiqueta* usuario1E1;
	Etiqueta* usuario2E1;
	Etiqueta* usuario3E1;
	Etiqueta* usuario1E2;
	Etiqueta* usuario2E2;
	Etiqueta* usuario3E2;
	Etiqueta* puntos1E1;
	Etiqueta* puntos2E1;
	Etiqueta* puntos3E1;
	Etiqueta* puntos1E2;
	Etiqueta* puntos2E2;
	Etiqueta* puntos3E2;
	Etiqueta* equipoGanadaor;
	Etiqueta* puntosGanador;
};

