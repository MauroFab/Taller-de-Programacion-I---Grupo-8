#pragma once
#ifndef _PROYECTIL_H_
#define _PROYECTIL_H_

#include <stdio.h>
#include "Textura.h"
#include "ConfiguracionJuegoXML.h"
#include "ConfiguracionProyectilXML.h"
#include "EstadoProyectil.h"

//************************
//esto NOO tiene que estar
#define FAKE_2_SCREEN_WIDTH 480
#define FAKE_2_SCREEN_HEIGHT 640

//************************

class Proyectil {

	public:

		static const int ANCHO_PROYECTIL = 11;
		static const int ALTO_PROYECTIL = 25;

		Proyectil(SDL_Renderer* rendererRecibido);

		virtual ~Proyectil(void);

		bool estaEnPantalla();

		void mover();

		void render();

		void setCoordenasDeComienzo(int posX, int posY);

		EstadoProyectil* getEstado();

	private:

		SDL_Rect *fotogramas;
		Textura* texturaProyectil;
		SDL_Renderer* renderer;
		int frame;
		int cantDeFotogramas;
		int anchoFotograma;
		int altoFotograma;

		// Posicion del proyectil
		int posicionX, posicionY;

		int velocidad;

		// Velocidad del proyectil
		int velocidadX, velocidadY;
};

#endif //_PROYECTIL_H_