#pragma once
#include "../juego/Avion.h"
#include "../common/Evento.h"
#include "../common/xml/ServidorXml.h"
#include "../juego/EstadoJuego.h"

class ModeloDelJuego
{
public:
	ModeloDelJuego(ServidorXml* servidorXml, int cantidadMaximaDeUsuarios);
	~ModeloDelJuego();
	void actualizarElJuegoEnBaseA(Evento* evento, int idDelJugadorQueMandoElEvento);
	void avanzarElTiempo();

	//Deberia pedir un estado del juego, no de cada uno en particular
	EstadoAvion* obtenerEstadoDelAvionDelJugador(int id);
	EstadoJuego* obtenerEstadoDelJuego();
private:
	void darPosicionInicialAAviones();
	Avion** avion;
	int cantidadMaximaDeUsuarios;
	void crearAviones(ServidorXml* servidorXml);
};

