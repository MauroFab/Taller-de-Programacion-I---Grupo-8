#pragma once
#ifndef _AVION_H_
#define _AVION_H_

#include <SDL2\SDL.h>
#include <SDL2\SDL_image.h>
#include <stdio.h>
#include <string>

//************************
//esto NOO tiene que estar
#define FAKE_SCREEN_WIDTH 480
#define FAKE_SCREEN_HEIGHT 640

#define FAKE_POS_X 200
#define FAKE_POS_Y 400
//************************

#include "Textura.h"
#include "Proyectil.h"
#include "ConfiguracionJuegoXML.h"
#include "ConfiguracionAvionXML.h"
#include "EstadoAvion.h"
#include "EstadoProyectil.h"
#include <list>

class Avion {

    public:

		Avion(SDL_Renderer* renderer);

		~Avion();

		bool handleEvent( SDL_Event& e );

		void mover();

		void render();

		EstadoAvion* getEstado();

		std::list<EstadoProyectil*> getEstadoProyectiles();

    private:

		SDL_Rect *fotogramas;
		Textura* texturaAvion;
		SDL_Renderer* renderer;
		int frame;
		int cantDeFotogramas;
		int anchoFotograma;
		int altoFotograma;
		int id;

		bool rollFlag;
		std::list<Proyectil*> proyectiles;

		// Posicion del avion
		int posicionX, posicionY;

		int velocidad;

		// Velocidad del avion
		int velocidadX, velocidadY;
};
#endif //_AVION_H_
