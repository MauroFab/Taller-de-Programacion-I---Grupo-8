#include "ModoColaboracion.h"

ModoColaboracion::ModoColaboracion(void) {
}

ModoColaboracion::~ModoColaboracion(void) {
}

char* ModoColaboracion::toString() {
	return "Colaboracion";
}

char* ModoColaboracion::getDisponibilidadToString() {
	return "No Disponibilidad";
}

bool ModoColaboracion::seJuegaPorEquipos() {
	return false;
}

bool ModoColaboracion::hayDisponibilidad() {
	return false;
}

void ModoColaboracion::asociarUsuarioAEquipo(int idUsuario, char* equipo) {
	// No realiza acci�n porque no corresponde
}

void ModoColaboracion::agregarUsuario(int idUsuario) {
	this->usuarios.push_back(idUsuario);
}

std::list<int> ModoColaboracion::getJugadoresEquipo(int equipo) {
	return this->usuarios;
}

std::list<int> ModoColaboracion::getJugadores() {
	return this->usuarios;
}

int ModoColaboracion::getEquipoDeJugador(int idUsuario) {
	return 0;
}

bool ModoColaboracion::seHaCompletadoLaConfiguracion() {
	return true;
}