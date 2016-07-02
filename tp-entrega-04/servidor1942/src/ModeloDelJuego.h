#pragma once

#include "../../juego/Avion.h"
#include "../../common/Evento.h"
#include "../../common/xml/ServidorXml.h"
#include "../../common/Temporizador.h"
#include "../../juego/EstadoJuego.h"
#include "../../juego/Mapa.h"
#include "../../estructura/AvionEnemigo.h"
#include "AsignadorDeUsuarios.h"
#include "FakeAvionBig.h"
#include "FakeAvionDeFormacion.h"
#include "FakeAvionMiddle.h"
#include "FakeAvionMini.h"
#include "FakeFormacionDeEnemigos.h"
#include "ConfiguracionInicialJuego.h"
#include <vector>

using namespace std;
//MainServidor
class ModeloDelJuego {

public:
	ModeloDelJuego(ServidorXml* servidorXml, AsignadorDeUsuarios* usuarios);
	~ModeloDelJuego();
	void actualizarElJuegoEnBaseA(Evento* evento, int idDelJugadorQueMandoElEvento);
	void actualizarMovimientos();
	
	//El estado es uno que se aloja dinamicamente, y no afecta al juego
	// liberar cuando se termina de usar
	EstadoJuego* obtenerEstadoDelJuego();
private:
	void reiniciarElJuego();
	void preparoEliNivel(int i, ServidorXml* servidorXml);
	void preparoElPrimerNivel();
	void preparoElSegundoNivel();
	EstadoAvion* getEstadoAvionJugador(int idAvion);

	vector<std::list<FakeFormacionDeEnemigos>> formacionesDeLosNiveles;
	vector<std::list<FakeAvionEnemigo*>> enemigosDeLosNiveles;
	vector<std::list<PowerUp>> powerUpsDeLosNiveles;

	std::list<FakeFormacionDeEnemigos> formaciones;
	std::list<FakeAvionEnemigo*> avionesEnemigos;
	std::list<PowerUp> powerUps;

	void setPosicionInicialListAvion();
	Avion** listAvion;
	Mapa* mapa;
	ServidorXml* servidorXml;
	Temporizador* temporizadorEtapa;
	int cantidadMaximaDeUsuarios;
	void crearAviones(ServidorXml* servidorXml, AsignadorDeUsuarios* usuarios);
	list<SuperficieOcupada> getSuperficiesOcupadasPorJugadores();
	void hacerInvulnerablesALosJugadores();
	void hacerVulnerablesALosJugadores();
	bool hayDestruccionDeTodosLosAviones();
	bool estoyEnModoPractica;
	void liberarMemoriaEscenarios();
	void liberarMemoriaEnemigosDelNivel(int nivel);
};