#include "GraficoProyectil.h"

GraficoProyectil::GraficoProyectil(SDL_Renderer* renderer, BalaView * balaView){
	this->id = balaView->balaModel->id;
	this->textura = new Textura();
	this->cantidadFotogramas = balaView->spriteXml->getCantidad();
	this->fotogramas = new SDL_Rect[this->cantidadFotogramas];
	char * pathProyectil = balaView->spriteXml->getPath();
	if( !textura->cargarDeArchivo(pathProyectil , renderer ) ) {
		printf( "Failed to load missil animation texture!\n" );
	} else {
		for(int i=0; i < cantidadFotogramas; i++) {
			SDL_Rect fotograma;
			fotograma.x = balaView->spriteXml->getAncho() * i;
			fotograma.y = 0;
			fotograma.w = balaView->spriteXml->getAncho();
			fotograma.h = balaView->spriteXml->getAlto();
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
