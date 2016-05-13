#include "Avion.h"

Avion::Avion(SDL_Renderer* rendererRecibido) {

    posicionX = FAKE_POS_X;
    posicionY = FAKE_POS_Y;

    velocidadX = 0;
    velocidadY = 0;

	frame = 0;
	rollFlag = false;

	ConfiguracionAvionXML* configAvion = ConfiguracionJuegoXML::getInstance()->getConfiguracionAvion();

	altoFotograma = configAvion->getAltoFotograma();
	anchoFotograma = configAvion->getAnchoFotograma();
	cantDeFotogramas = configAvion->getCantidadDeFotogramas();
	velocidad = configAvion->getVelocidad();
	id = configAvion->getId();
	renderer = rendererRecibido;

	texturaAvion = new Textura();
	fotogramas = new SDL_Rect[cantDeFotogramas];

	if( !texturaAvion->cargarDeArchivo( configAvion->getPathImagen(), renderer ) )
	{
		texturaAvion->cargarDeArchivo("avionNoEncontrado.bmp", renderer);
		cantDeFotogramas = 1;
		altoFotograma = texturaAvion->getHeight();
		anchoFotograma = texturaAvion->getWidth();
	}
		for(int i=0; i < cantDeFotogramas; i++){

			SDL_Rect fotograma;

			fotograma.x = anchoFotograma * i;
			fotograma.y = 0;
			fotograma.w = anchoFotograma;
			fotograma.h = altoFotograma;

			fotogramas[ i ] = fotograma;
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

bool Avion::handleEvent( SDL_Event& e )
{
	bool cambiaEstado = false;

    // Si se presiona una tecla
	if( e.type == SDL_KEYDOWN && e.key.repeat == 0)
    {
        switch( e.key.keysym.sym )
        {
			// Ajusta la velocidad
            case SDLK_UP: velocidadY -= velocidad; cambiaEstado = true; break;
            case SDLK_DOWN: velocidadY += velocidad; cambiaEstado = true; break;
            case SDLK_LEFT: velocidadX -= velocidad; cambiaEstado = true; break;
            case SDLK_RIGHT: velocidadX += velocidad; cambiaEstado = true; break;
			// Realiza el roll
			case SDLK_RETURN: rollFlag = true; cambiaEstado = true; break;
		}
	}
    // Si se libero una tecla
    else if( e.type == SDL_KEYUP && e.key.repeat == 0)
    {
        switch( e.key.keysym.sym )
        {
			// Ajusta la velocidad
            case SDLK_UP: velocidadY += velocidad; cambiaEstado = true; break;
            case SDLK_DOWN: velocidadY -= velocidad; cambiaEstado = true; break;
            case SDLK_LEFT: velocidadX += velocidad; cambiaEstado = true; break;
            case SDLK_RIGHT: velocidadX -= velocidad; cambiaEstado = true; break;

			// Realiza un disparo
			case SDLK_SPACE: {

				if(!rollFlag){
					Proyectil* proyectil = new Proyectil(renderer);
					//El centro del proyectil esta en el pixel 5
					proyectil->setCoordenasDeComienzo(posicionX + (anchoFotograma / 2) - 5, posicionY - (altoFotograma/24));
					proyectiles.push_back(proyectil);
					cambiaEstado = true; 
				}

			} break;
        }
    }

	return cambiaEstado;
}

void Avion::mover() {

	if(!rollFlag){

		// Mueve el avion hacia la derecha o a la izquierda
		 posicionX += velocidadX;

		// Para que no se salga de la pantalla en X
	   if( ( posicionX < 0 ) || ( posicionX + anchoFotograma > FAKE_SCREEN_WIDTH ) ){
			posicionX -= velocidadX;
	   }

		// Mueve el avion hacia arriba o hacia abajo
		posicionY += velocidadY;

		// Para que no se salga de la pantalla en Y
	   if( ( posicionY < 0 ) || ( posicionY + altoFotograma > FAKE_SCREEN_HEIGHT ) ){
		    posicionY -= velocidadY;
	   }
	}
	if(!proyectiles.empty()){
		Proyectil* ultimoProyectil = proyectiles.front();
		if(!ultimoProyectil->estaEnPantalla() ){
			proyectiles.pop_front();
			delete ultimoProyectil;
		}
	}
}

void Avion::render()
{
	if (rollFlag) ++frame;

	SDL_Rect* currentClip = &fotogramas[ frame / cantDeFotogramas ];

	if ((frame / cantDeFotogramas) >= cantDeFotogramas - 1){
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

EstadoAvion* Avion::getEstado() {

	EstadoAvion*  estado =  new EstadoAvion(id, frame, posicionX, posicionY); 

	std::list<EstadoProyectil*> lista;

	std::list<Proyectil*>::iterator it;

	for (it = proyectiles.begin(); it != proyectiles.end(); it++) {

		estado->agregarEstadoProyectil((*it)->getEstado());
	}

	return estado;
}

std::list<EstadoProyectil*> Avion::getEstadoProyectiles() {

	std::list<EstadoProyectil*> lista;

	std::list<Proyectil*>::iterator it;

	for (it = proyectiles.begin(); it != proyectiles.end(); it++) {

		lista.push_back((*it)->getEstado());
	}

	return lista;
}