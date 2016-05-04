#pragma once

#include "Constantes.h"
#include "Textura.h"
#include "Proyectil.h"
#include <list>

class Avion {

    public:

		static const int ANCHO_AVION = 64;
		static const int ALTO_AVION = 206;

		static const int VELOCIDAD_AVION = 10;

		Avion(SDL_Renderer* renderer, std::string dirImagenAvion, int cantidadDeFrames, int anchoFotograma, int altoFotograma);

		~Avion();

		void handleEvent( SDL_Event& e );

		void mover();

		void render();

    private:

		SDL_Rect *fotogramas;
		Textura* texturaAvion;
		SDL_Renderer* renderer;
		int frame;
		int cantDeFotogramas;
		bool rollFlag;
		std::list<Proyectil*> proyectiles;

		// Posicion del avion
		int posicionX, posicionY;

		// Velocidad del avion
		int velocidadX, velocidadY;
};