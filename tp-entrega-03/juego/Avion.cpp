#include "Avion.h"

Avion::Avion(int ventanaAncho, int ventanaAlto, AvionView* avionView, BalaView* balaView) {

	this->ventanaAncho = ventanaAncho;
	this->ventanaAlto = ventanaAlto;
	this->altoAvion = avionView->spriteXml->getAlto();
	this->anchoAvion = avionView->spriteXml->getAncho();
	this->velocidad = avionView->avionModel->velAvion;
    velocidadX = 0;
    velocidadY = 0;
	cantDeFotogramas = avionView->spriteXml->getCantidad();
	frame = 0;
	rollFlag = false;
	id = avionView->avionModel->id;
	this->balaView = balaView;
}

Avion::~Avion() {
	std::list<Proyectil*>::iterator it;
	for (it = proyectiles.begin(); it != proyectiles.end(); it++) {
		delete (*it);
	}
}

void Avion::setPosicion(Posicion pos) {

	this->posicionX = pos.getPosX();
	this->posicionY = pos.getPosY();
}

void Avion::continuarMovimientoDelAvion(){
	if(!rollFlag){
		// Mueve el avion hacia la derecha o a la izquierda
		posicionX += velocidadX;

		// Para que no se salga de la pantalla en X
		if( ( posicionX < 0 ) || ( posicionX + anchoAvion > this->ventanaAncho ) ){
			posicionX -= velocidadX;
		}

		// Mueve el avion hacia arriba o hacia abajo
		posicionY += velocidadY;

		// Para que no se salga de la pantalla en Y
		if( ( posicionY < 0 ) || ( posicionY + altoAvion > this->ventanaAlto ) ){
			posicionY -= velocidadY;
	   }
	}else{
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

	EstadoAvion*  estado =  new EstadoAvion(id, frame, posicionX, posicionY); 
	std::list<EstadoProyectil*> lista;
	std::list<Proyectil*>::iterator it;
	for (it = proyectiles.begin(); it != proyectiles.end(); it++) {
		estado->agregarEstadoProyectil((*it)->createEstado());
	}
	return estado;
}

std::list<EstadoProyectil*> Avion::getEstadoProyectiles() {
	std::list<EstadoProyectil*> lista;
	std::list<Proyectil*>::iterator it;
	for (it = proyectiles.begin(); it != proyectiles.end(); it++) {
		lista.push_back((*it)->createEstado());
	}
	return lista;
}

void Avion::realizarAccionEnBaseA(Evento* evento){
	switch(evento->getNumeroDeEvento()){
    case apretadaLaTeclaDeMovimientoHaciaIzquierda  :
		this->darVelocidadHaciaLaIzquierda();
       break;
    case soltadaLaTeclaDeMovimientoHaciaIzquierda   :
		this->quitarVelocidadHaciaLaIzquierda();
       break; 
	case apretadaLaTeclaDeMovimientoHaciaDerecha   :
		this->darVelocidadHaciaLaDerecha();
       break; 
	case soltadaLaTeclaDeMovimientoHaciaDerecha    :
		this->quitarVelocidadHaciaLaDerecha();
       break; 
	case apretadaLaTeclaDeMovimientoHaciaArriba   :
		this->darVelocidadHaciaArriba();
       break; 
	case soltadaLaTeclaDeMovimientoHaciaArriba  :
		this->quitarVelocidadHaciaArriba();
       break; 
	case apretadaLaTeclaDeMovimientoHaciaAbajo  :
		this->darVelocidadHaciaAbajo();
       break; 
	case soltadaLaTeclaDeMovimientoHaciaAbajo  :
		this->quitarVelocidadHaciaAbajo();
       break; 
	case apretadaLaTeclaDeDisparo :
		this->disparar();
       break; 
	case apretadaLaTeclaDeRoll  :
		this->hacerUnRoll();
       break; 
	}
}

//BUG-000 aca hay un error pues plantea que se suma la misma velocidad en ambas coordenadas
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
		Proyectil* proyectil = new Proyectil(this->balaView);
		//El centro del proyectil esta en el pixel 5
		proyectil->setCoordenasDeComienzo(posicionX + (anchoAvion / 2) - 5, posicionY - (altoAvion/24));
		proyectiles.push_back(proyectil);
	}
}

void Avion::hacerUnRoll(){
	rollFlag = true;
}