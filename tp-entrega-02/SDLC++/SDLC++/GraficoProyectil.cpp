#include "GraficoProyectil.h"


GraficoProyectil::GraficoProyectil(SDL_Renderer* renderer, std::string pathProyectil, int cantFotogramas, int ancho, int alto) {

	textura = new Textura();
	fotogramas = new SDL_Rect[cantFotogramas];
	cantidadFotogramas = cantFotogramas;

	if( !textura->cargarDeArchivo( pathProyectil, renderer ) ) {
		
		printf( "Failed to load missil animation texture!\n" );

	} else {

		for (int i = 0; i < cantidadFotogramas; i++) {

			SDL_Rect fotograma;

			fotograma.x = ancho * i;
			fotograma.y = 0;
			fotograma.w = ancho;
			fotograma.h = alto;

			fotogramas[ i ] = fotograma;
		}
	}
}

GraficoProyectil::~GraficoProyectil(void) {

	delete [] fotogramas;
	textura->liberar();
}

Textura* GraficoProyectil::getTextura() {
	return textura;
}

SDL_Rect* GraficoProyectil::getCurrentClip(int frame) {

	return &fotogramas[ frame / cantidadFotogramas ];
}
