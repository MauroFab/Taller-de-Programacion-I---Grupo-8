#pragma once

#include <list>
#include "EstadoJugador.h"
#include "VistaInformacion.h"

#define CANTIDAD_USUARIOS_TRES 3

using namespace std;

class VistaInformacionTresJugadores : public VistaInformacion {

public:
	VistaInformacionTresJugadores(SDL_Renderer* renderer);
	virtual ~VistaInformacionTresJugadores(void);
	void mostrar(std::list<EstadoJugador> estadosJugadores);
	void reiniciar();
private:
	Etiqueta* usuario1;
	Etiqueta* usuario2;
	Etiqueta* usuario3;
	Etiqueta* puntos1;
	Etiqueta* puntos2;
	Etiqueta* puntos3;
	Etiqueta* usuarioGanadaor;
	Etiqueta* puntosGanador;
	Etiqueta* puntosTotales;
	Etiqueta* usuarios[CANTIDAD_USUARIOS_TRES];
	Etiqueta* puntos[CANTIDAD_USUARIOS_TRES];
};

