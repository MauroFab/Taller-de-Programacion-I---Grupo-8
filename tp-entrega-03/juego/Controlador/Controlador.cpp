#include "Controlador.h"


Controlador::Controlador(Avion* avionRecibido){
	this->avion = avionRecibido;
}



Controlador::~Controlador(void)
{
}

void Controlador::procesarTeclasPresionadas(SDL_Event& e){

    // Si se presiona una tecla
	if( e.type == SDL_KEYDOWN && e.key.repeat == 0){
        switch( e.key.keysym.sym )
        {
            case SDLK_UP: avion->darVelocidadHaciaArriba(); break;
            case SDLK_DOWN: avion->darVelocidadHaciaAbajo(); break;
            case SDLK_LEFT: avion->darVelocidadHaciaLaIzquierda(); break;
            case SDLK_RIGHT: avion->darVelocidadHaciaLaDerecha(); break;
			case SDLK_SPACE: avion->disparar(); break;
			case SDLK_RETURN: avion->hacerUnRoll(); break;
		}
	}
    // Si se libero una tecla
    else if( e.type == SDL_KEYUP && e.key.repeat == 0)
    {
        switch( e.key.keysym.sym )
        {
			// Ajusta la velocidad
            case SDLK_UP: avion->quitarVelocidadHaciaArriba(); break;
            case SDLK_DOWN: avion->quitarVelocidadHaciaAbajo();break;
            case SDLK_LEFT: avion->quitarVelocidadHaciaLaIzquierda();break;
            case SDLK_RIGHT: avion->quitarVelocidadHaciaLaDerecha();break;
		}
	}
}