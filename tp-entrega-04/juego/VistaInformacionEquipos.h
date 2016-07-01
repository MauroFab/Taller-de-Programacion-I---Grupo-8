#pragma once

#include <list>
#include "EstadoJugador.h"
#include "VistaInformacion.h"

#define EQUIPO_1 1
#define EQUIPO_2 2
#define CANTIDAD_MAXIMA_POR_EQUIPO 3

using namespace std;

class VistaInformacionEquipos : public VistaInformacion {

public:
	VistaInformacionEquipos(SDL_Renderer* renderer);
	virtual ~VistaInformacionEquipos(void);
	void mostrar(std::list<EstadoJugador> estadosJugadores);
	void reiniciar();
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
	
	Etiqueta* equipoU1[CANTIDAD_MAXIMA_POR_EQUIPO];
	Etiqueta* equipoU2[CANTIDAD_MAXIMA_POR_EQUIPO];

	Etiqueta* puntos1[CANTIDAD_MAXIMA_POR_EQUIPO];
	Etiqueta* puntos2[CANTIDAD_MAXIMA_POR_EQUIPO];

	int cantidadEquipo1;
	int cantidadEquipo2;
};

