#pragma once

#include <map>
#include "EstadoAvion.h"
class VistaExplosion
{
public:
	VistaExplosion(void);
	~VistaExplosion(void);
	void procesarEstadoAvionQueEstaDestruido(EstadoAvion* estadoAvion);

private:
	bool esUnAvionDeUnJugador(EstadoAvion* estadoAvion);
	bool yaPaseElSonidoDeExplosionDe(EstadoAvion* estadoAvion);
	map<int,bool> yaPaseElSonidoDelJugador;
};

