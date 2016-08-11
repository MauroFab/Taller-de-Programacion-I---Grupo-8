#include "VistaInformacionTresJugadores.h"

VistaInformacionTresJugadores::VistaInformacionTresJugadores(SDL_Renderer* renderer) {
	this->renderer = renderer;
	this->fondo = new FondoInicio("fondoInformacionColaboracionTresJugadores.bmp", this->renderer);
	this->font = TTF_OpenFont(FUENTE_PATH, 15);

	this->usuario1 = new Etiqueta(this->renderer, this->font);
	this->usuario1->setPosicion(100, 115);
	this->usuario2 = new Etiqueta(this->renderer, this->font);
	this->usuario2->setPosicion(100, 180);
	this->usuario3 = new Etiqueta(this->renderer, this->font);
	this->usuario3->setPosicion(100, 250);
	this->puntos1 = new Etiqueta(this->renderer, this->font);
	this->puntos1->setPosicion(310, 115);
	this->puntos2 = new Etiqueta(this->renderer, this->font);
	this->puntos2->setPosicion(310, 180);
	this->puntos3 = new Etiqueta(this->renderer, this->font);
	this->puntos3->setPosicion(310, 250);
	this->usuarioGanadaor = new Etiqueta(this->renderer, this->font);
	this->usuarioGanadaor->setPosicion(100, 400);
	this->puntosGanador = new Etiqueta(this->renderer, this->font);
	this->puntosGanador->setPosicion(310, 400);
	this->puntosTotales = new Etiqueta(this->renderer, this->font);
	this->puntosTotales->setPosicion(210, 530);

	this->usuarios[0] = this->usuario1;
	this->usuarios[1] = this->usuario2;
	this->usuarios[2] = this->usuario3;
	
	this->puntos[0] = this->puntos1;
	this->puntos[1] = this->puntos2;
	this->puntos[2] = this->puntos3;

	this->seHaGraficado = false;
}

VistaInformacionTresJugadores::~VistaInformacionTresJugadores(void) {
	delete this->fondo;
	delete this->usuario1;
	delete this->usuario2;
	delete this->usuario3;
	delete this->puntos1;
	delete this->puntos2;
	delete this->puntos3;
	delete this->usuarioGanadaor;
	delete this->puntosGanador;
	delete this->puntosTotales;
}

void VistaInformacionTresJugadores::mostrar(std::list<EstadoJugador> estadosJugadores) {

	if (!this->seHaGraficado) {
		EstadoJugador jugadorGanador;
		EstadoJugador jugadores[CANTIDAD_USUARIOS_TRES];
		int i = 0; int puntajeTotal = 0;

		std::list<EstadoJugador>::iterator it;
		// Carga todo las etiquetas con los puntos y nombres de usuario
		for (it = estadosJugadores.begin(); it != estadosJugadores.end(); it++) {

			string nombre = (*it).getNombreUsuario();
			string puntos = StringUtil::intToString((*it).getPuntajeAcumulado());
			int idUsuario = (*it).getid();

			this->usuarios[idUsuario]->setTexto(nombre);
			this->puntos[idUsuario]->setTexto(puntos);

			// Calcula la suma total de puntos
			puntajeTotal = puntajeTotal + (*it).getPuntajeAcumulado();
			jugadores[i] = (*it); i++;
		}

		// Busca el jugador con mas puntos
		i = 0; jugadorGanador = jugadores[i]; i++;
		while (i < CANTIDAD_USUARIOS_TRES) {
			if (jugadores[i].getPuntajeAcumulado() > jugadorGanador.getPuntajeAcumulado()) {
				jugadorGanador = jugadores[i];
			}
			i++;
		}

		this->usuarioGanadaor->setTexto(jugadorGanador.getNombreUsuario());
		this->puntosGanador->setTexto(StringUtil::intToString(jugadorGanador.getPuntajeAcumulado()));

		this->puntosTotales->setTexto(StringUtil::intToString(puntajeTotal));

		this->seHaGraficado = true;
	}

	this->fondo->render();

	for (int i = 0; i < CANTIDAD_USUARIOS_TRES; i++) {
		this->usuarios[i]->render();
		this->puntos[i]->render();
	}

	this->usuarioGanadaor->render();
	this->puntosGanador->render();
	this->puntosTotales->render();
}

void VistaInformacionTresJugadores::reiniciar() {
	this->seHaGraficado = false;
}