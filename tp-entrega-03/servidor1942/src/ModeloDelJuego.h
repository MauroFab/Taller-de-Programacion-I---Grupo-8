#pragma once

#include "../../juego/Avion.h"
#include "../../common/Evento.h"
#include "../../common/xml/ServidorXml.h"
#include "../../juego/EstadoJuego.h"
#include "../../juego/Mapa.h"
#include "../../estructura/AvionEnemigo.h"
#include "FakeAvionBig.h"
using namespace std;
//MainServidor
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
	EstadoAvion* getEstadoAvionJugador(int idAvion);

	std::list<FakeAvionEnemigo> avionesEnemigos;
	std::list<PowerUp> powerUps;
	void setPosicionInicialListAvion();
	Avion** listAvion;
	Mapa* mapa;
	int cantidadMaximaDeUsuarios;
	void crearAviones(ServidorXml* servidorXml);
	AvionEnemigo * avionEnemigoBeta;
};