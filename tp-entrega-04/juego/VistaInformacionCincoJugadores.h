#pragma once

#include <list>
#include "EstadoJugador.h"
#include "VistaInformacion.h"

#define CANTIDAD_USUARIOS_CINCO 5

using namespace std;

class VistaInformacionCincoJugadores : public VistaInformacion {

public:
	VistaInformacionCincoJugadores(SDL_Renderer* renderer);
	virtual ~VistaInformacionCincoJugadores(void);
	void mostrar(std::list<EstadoJugador> estadosJugadores);
	void reiniciar();
private:
	Etiqueta* usuario1;
	Etiqueta* usuario2;
	Etiqueta* usuario3;
	Etiqueta* usuario4;
	Etiqueta* usuario5;
	Etiqueta* puntos1;
	Etiqueta* puntos2;
	Etiqueta* puntos3;
	Etiqueta* puntos4;
	Etiqueta* puntos5;
	Etiqueta* usuarioGanadaor;
	Etiqueta* puntosGanador;
	Etiqueta* puntosTotales;
	Etiqueta* usuarios[CANTIDAD_USUARIOS_CINCO];
	Etiqueta* puntos[CANTIDAD_USUARIOS_CINCO];
};

