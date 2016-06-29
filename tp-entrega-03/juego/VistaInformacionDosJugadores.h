#pragma once

#include <list>
#include "EstadoJugador.h"
#include "VistaInformacion.h"

#define CANTIDAD_USUARIOS_DOS 2

using namespace std;

class VistaInformacionDosJugadores : public VistaInformacion {

public:
	VistaInformacionDosJugadores(SDL_Renderer* renderer);
	virtual ~VistaInformacionDosJugadores(void);
	void mostrar(std::list<EstadoJugador> estadosJugadores);
private:
	Etiqueta* usuario1;
	Etiqueta* usuario2;
	Etiqueta* puntos1;
	Etiqueta* puntos2;
	Etiqueta* usuarioGanadaor;
	Etiqueta* puntosGanador;
	Etiqueta* usuarios[CANTIDAD_USUARIOS_DOS];
	Etiqueta* puntos[CANTIDAD_USUARIOS_DOS];
};

