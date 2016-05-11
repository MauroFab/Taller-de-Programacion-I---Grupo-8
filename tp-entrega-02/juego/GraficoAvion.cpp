#include "GraficoAvion.h"


GraficoAvion::GraficoAvion(SDL_Renderer* renderer, int id, std::string pathAvion, int cantFotogramas, int ancho, int alto) {

	this->id = id;
	textura = new Textura();
	fotogramas = new SDL_Rect[cantFotogramas + 1];
	cantidadFotogramas = cantFotogramas;

	if( !textura->cargarDeArchivo( pathAvion, renderer ) ) {

		textura->cargarDeArchivo(FAKE_PATH_AVION_NOT_ENC, renderer);
		cantidadFotogramas = 1;

	} else {
		//1 mas para el grisado
		for(int i=0; i < cantidadFotogramas + 1; i++) {

			SDL_Rect fotograma;

			fotograma.x = ancho * i;
			fotograma.y = 0;
			fotograma.w = ancho;
			fotograma.h = alto;

			fotogramas[ i ] = fotograma;
		}
	}
}

GraficoAvion::~GraficoAvion(void) {

	delete [] fotogramas;
	textura->liberar();
}

Textura* GraficoAvion::getTextura() {
	return textura;
}

SDL_Rect* GraficoAvion::getCurrentClip(int frame) {

	return &fotogramas[ frame / cantidadFotogramas ];
}