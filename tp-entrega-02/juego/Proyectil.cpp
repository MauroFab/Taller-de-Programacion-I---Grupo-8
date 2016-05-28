#include "Proyectil.h"

Proyectil::Proyectil(SDL_Renderer* rendererRecibido) {

    velocidadX = 0;
    velocidadY = 0;

	frame = 0;

//	ConfiguracionProyectilXML* configProyectil = ConfiguracionJuegoXML::getInstance()->getConfiguracionProyectil();
	BalaView * balaView = ConfiguracionJuegoXML::getInstance()->balaView;

	altoFotograma = balaView->spriteXml->getAlto();
	anchoFotograma = balaView->spriteXml->getAncho();
	cantDeFotogramas = balaView->spriteXml->getCantidad();
	velocidad = balaView->balaModel->velBala;
	velocidadY -= velocidad;
	renderer = rendererRecibido;
	texturaProyectil = new Textura();
	fotogramas = new SDL_Rect[cantDeFotogramas];
	
	if( !texturaProyectil->cargarDeArchivo( balaView->spriteXml->getPath(), renderer ) ) {
		
		printf( "Failed to load missil animation texture!\n" );

	} else {

		for (int i = 0; i < cantDeFotogramas; i++) {

			SDL_Rect fotograma;

			fotograma.x = anchoFotograma * i;
			fotograma.y = 0;
			fotograma.w = anchoFotograma;
			fotograma.h = altoFotograma;

			fotogramas[ i ] = fotograma;
		}
	}
}

Proyectil::~Proyectil(void) {

	delete [] fotogramas;

	if (texturaProyectil != NULL) texturaProyectil->liberar();
}

void Proyectil::setCoordenasDeComienzo(int posX, int posY) {

	posicionX = posX;
	posicionY = posY;
}

bool Proyectil::estaEnPantalla() {
	return (posicionY >= - FAKE_2_SCREEN_HEIGHT);
}

void Proyectil::mover() {
	posicionY += velocidadY;
}

void Proyectil::render() {

	SDL_Rect* currentClip = &fotogramas[ frame / cantDeFotogramas ];

    // Muestra el proyectil
	texturaProyectil->render( posicionX, posicionY, renderer, currentClip );
}

EstadoProyectil* Proyectil::getEstado() {

	return new EstadoProyectil(frame, posicionX, posicionY);
}