#include "Proyectil.h"


Proyectil::Proyectil(SDL_Renderer* rendererRecibido, std::string dirImagenProyectil, int cantidadDeFotogramas, int anchoFotograma, int altoFotograma) {

    //Initialize the velocity
    mVelX = 0;
    mVelY = 0;

	frame = 0;

	cantDeFotogramas = cantidadDeFotogramas;
	renderer = rendererRecibido;
	texturaProyectil = new Textura();
	fotogramas = new SDL_Rect[cantDeFotogramas];

	bool success = true;
	if( !texturaProyectil->cargarDeArchivo( dirImagenProyectil, renderer ) ) {
		
		printf( "Failed to load missil animation texture!\n" );
		success = false;

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

	mPosX = posX + (Avion::DOT_WIDTH/2);
	mPosY = posY - (Avion::DOT_HEIGHT/32);
}

void Proyectil::move() {

	while (mPosY >= -SCREEN_HEIGHT) {

		SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );
		SDL_RenderClear( renderer );

		Mapa::getInstace()->graficar();

		mVelY -= DOT_VEL;
		mPosY += mVelY;
		render();

		SDL_RenderPresent( renderer );
	}
	
	texturaProyectil->liberar();
	texturaProyectil = NULL;
}

void Proyectil::render() {

	SDL_Rect* currentClip = &fotogramas[ frame / cantDeFotogramas ];

    //Show the dot
	texturaProyectil->render( mPosX, mPosY, renderer, currentClip );
}