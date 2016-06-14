#include "GraficoMapa.h"

GraficoMapa::GraficoMapa(SDL_Renderer* renderer, FondoView * fondoView, int posicionInicial) {

	char * pathFondo = fondoView->spriteXml->getPath();
	tamanioMaximoMapa = fondoView->altoFondo;
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
}

GraficoMapa::~GraficoMapa(void) {
	std::list<ElementoDelMapa*>::iterator it;
	for(it=elementosDelMapa.begin(); it!=elementosDelMapa.end(); it++)
		 delete (*it);
	textura->liberar();
}

/*--------------------Métodos privados-----------------------*/

void GraficoMapa::configurarElMapaConLaPosicion(int posicion){
	cantidadDePixelesQuePasaron = posicion;
	scrollingOffset = (posicion % altoMapa);
}

void GraficoMapa::graficarElementos() {
	std::list<ElementoDelMapa*>::iterator it;
	for(it=elementosDelMapa.begin(); it!=elementosDelMapa.end(); it++)
	     (*it)->graficarseSiEstaEnPantalla(altoMapa + cantidadDePixelesQuePasaron, cantidadDePixelesQuePasaron, cantidadDePixelesQuePasaron);
}

/*--------------------Métodos públicos-----------------------*/

Textura* GraficoMapa::getTextura() {
	return textura;
}

void GraficoMapa::reiniciar() {
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
	textura->render(0, scrollingOffset, renderer);
	textura->render(0, scrollingOffset - altoMapa, renderer);
	this->graficarElementos();
}

void GraficoMapa::actualizar(EstadoMapa* estadoMapa) {
	this->scrollingOffset = estadoMapa->getScrollingOffSet();
	this->cantidadDePixelesQuePasaron = estadoMapa->getCantidadDePixeles();
	if (estadoMapa->getCodigoReinicio() == 1)
		this->reiniciar();
}