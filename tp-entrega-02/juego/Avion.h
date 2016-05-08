#pragma once

#include "Constantes.h"
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

		void handleEvent( SDL_Event& e );

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