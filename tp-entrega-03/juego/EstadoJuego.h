#pragma once

#include "../juego/EstadoAvion.h"
#include "../juego/EstadoMapa.h"
#include "../common/Evento.h"

#include <stdio.h>
//Este objeto esta pensado para comunicar el estado del juego del servidor
//Se ira completando junto al modelo

class EstadoJuego {

public:
	//Hay varios constructores por ahora, luego quizas se fusionen

	//Este constructor es bueno para la comunicacion normal del juego
	EstadoJuego(std::list<EstadoAvion*> estadoAvion, EstadoMapa* estadoMapa);

	//Este se usa si solamente se pretende comunicar un evento, como el inicio de la partida
	EstadoJuego(Evento evento);

	//Este soporta las dos cosas, si solo se necesita una, se puede usar uno de los anteriores
	EstadoJuego(std::list<EstadoAvion*> estadoAviones, Evento evento, EstadoMapa* estadoMapa);

	//Este es como el primero si se quiere cargar con otra estructura los estadoAvion
	EstadoJuego(EstadoAvion** estadoAvionJugador, int cantidadDeJugadores);

	Evento* obtenerEvento();
	
	~EstadoJuego();
	std::list<EstadoAvion*> getEstadoDeLosAviones();
	EstadoMapa* getEstadoDelMapa();

private:
	std::list<EstadoAvion*> estadoDeLosAviones;
	EstadoMapa* estadoMapa;
	Evento* evento;
};

