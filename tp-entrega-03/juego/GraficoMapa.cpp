#include "GraficoMapa.h"

GraficoMapa::GraficoMapa(SDL_Renderer* renderer, FondoView * fondoView, int posicionInicial) {

	char * pathFondo = fondoView->spriteXml->getPath();
	textura = new Textura();
	this->renderer = renderer;

	if( !textura->cargarDeArchivo(pathFondo, this->renderer) ){
		textura->cargarDeArchivo( FONDO_DEFAULT,renderer );
	}
	anchoMapa = textura->getWidth();
	altoMapa = textura->getHeight();	
	this->configurarElMapaConLaPosicion(posicionInicial);

	if (!elementosDelMapa.empty()) {
		std::list<ElementoDelMapa*>::iterator it;
		for(it=elementosDelMapa.begin(); it!=elementosDelMapa.end(); it++)
			delete (*it);
		elementosDelMapa.clear();
	}
	this->scrollingOffset = 0;
	this->hayQueReiniciar = false;
}

GraficoMapa::~GraficoMapa(void) {
	std::list<ElementoDelMapa*>::iterator it;
	for(it=elementosDelMapa.begin(); it!=elementosDelMapa.end(); it++)
		 delete (*it);
	textura->liberar();
}

/*--------------------M�todos privados-----------------------*/

void GraficoMapa::configurarElMapaConLaPosicion(int posicion){
	cantidadDePixelesQuePasaron = posicion;
	scrollingOffset = (posicion % altoMapa);
}

void GraficoMapa::graficarElementos() {
	std::list<ElementoDelMapa*>::iterator it;
	for(it=elementosDelMapa.begin(); it!=elementosDelMapa.end(); it++)
	     (*it)->graficarseSiEstaEnPantalla(altoMapa + cantidadDePixelesQuePasaron, cantidadDePixelesQuePasaron);
}

/*--------------------M�todos p�blicos-----------------------*/

Textura* GraficoMapa::getTextura() {
	return textura;
}

void GraficoMapa::reiniciar() {
	this->scrollingOffset = 0;
	std::list<ElementoDelMapa*>::iterator it;
	for(it=elementosDelMapa.begin(); it!=elementosDelMapa.end(); it++)
		(*it)->reiniciar();
}

void GraficoMapa::crearElementos(ElementoView* *listaElementosView, int canElemV) {
	//se crean los elementos a partir de los datos originales
	for(int e = 0; e < canElemV; e++){
		ElementoView * elementoView = listaElementosView[e];
		Textura * texturaElemento = new Textura();
		char * path = elementoView->spriteXml->getPath();
		if(!texturaElemento->cargarDeArchivo(path,renderer)){
			texturaElemento->cargarDeArchivo("error.bmp",renderer);
		};
		ElementoDelMapa* elementoDelMapa = new ElementoDelMapa(elementoView->posicion.x,elementoView->posicion.y, renderer,texturaElemento);
		elementosDelMapa.push_back(elementoDelMapa);
	}
}

void GraficoMapa::graficarFondoYElementos() {

	//Despu�s de la ultima posicion de la imagen de fondo sigue la primera
	if(this->scrollingOffset >= altoMapa)
		this->scrollingOffset = 0;

	textura->render(0, scrollingOffset, renderer);
	textura->render(0, scrollingOffset - altoMapa, renderer);
	this->graficarElementos();
}

void GraficoMapa::actualizar(EstadoMapa* estadoMapa) {
	this->scrollingOffset++;
	this->cantidadDePixelesQuePasaron = estadoMapa->getCantidadDePixeles();
}