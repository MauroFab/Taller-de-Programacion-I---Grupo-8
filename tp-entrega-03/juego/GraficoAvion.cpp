#include "GraficoAvion.h"

GraficoAvion::GraficoAvion(SDL_Renderer* renderer, AvionView * avionView) {	
	this->id = avionView->avionModel->id;
	this->textura = new Textura();
	this->cantidadFotogramas = avionView->spriteXml->getCantidad();
	this->fotogramas = new SDL_Rect[this->cantidadFotogramas];
	char * pathAvion = avionView->spriteXml->getPath();
	if( !textura->cargarDeArchivo( pathAvion, renderer ) ) {
		textura->cargarDeArchivo(FAKE_PATH_AVION_NOT_ENC, renderer);
		cantidadFotogramas = 1;
	} else {
		//1 mas para el grisado
		for(int i=0; i < cantidadFotogramas; i++) {
			SDL_Rect fotograma;
			fotograma.x = avionView->spriteXml->getAncho() * i;
			fotograma.y = 0;
			fotograma.w = avionView->spriteXml->getAncho();
			fotograma.h = avionView->spriteXml->getAlto();
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
