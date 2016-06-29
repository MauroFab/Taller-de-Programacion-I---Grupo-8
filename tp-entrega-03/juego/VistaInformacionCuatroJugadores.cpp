#include "VistaInformacionCuatroJugadores.h"

VistaInformacionCuatroJugadores::VistaInformacionCuatroJugadores(SDL_Renderer* renderer) {
	this->renderer = renderer;
	this->fondo = new FondoInicio("fondoInformacionColaboracionCuatroJugadores.bmp", this->renderer);
	this->font = TTF_OpenFont(FUENTE_PATH, 15);

	this->usuario1 = new Etiqueta(this->renderer, this->font);
	this->usuario1->setPosicion(100, 170);
	this->usuario2 = new Etiqueta(this->renderer, this->font);
	this->usuario2->setPosicion(100, 230);
	this->usuario3 = new Etiqueta(this->renderer, this->font);
	this->usuario3->setPosicion(100, 300);
	this->usuario4 = new Etiqueta(this->renderer, this->font);
	this->usuario4->setPosicion(100, 360);
	this->puntos1 = new Etiqueta(this->renderer, this->font);
	this->puntos1->setPosicion(310, 170);
	this->puntos2 = new Etiqueta(this->renderer, this->font);
	this->puntos2->setPosicion(310, 230);
	this->puntos3 = new Etiqueta(this->renderer, this->font);
	this->puntos3->setPosicion(310, 300);
	this->puntos4 = new Etiqueta(this->renderer, this->font);
	this->puntos4->setPosicion(310, 360);
	this->usuarioGanadaor = new Etiqueta(this->renderer, this->font);
	this->usuarioGanadaor->setPosicion(100, 500);
	this->puntosGanador = new Etiqueta(this->renderer, this->font);
	this->puntosGanador->setPosicion(310, 500);

	this->usuarios[0] = this->usuario1;
	this->usuarios[1] = this->usuario2;
	this->usuarios[2] = this->usuario3;
	this->usuarios[3] = this->usuario4;
	
	this->puntos[0] = this->puntos1;
	this->puntos[1] = this->puntos2;
	this->puntos[2] = this->puntos3;
	this->puntos[3] = this->puntos4;
}

VistaInformacionCuatroJugadores::~VistaInformacionCuatroJugadores(void) {
	delete this->fondo;
	delete this->usuario1;
	delete this->usuario2;
	delete this->usuario3;
	delete this->puntos4;
	delete this->puntos1;
	delete this->puntos2;
	delete this->puntos3;
	delete this->puntos4;
	delete this->usuarioGanadaor;
	delete this->puntosGanador;
}

void VistaInformacionCuatroJugadores::mostrar(std::list<EstadoJugador> estadosJugadores) {

	EstadoJugador jugadorGanador;
	EstadoJugador jugadores[CANTIDAD_USUARIOS];
	int i = 0;

	std::list<EstadoJugador>::iterator it;
	// Carga todo las etiquetas con los puntos y nombres de usuario
	for (it = estadosJugadores.begin(); it != estadosJugadores.end(); it++) {

		string nombre = (*it).getNombreUsuario();
		string puntos = StringUtil::intToString((*it).getPuntajeAcumulado());
		int idUsuario = (*it).getid();

		this->usuarios[idUsuario]->setTexto(nombre);
		this->puntos[idUsuario]->setTexto(puntos);

		jugadores[i] = (*it); i++;
	}

	// Busca el jugador con mas puntos
	i = 0; jugadorGanador = jugadores[i]; i++;
	while (i < CANTIDAD_USUARIOS) {
		if (jugadores[i].getPuntajeAcumulado() > jugadorGanador.getPuntajeAcumulado()) {
			jugadorGanador = jugadores[i];
		}
		i++;
	}

	this->usuarioGanadaor->setTexto(jugadorGanador.getNombreUsuario());
	this->puntosGanador->setTexto(StringUtil::intToString(jugadorGanador.getPuntajeAcumulado()));

	this->fondo->render();

	for (int i = 0; i < CANTIDAD_USUARIOS; i++) {
		this->usuarios[i]->render();
		this->puntos[i]->render();
	}

	this->usuarioGanadaor->render();
	this->puntosGanador->render();
}