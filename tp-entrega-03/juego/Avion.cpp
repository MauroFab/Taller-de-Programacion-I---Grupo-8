#include "Avion.h"

bool Avion::instanceFlag = false;
Avion* Avion::instance = NULL;

Avion* Avion::getInstance() {

	if(!instanceFlag){
        instance = new Avion();
        instanceFlag = true;
    }
    return instance;
}

void Avion::inicializar(SDL_Renderer* rendererRecibido,int ventanaAncho,int ventanaAlto,AvionView * avionView) {

	this->ventanaAncho = ventanaAncho;
	this->ventanaAlto = ventanaAlto;
	this->avionView = avionView;

    velocidadX = 0;
    velocidadY = 0;

	frame = 0;
	rollFlag = false;

	renderer = rendererRecibido;

	if (fotogramas != NULL) {
		delete [] fotogramas;
	}
	fotogramas = new SDL_Rect[avionView->spriteXml->getCantidad()];

	if( !texturaAvion->cargarDeArchivo( avionView->spriteXml->getPath(), renderer ) )
	{
		texturaAvion->cargarDeArchivo("avionNoEncontrado.bmp", renderer);
	}
		for(int i=0; i < avionView->spriteXml->getCantidad(); i++){

			SDL_Rect fotograma;

			fotograma.x = avionView->spriteXml->getAncho()*i;//anchoFotograma * i;
			fotograma.y = 0;
			fotograma.w = avionView->spriteXml->getAncho();//anchoFotograma;
			fotograma.h = avionView->spriteXml->getAlto();//altoFotograma;

			fotogramas[ i ] = fotograma;
	}
	velocidad = this->avionView->avionModel->velAvion;
}

Avion::Avion() {

	fotogramas = NULL;
	texturaAvion = new Textura();
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

void Avion::hacerUnRoll(){
	rollFlag = true;
}

void Avion::continuarMovimientoDelAvion(){
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
	}else{
		int cantDeFotogramas = this->avionView->spriteXml->getCantidad();
		if ((frame / cantDeFotogramas) >= cantDeFotogramas - 1){
			frame = 0;
			rollFlag = false;
		}
			frame++;
	}
}

void Avion::continuarMovimientoDeLosProyectiles(){
	std::list<Proyectil*>::iterator it;
	for (it = proyectiles.begin(); it != proyectiles.end(); it++) {
		if ((*it)->estaEnPantalla()) {
			(*it)->mover();
		}
	}
}

void Avion::eliminarLosProyectilesQueSalieronDeLaPantalla(){
		Proyectil* ultimoProyectil = proyectiles.front();
		if(!ultimoProyectil->estaEnPantalla() ){
			proyectiles.pop_front();
			delete ultimoProyectil;
		}
}
void Avion::mover() {
	continuarMovimientoDelAvion();
	//Avanzo los proyectiles
	continuarMovimientoDeLosProyectiles();
	//Si hay proyectiles
	if(!proyectiles.empty())
		eliminarLosProyectilesQueSalieronDeLaPantalla();

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

void Avion::darVelocidadHaciaArriba(){
	velocidadY -= velocidad;
}
void Avion::quitarVelocidadHaciaArriba(){
	velocidadY += velocidad;
}
		
void Avion::darVelocidadHaciaAbajo(){
	velocidadY += velocidad;
}
void Avion::quitarVelocidadHaciaAbajo(){
	velocidadY -= velocidad;
}

void Avion::darVelocidadHaciaLaDerecha(){
	velocidadX += velocidad;
}
void Avion::quitarVelocidadHaciaLaDerecha(){
	velocidadX -= velocidad;
}

void Avion::darVelocidadHaciaLaIzquierda(){
	velocidadX -= velocidad;
}
void Avion::quitarVelocidadHaciaLaIzquierda(){
	velocidadX += velocidad;
}

void Avion::disparar(){
	if(!rollFlag){
		Proyectil* proyectil = new Proyectil(renderer);
		//El centro del proyectil esta en el pixel 5
		proyectil->setCoordenasDeComienzo(posicionX + (this->avionView->spriteXml->getAncho() / 2) - 5, posicionY - (this->avionView->spriteXml->getAlto()/24));
		proyectiles.push_back(proyectil);
	}
}