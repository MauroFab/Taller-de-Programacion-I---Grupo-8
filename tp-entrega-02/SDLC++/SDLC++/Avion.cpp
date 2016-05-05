#include "Avion.h"

Avion::Avion(SDL_Renderer* rendererRecibido, std::string dirImagenAvion, int cantidadDeFotogramas, int anchoFotogramaRecibido, int altoFotogramaRecibido) {

    posicionX = 200;
    posicionY = 400;

    velocidadX = 0;
    velocidadY = 0;

	frame = 0;
	rollFlag = false;

	altoFotograma = altoFotogramaRecibido;
	anchoFotograma = anchoFotogramaRecibido;
	cantDeFotogramas = cantidadDeFotogramas;
	renderer = rendererRecibido;
	texturaAvion = new Textura();
	fotogramas = new SDL_Rect[cantDeFotogramas];

	if( !texturaAvion->cargarDeArchivo( dirImagenAvion, renderer ) )
	{
		printf( "Failed to load plane animation texture!\n" );
	}
	else
	{
		for(int i=0; i < cantDeFotogramas; i++){

			SDL_Rect fotograma;

			fotograma.x = anchoFotograma * i;
			fotograma.y = 0;
			fotograma.w = anchoFotograma;
			fotograma.h = altoFotograma;

			fotogramas[ i ] = fotograma;
		}
	}
}

Avion::~Avion() {

	delete [] fotogramas;
	texturaAvion->liberar();

	std::list<Proyectil*>::iterator it;

	for (it = proyectiles.begin(); it != proyectiles.end(); it++) {
		delete (*it);
	}
}

void Avion::handleEvent( SDL_Event& e )
{
    // Si se presiona una tecla
	if( e.type == SDL_KEYDOWN && e.key.repeat == 0 )
    {
        switch( e.key.keysym.sym )
        {
			// Ajusta la velocidad
            case SDLK_UP: velocidadY -= VELOCIDAD_AVION; break;
            case SDLK_DOWN: velocidadY += VELOCIDAD_AVION; break;
            case SDLK_LEFT: velocidadX -= VELOCIDAD_AVION; break;
            case SDLK_RIGHT: velocidadX += VELOCIDAD_AVION; break;
			
			// Realiza el roll
			case SDLK_RETURN: rollFlag = true; break;
        }
    }

    // Si se libero una tecla
    else if( e.type == SDL_KEYUP && e.key.repeat == 0 )
    {
        switch( e.key.keysym.sym )
        {
			// Ajusta la velocidad
            case SDLK_UP: velocidadY += VELOCIDAD_AVION; break;
            case SDLK_DOWN: velocidadY -= VELOCIDAD_AVION; break;
            case SDLK_LEFT: velocidadX += VELOCIDAD_AVION; break;
            case SDLK_RIGHT: velocidadX -= VELOCIDAD_AVION; break;

			// Realiza un disparo
			case SDLK_SPACE: {

				Proyectil* proyectil = new Proyectil(renderer, "proyectil2.bmp", 1, 11, 25);
				//El centro del proyectil esta en el pixel 5
				proyectil->setCoordenasDeComienzo(posicionX + (anchoFotograma / 2) - 5, posicionY - (altoFotograma/24));
				proyectiles.push_back(proyectil);

							 } break;
        }
    }
}

void Avion::mover() {

	// Mueve el avion hacia la derecha o a la izquierda
    posicionX += velocidadX;

	// Para que no se salga de la pantalla en X
    if( ( posicionX < 0 ) || ( posicionX + anchoFotograma > SCREEN_WIDTH ) )
    {
        posicionX -= velocidadX;
    }

	// Mueve el avion hacia arriba o hacia abajo
    posicionY += velocidadY;

    // Para que no se salga de la pantalla en Y
    if( ( posicionY < 0 ) || ( posicionY + altoFotograma > SCREEN_HEIGHT ) )
    {
        posicionY -= velocidadY;
    }
}

void Avion::render()
{
	if (rollFlag) ++frame;

	SDL_Rect* currentClip = &fotogramas[ frame / cantDeFotogramas ];

	if ((frame / cantDeFotogramas) >= cantDeFotogramas){
		frame = 0;
		rollFlag = false;
	}

	std::list<Proyectil*>::iterator it;

	for (it = proyectiles.begin(); it != proyectiles.end(); it++) {
		
		if ((*it)->estaEnPantalla()) {
			
			(*it)->mover();
			(*it)->render();
		}
	}

    // Muestra el avion
	texturaAvion->render( posicionX, posicionY, renderer, currentClip );
}
