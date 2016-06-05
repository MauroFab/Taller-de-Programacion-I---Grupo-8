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
			// Ajusta la velocidad
            case SDLK_UP: avion->darVelocidadHaciaArriba(); break;
            case SDLK_DOWN: avion->darVelocidadHaciaAbajo(); break;
            case SDLK_LEFT: avion->darVelocidadHaciaLaIzquierda(); break;
            case SDLK_RIGHT: avion->darVelocidadHaciaLaDerecha(); break;
			case SDLK_SPACE: avion->disparar(); break;
			case SDLK_RETURN: avion->hacerUnRoll(); break;
			// Realiza el roll
			//case SDLK_RETURN: rollFlag = true; break;
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

			// Realiza un disparo
			case SDLK_SPACE: {
				//proyectiles
				/*if(!rollFlag){
					Proyectil* proyectil = new Proyectil(renderer);
					//El centro del proyectil esta en el pixel 5
					proyectil->setCoordenasDeComienzo(posicionX + (this->avionView->spriteXml->getAncho() / 2) - 5, posicionY - (this->avionView->spriteXml->getAlto()/24));
					proyectiles.push_back(proyectil);
					cambiaEstado = true; 
				}
				*/
			} break;
		}
	}
}