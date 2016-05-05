#pragma once

#include "Constantes.h"
#include "Textura.h"
#include "ConfiguracionJuegoXML.h"
#include "ConfiguracionProyectilXML.h"

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

