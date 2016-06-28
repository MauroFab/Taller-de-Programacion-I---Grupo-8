#include "GraficadorInformacion.h"

GraficadorInformacion::GraficadorInformacion(SDL_Renderer* renderer) {
}

GraficadorInformacion::~GraficadorInformacion(void) {
}

void GraficadorInformacion::seleccionarVista(int numeroEquipo, int cantidadJugadores) {
	if (numeroEquipo != 0) {
		this->vistaActual = this->vistas[0];
	} else {
		this->vistaActual = this->vistas[cantidadJugadores];
	}
}

void GraficadorInformacion::render(std::list<EstadoJugador> estadosJugadores) {
	this->vistaActual->mostrar(estadosJugadores);
}