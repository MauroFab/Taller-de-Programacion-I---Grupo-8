#include "VistaInformacionEquipos.h"

VistaInformacionEquipos::VistaInformacionEquipos(SDL_Renderer* renderer) {
	this->renderer = renderer;
	this->fondo = new FondoInicio("fondoInformacionEquipos.bmp", this->renderer);
	this->font = TTF_OpenFont(FUENTE_PATH, 15);

	this->usuario1E1 = new Etiqueta(this->renderer, this->font);
	this->usuario1E1->setPosicion(80, 180);
	this->usuario2E1 = new Etiqueta(this->renderer, this->font);
	this->usuario2E1->setPosicion(80, 240);
	this->usuario3E1 = new Etiqueta(this->renderer, this->font);
	this->usuario3E1->setPosicion(80, 300);
	this->usuario1E2 = new Etiqueta(this->renderer, this->font);
	this->usuario1E2->setPosicion(260, 180);
	this->usuario2E2 = new Etiqueta(this->renderer, this->font);
	this->usuario2E2->setPosicion(260, 240);
	this->usuario3E2 = new Etiqueta(this->renderer, this->font);
	this->usuario3E2->setPosicion(260, 300);
	this->puntos1E1 = new Etiqueta(this->renderer, this->font);
	this->puntos1E1->setPosicion(190, 180);
	this->puntos2E1 = new Etiqueta(this->renderer, this->font);
	this->puntos2E1->setPosicion(190, 240);
	this->puntos3E1 = new Etiqueta(this->renderer, this->font);
	this->puntos3E1->setPosicion(190, 300);
	this->puntos1E2 = new Etiqueta(this->renderer, this->font);
	this->puntos1E2->setPosicion(370, 180);
	this->puntos2E2 = new Etiqueta(this->renderer, this->font);
	this->puntos2E2->setPosicion(370, 240);
	this->puntos3E2 = new Etiqueta(this->renderer, this->font);
	this->puntos3E2->setPosicion(370, 300);
	this->equipoGanadaor = new Etiqueta(this->renderer, this->font);
	this->equipoGanadaor->setPosicion(140, 450);
	this->puntosGanador = new Etiqueta(this->renderer, this->font);
	this->puntosGanador->setPosicion(300, 450);

	// Los del equipo 1
	this->equipoU1[0] = this->usuario1E1;
	this->equipoU1[1] = this->usuario2E1;
	this->equipoU1[2] = this->usuario3E1;

	// Los del equipo 2
	this->equipoU2[0] = this->usuario1E2;
	this->equipoU2[1] = this->usuario2E2;
	this->equipoU2[2] = this->usuario3E2;

	// Los puntos del equipo 1
	this->puntos1[0] = this->puntos1E1;
	this->puntos1[1] = this->puntos2E1;
	this->puntos1[2] = this->puntos3E1;

	// Los puntos del equipo 2
	this->puntos2[0] = this->puntos1E2;
	this->puntos2[1] = this->puntos2E2;
	this->puntos2[2] = this->puntos3E2;

	this->seHaGraficado = false;
	this->cantidadEquipo1 = 0;
	this->cantidadEquipo2 = 0;
}

VistaInformacionEquipos::~VistaInformacionEquipos(void) {
	delete this->fondo;
	delete this->usuario1E1;
	delete this->usuario2E1;
	delete this->usuario3E1;
	delete this->usuario1E2;
	delete this->usuario2E2;
	delete this->usuario3E2;
	delete this->puntos1E1;
	delete this->puntos2E1;
	delete this->puntos3E1;
	delete this->puntos1E2;
	delete this->puntos2E2;
	delete this->puntos3E2;
	delete this->equipoGanadaor;
	delete this->puntosGanador;
}

void VistaInformacionEquipos::mostrar(std::list<EstadoJugador> estadosJugadores) {
	
	if (!this->seHaGraficado) {
		EstadoJugador equipoGanador;
		EstadoJugador jugadores1[CANTIDAD_MAXIMA_POR_EQUIPO];
		EstadoJugador jugadores2[CANTIDAD_MAXIMA_POR_EQUIPO];
		int puntaje1 = 0; int puntaje2 = 0;

		std::list<EstadoJugador>::iterator it;
		// Carga todas las etiquetas con los puntos y nombres de usuario
		for (it = estadosJugadores.begin(); it != estadosJugadores.end(); it++) {

			string nombre = (*it).getNombreUsuario();
			string puntos = StringUtil::intToString((*it).getPuntajeAcumulado());

			if ((*it).getEquipo() == EQUIPO_1) {
				this->equipoU1[cantidadEquipo1]->setTexto(nombre);
				this->puntos1[cantidadEquipo1]->setTexto(puntos);
				jugadores1[cantidadEquipo1] = (*it);
				cantidadEquipo1++;
			} else if ((*it).getEquipo() == EQUIPO_2) {
				this->equipoU2[cantidadEquipo2]->setTexto(nombre);
				this->puntos2[cantidadEquipo2]->setTexto(puntos);
				jugadores2[cantidadEquipo2] = (*it);
				cantidadEquipo2++;
			}
		}
		// Sumo los puntajes de cada jugador para cada equipo
		// Equipo 1
		for (int i = 0; i < cantidadEquipo1; i++) {
			puntaje1 = puntaje1 +  jugadores1[i].getPuntajeAcumulado(); 
		}
		// Equipo 2
		for (int i = 0; i < cantidadEquipo2; i++) {
			puntaje2 = puntaje2 + jugadores2[i].getPuntajeAcumulado(); 
		}
		// Decide cual equipo es el ganador
		if (puntaje1 > puntaje2) {
			this->equipoGanadaor->setTexto("Equipo 1");
			this->puntosGanador->setTexto(StringUtil::intToString(puntaje1));
		} else if (puntaje1 < puntaje2) {
			this->equipoGanadaor->setTexto("Equipo 2");
			this->puntosGanador->setTexto(StringUtil::intToString(puntaje2));
		} else {
			this->equipoGanadaor->setTexto("Empate");
			this->puntosGanador->setTexto(StringUtil::intToString(puntaje1));
		}
		this->seHaGraficado = true;
	}

	this->fondo->render();

	for (int i = 0; i < cantidadEquipo1; i++) {
		this->equipoU1[i]->render();
		this->puntos1[i]->render();
	}

	for (int i = 0; i < cantidadEquipo2; i++) {
		this->equipoU2[i]->render();
		this->puntos2[i]->render();
	}

	this->equipoGanadaor->render();
	this->puntosGanador->render();
}

void VistaInformacionEquipos::reiniciar() {
	this->seHaGraficado = false;
	this->cantidadEquipo1 = 0;
	this->cantidadEquipo2 = 0;
}