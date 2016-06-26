#include "ModoEquipo.h"

ModoEquipo::ModoEquipo(int cantidadMaximaClientes) {
	this->cantidadClientes = cantidadMaximaClientes;
}

ModoEquipo::~ModoEquipo(void) {
}

char* ModoEquipo::toString() {
	return "Equipo";
}

bool ModoEquipo::hayDisponibilidadEquipoUno() {
	return (this->equipo1.size() < (this->cantidadClientes/2));
}

bool ModoEquipo::hayDisponibilidadEquipoDos() {
	return (this->equipo2.size() < (this->cantidadClientes/2));
}

char* ModoEquipo::getDisponibilidadToString() {
	if (hayDisponibilidad()) {
		return "Disponibilidad";
	}
	else {
		return "No Disponibilidad";
	}
}

bool ModoEquipo::seJuegaPorEquipos() {
	return true;
}

bool ModoEquipo::hayDisponibilidad() {
	if (hayDisponibilidadEquipoUno() && hayDisponibilidadEquipoDos()) {
		return true;
	}
	else {
		return false;
	}
}

void ModoEquipo::asociarUsuarioAEquipo(int idUsuario, char* equipo) {
	if (strcmp(equipo, "1") == 0) {
		this->equipo1.push_back(idUsuario);
	}
	else {
		this->equipo2.push_back(idUsuario);
	}
}

void ModoEquipo::agregarUsuario(int idUsuario) {
	if (hayDisponibilidadEquipoUno()) {
		this->equipo1.push_back(idUsuario);
	}
	else {
		this->equipo2.push_back(idUsuario);
	}
}