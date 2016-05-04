#pragma once

#include "Constantes.h"
#include "Textura.h"

class Proyectil {

	public:

		static const int ANCHO_PROYECTIL = 47;
		static const int ALTO_PROYECTIL = 44;

		static const int VELOCIDAD_PROYECTIL = 1;

		Proyectil(SDL_Renderer* rendererRecibido, std::string dirImagenProyectil, int cantidadDeFrames, int anchoFotograma, int altoFotograma);

		virtual ~Proyectil(void);

		bool estaEnPantalla();

		void mover();

		void render();

		void setCoordenasDeComienzo(int posX, int posY);

	private:

		SDL_Rect *fotogramas;
		Textura* texturaProyectil;
		SDL_Renderer* renderer;
		int frame;
		int cantDeFotogramas;

		// Posicion del proyectil
		int posicionX, posicionY;

		// Velocidad del proyectil
		int velocidadX, velocidadY;
};

