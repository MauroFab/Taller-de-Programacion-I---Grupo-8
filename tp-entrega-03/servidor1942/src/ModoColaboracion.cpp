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
	// No realiza acción porque no corresponde
}

void ModoColaboracion::agregarUsuario(int idUsuario) {
	this->usuarios.push_back(idUsuario);
}