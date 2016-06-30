#include "ConfiguracionInicialJuego.h"

ConfiguracionInicialJuego* ConfiguracionInicialJuego::instance = NULL;

ConfiguracionInicialJuego::ConfiguracionInicialJuego(void) {
}

ConfiguracionInicialJuego::~ConfiguracionInicialJuego(void) {
	delete this->modoDeJuego;
}

ConfiguracionInicialJuego* ConfiguracionInicialJuego::getInstance() {
	if (instance == NULL) {
		instance = new ConfiguracionInicialJuego();
	}
	return instance;
}
void ConfiguracionInicialJuego::liberar(){
delete instance;
}
void ConfiguracionInicialJuego::inicializar(ServidorXml* servidorXml) {

	int modoDeJuego = servidorXml->getModo();

	if (modoDeJuego == M_MODO_NORMAL_COLABORACION || modoDeJuego == M_MODO_PRACTICA_COLABORACION) {
		this->modoDeJuego = new ModoColaboracion();
	}
	else {
		this->modoDeJuego = new ModoEquipo(servidorXml->getCantidadMaximaClientes());
	}
}

char* ConfiguracionInicialJuego::getModoDeJuego() {
	return this->modoDeJuego->toString();
}

char* ConfiguracionInicialJuego::getDisponibilidad() {
	return this->modoDeJuego->getDisponibilidadToString();
}

bool ConfiguracionInicialJuego::seJuegaPorEquipos() {
	return this->modoDeJuego->seJuegaPorEquipos();
}

bool ConfiguracionInicialJuego::hayDisponibilidad() {
	return this->modoDeJuego->hayDisponibilidad();
}

void ConfiguracionInicialJuego::asociarUsuarioAEquipo(int idUsuario, char* equipo) {
	this->modoDeJuego->asociarUsuarioAEquipo(idUsuario, equipo); 
}

void ConfiguracionInicialJuego::agregarUsuario(int idUsuario) {
	this->modoDeJuego->agregarUsuario(idUsuario);
}

/* Si es en colaboracion, igualmente devuelve la lista con todos los jugadores
	Si el equipo es incorrecto devuelve una lista vacia
*/
std::list<int> ConfiguracionInicialJuego::getJugadoresEquipo(int equipo) {
	return this->modoDeJuego->getJugadoresEquipo(equipo);
}

/* Si es equipos devuelve una lista con todos los jugadores, de la siguiente forma:
	si son dos jugadores por equipo,
	lista = [jugador(equipo1), jugador(equipo1), jugador(equipo2), jugador(equipo2)]
*/
std::list<int> ConfiguracionInicialJuego::getJugadores() {
	return this->modoDeJuego->getJugadores();
}

// Devueve el equipo asociado a un jugador
int ConfiguracionInicialJuego::getEquipoDeJugador(int idUsuario) {
	return this->modoDeJuego->getEquipoDeJugador(idUsuario);
}