#include "Avion.h"

Avion::Avion(SDL_Renderer* rendererRecibido,int ventanaAncho,int ventanaAlto,AvionView * avionView) {

	this->ventanaAncho = ventanaAncho;
	this->ventanaAlto = ventanaAlto;
	this->avionView = avionView;

    velocidadX = 0;
    velocidadY = 0;

	frame = 0;
	rollFlag = false;

///	AvionView* configAvion = ConfiguracionJuegoXML::getInstance()->getConfiguracionAvion();

//	altoFotograma = configAvion->getAltoFotograma();
//	anchoFotograma = configAvion->getAnchoFotograma();
//	cantDeFotogramas = configAvion->getCantidadDeFotogramas();
//	velocidad = configAvion->getVelocidad();
//	id = configAvion->getId();
	renderer = rendererRecibido;

	texturaAvion = new Textura();
	fotogramas = new SDL_Rect[avionView->spriteXml->getCantidad()];

	if( !texturaAvion->cargarDeArchivo( avionView->spriteXml->getPath(), renderer ) )
	{
		texturaAvion->cargarDeArchivo("avionNoEncontrado.bmp", renderer);
//		cantDeFotogramas = 1;
//		altoFotograma = texturaAvion->getHeight();
//		anchoFotograma = texturaAvion->getWidth();
	}
		for(int i=0; i < avionView->spriteXml->getCantidad(); i++){

			SDL_Rect fotograma;

			fotograma.x = avionView->spriteXml->getAncho()*i;//anchoFotograma * i;
			fotograma.y = 0;
			fotograma.w = avionView->spriteXml->getAncho();//anchoFotograma;
			fotograma.h = avionView->spriteXml->getAlto();//altoFotograma;

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
	//NO se hace DELETE de AvionView, pues es [AGREGACION]
}

void Avion::setPosicion(Posicion pos) {

	this->posicionX = pos.getPosX();
	this->posicionY = pos.getPosY();
}

bool Avion::handleEvent( SDL_Event& e ){
	bool cambiaEstado = false;
	int velocidad = this->avionView->avionModel->velAvion;

    // Si se presiona una tecla
	if( e.type == SDL_KEYDOWN && e.key.repeat == 0){
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
					proyectil->setCoordenasDeComienzo(posicionX + (this->avionView->spriteXml->getAncho() / 2) - 5, posicionY - (this->avionView->spriteXml->getAlto()/24));
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
		if( ( posicionX < 0 ) || ( posicionX + this->avionView->spriteXml->getAncho() > this->ventanaAncho ) ){
			posicionX -= velocidadX;
		}

		// Mueve el avion hacia arriba o hacia abajo
		posicionY += velocidadY;

		// Para que no se salga de la pantalla en Y
		if( ( posicionY < 0 ) || ( posicionY + this->avionView->spriteXml->getAlto() > this->ventanaAlto ) ){
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
	int cantDeFotogramas = this->avionView->spriteXml->getCantidad();
	if (rollFlag)
		++frame;

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

	EstadoAvion*  estado =  new EstadoAvion(this->avionView->avionModel->id, frame, posicionX, posicionY); 
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