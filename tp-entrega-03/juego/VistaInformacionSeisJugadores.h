#pragma once

#include <list>
#include "EstadoJugador.h"
#include "VistaInformacion.h"

#define CANTIDAD_USUARIOS_SEIS 6

using namespace std;

class VistaInformacionSeisJugadores : public VistaInformacion {

public:
	VistaInformacionSeisJugadores(SDL_Renderer* renderer);
	~VistaInformacionSeisJugadores(void);
	void mostrar(std::list<EstadoJugador> estadosJugadores);
	void reiniciar();
private:
	Etiqueta* usuario1;
	Etiqueta* usuario2;
	Etiqueta* usuario3;
	Etiqueta* usuario4;
	Etiqueta* usuario5;
	Etiqueta* usuario6;
	Etiqueta* puntos1;
	Etiqueta* puntos2;
	Etiqueta* puntos3;
	Etiqueta* puntos4;
	Etiqueta* puntos5;
	Etiqueta* puntos6;
	Etiqueta* usuarioGanadaor;
	Etiqueta* puntosGanador;
	Etiqueta* puntosTotales;
	Etiqueta* usuarios[CANTIDAD_USUARIOS_SEIS];
	Etiqueta* puntos[CANTIDAD_USUARIOS_SEIS];
};

