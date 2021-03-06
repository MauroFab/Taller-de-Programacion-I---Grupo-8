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

	int c = this->equipo1.size() + this->equipo2.size();
	bool v = c == (this->cantidadClientes-1);
	bool f = v && (this->equipo1.empty() || this->equipo2.empty());
	return !f;
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
	if (this->equipo1.empty()) {
		this->equipo1.push_back(idUsuario);
	}
	else if (this->equipo2.empty()) {
		this->equipo2.push_back(idUsuario);
	}
}

std::list<int> ModoEquipo::getJugadoresEquipo(int equipo) {
	if (equipo == 1) {
		return this->equipo1;
	}
	else if (equipo == 2) {
		return this->equipo2;
	}
	std::list<int> lista;
	return lista;
}

std::list<int> ModoEquipo::getJugadores() {
	
	std::list<int> lista;
	std::list<int>::iterator it;
	
	// Primero, los del equipo 1
	for (it = this->equipo1.begin(); it != this->equipo1.end(); it++) {
		lista.push_back(*it);
	}

	// Segundo, los del equipo 2
	for (it = this->equipo2.begin(); it != this->equipo2.end(); it++) {
		lista.push_back(*it);
	}
	return lista;
}

int ModoEquipo::getEquipoDeJugador(int idUsuario) {

	std::list<int>::iterator it;

	for (it = this->equipo1.begin(); it != this->equipo1.end(); it++) {
		if ((*it) == idUsuario) return 1;
	}

	for (it = this->equipo2.begin(); it != this->equipo2.end(); it++) {
		if ((*it) == idUsuario) return 2;
	}
}

bool ModoEquipo::seHaCompletadoLaConfiguracion() {
	return ((this->equipo1.size() + this->equipo2.size()) == this->cantidadClientes);
}