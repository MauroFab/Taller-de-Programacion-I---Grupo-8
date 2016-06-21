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
	void actualizarMovimientos();

	
	//El estado es uno que se aloja dinamicamente, y no afecta al juego
	// liberar cuando se termina de usar
	EstadoJuego* obtenerEstadoDelJuego();
private:
	EstadoAvion* obtenerEstadoDelAvionDelJugador(int id);
	//Este es un avion enemigo que creo fijo para empezar a probar las colisiones
	AvionEnemigo* avionEnemigo;
	void darPosicionInicialAAviones();
	Avion** avion;
	Mapa* mapa;
	int cantidadMaximaDeUsuarios;
	void crearAviones(ServidorXml* servidorXml);
};