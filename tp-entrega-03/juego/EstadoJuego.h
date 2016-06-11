#pragma once
#include "../juego/EstadoAvion.h"
#include <stdio.h>
//Este objeto esta pensado para comunicar el estado del juego del servidor
//Se ira completando junto al modelo

class EstadoJuego
{
public:
	EstadoJuego(EstadoAvion** estadoAvionJugador, int cantidadDeJugadores);
	EstadoJuego(std::list<EstadoAvion*> estadoAvion);
	~EstadoJuego();
	std::list<EstadoAvion*> getEstadoDeLosAviones();

private:
	std::list<EstadoAvion*> estadoDeLosAviones;
};

