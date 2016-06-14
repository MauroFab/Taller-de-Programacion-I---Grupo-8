#pragma once
#include "../../juego/Avion.h"
#include "../../common/Evento.h"
#include "../../common/xml/ServidorXml.h"
#include "../../juego/EstadoJuego.h"
#include "../../juego/Mapa.h"

class ModeloDelJuego {

public:
	ModeloDelJuego(ServidorXml* servidorXml, int cantidadMaximaDeUsuarios);
	~ModeloDelJuego();
	void actualizarElJuegoEnBaseA(Evento* evento, int idDelJugadorQueMandoElEvento);
	void avanzarElTiempo();

	//Deberia pedir un estado del juego, no de cada uno en particular
	EstadoAvion* obtenerEstadoDelAvionDelJugador(int id);
	//El estado es uno que se aloja dinamicamente, y no afecta al juego
	// liberar cuando se termina de usar
	EstadoJuego* obtenerEstadoDelJuego();
private:
	void darPosicionInicialAAviones();
	Avion** avion;
	Mapa* mapa;
	int cantidadMaximaDeUsuarios;
	void crearAviones(ServidorXml* servidorXml);
};

