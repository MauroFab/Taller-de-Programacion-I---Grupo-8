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