#pragma once

#include <map>
#include "EstadoAvion.h"
#include "Textura.h"

class VistaExplosion {

public:
	VistaExplosion(SDL_Renderer* renderer);
	~VistaExplosion(void);
	void procesarEstadoAvionQueEstaDestruido(EstadoAvion* estadoAvion);
	void reiniciar();
private:
	bool esUnAvionDeUnJugador(EstadoAvion* estadoAvion);
	bool yaPaseElSonidoDeExplosionDe(EstadoAvion* estadoAvion);
	map<int,bool> yaPaseElSonidoDelJugador;
	map<int,int> iteracionesDesdeQueExplotoElAvion;
	void graficarExplosion(EstadoAvion* estadoAvion);
	Textura* texturaExplosion;
	SDL_Renderer* renderer;
};