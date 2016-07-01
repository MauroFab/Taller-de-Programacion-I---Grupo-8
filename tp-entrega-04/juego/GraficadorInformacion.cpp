#include "GraficadorInformacion.h"

GraficadorInformacion::GraficadorInformacion(SDL_Renderer* renderer) {
	this->vistas[0] = new VistaInformacionEquipos(renderer);
	this->vistas[1] = new VistaInformacionUnJugador(renderer);
	this->vistas[2] = new VistaInformacionDosJugadores(renderer);
	this->vistas[3] = new VistaInformacionTresJugadores(renderer);
	this->vistas[4] = new VistaInformacionCuatroJugadores(renderer);
	this->vistas[5] = new VistaInformacionCincoJugadores(renderer);
	this->vistas[6] = new VistaInformacionSeisJugadores(renderer);
}

GraficadorInformacion::~GraficadorInformacion(void) {
	for (int i = 0; i < CANTIDAD_VISTAS; i++) {
		delete this->vistas[i];
	}
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

void GraficadorInformacion::reiniciar() {
	this->vistaActual->reiniciar();
}