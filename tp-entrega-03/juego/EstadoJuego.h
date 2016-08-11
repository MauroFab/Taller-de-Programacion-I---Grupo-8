#pragma once

#include "../juego/EstadoAvion.h"
#include "../juego/EstadoMapa.h"
#include "../common/Evento.h"
#include "../juego/EstadoJugador.h"
#include "../juego/EstadoPowerUp.h"
#include "../common/IGenericaVO.h"
#include <stdio.h>

class EstadoJuego {

public:
	//Hay varios constructores por ahora, luego quizas se fusionen

	//Este constructor es bueno para la comunicacion normal del juego
	EstadoJuego(std::list<EstadoAvion*> estadoAvion, 
				std::list<EstadoJugador> estadoJugador,
				std::list<EstadoPowerUp> estadoPowerUp,
				EstadoMapa* estadoMapa);

	//Este se usa si solamente se pretende comunicar un evento, como el inicio de la partida
	EstadoJuego(Evento evento);

	//Este soporta las dos cosas, si solo se necesita una, se puede usar uno de los anteriores
	//Es el que se usa en el protocolo al decodificar tambien
	EstadoJuego(std::list<EstadoAvion*> estadoAviones,  
		std::list<EstadoJugador> estadoJugador,
		std::list<EstadoPowerUp> estadoPowerUp,
		EstadoMapa* estadoMapa,
		Evento evento);

	//Este es como el primero si se quiere cargar con otra estructura los estadoAvion

	//Fuera de uso por ahora
	EstadoJuego(EstadoAvion** estadoAvionJugador, int cantidadDeJugadores);

	Evento* obtenerEvento();
	
	~EstadoJuego();
	std::list<EstadoAvion*> getEstadoDeLosAviones();
	EstadoMapa* getEstadoDelMapa();

	std::list<EstadoJugador> getEstadoDeLosJugadores();
	std::list<EstadoPowerUp> getEstadoPowerUps();
	void toString(TCadena1000 cadena);

private:
	std::list<EstadoAvion*> estadoDeLosAviones;
	std::list<EstadoPowerUp> estadoPowerUps;
	EstadoMapa* estadoMapa;
	Evento* evento;
	std::list<EstadoJugador> estadoJugador;
};