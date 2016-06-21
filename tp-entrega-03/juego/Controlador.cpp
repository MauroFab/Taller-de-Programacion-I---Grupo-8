#include "Controlador.h"

Controlador::Controlador(){
}

Controlador::~Controlador(void){
}

void Controlador::procesarTeclasPresionadas(SDL_Event& e){
	Evento* evento;
    // Si se presiona una tecla
	if( e.type == SDL_KEYDOWN && e.key.repeat == 0){
        switch( e.key.keysym.sym )
        {
            case SDLK_UP:{
				evento = new Evento(apretadaLaTeclaDeMovimientoHaciaArriba);
				notificar(evento);
				};
				break;
            case SDLK_DOWN:{
				evento = new Evento(apretadaLaTeclaDeMovimientoHaciaAbajo);
				notificar(evento);
				};
				break;
            case SDLK_LEFT:{
				evento = new Evento(apretadaLaTeclaDeMovimientoHaciaIzquierda);
				notificar(evento);
				};
				break;
            case SDLK_RIGHT: {
				evento = new Evento(apretadaLaTeclaDeMovimientoHaciaDerecha);
				notificar(evento);
				};
				break;
			case SDLK_SPACE:{
				evento = new Evento(apretadaLaTeclaDeDisparo);
				notificar(evento);
				// Reproduce el sonido de disparo
				Mix_PlayChannel( -1, CacheSonido::getInstance()->getChunk(DISPARO), 0 );
				};
				break;
			case SDLK_RETURN:{
				evento = new Evento(apretadaLaTeclaDeRoll);
				notificar(evento);
				};
				break;
		}
	}
    // Si se libero una tecla
    else if( e.type == SDL_KEYUP && e.key.repeat == 0)
    {
        switch( e.key.keysym.sym )
        {
            case SDLK_UP:{
				evento = new Evento(soltadaLaTeclaDeMovimientoHaciaArriba);
				notificar(evento);
				};
				break;
            case SDLK_DOWN:{
				evento = new Evento(soltadaLaTeclaDeMovimientoHaciaAbajo);
				notificar(evento);
				};
				break;
            case SDLK_LEFT:{
				evento = new Evento(soltadaLaTeclaDeMovimientoHaciaIzquierda);
				notificar(evento);
				};
				break;
            case SDLK_RIGHT: {
				evento = new Evento(soltadaLaTeclaDeMovimientoHaciaDerecha);
				notificar(evento);
				};
				break;
			case SDLK_SPACE:{
				evento = new Evento(soltadaLaTeclaDeDisparo);
				notificar(evento);
				};
				break;
			case SDLK_RETURN:{
				evento = new Evento(soltadaLaTeclaDeRoll);
				notificar(evento);
				};
				break;
		}
	}
}