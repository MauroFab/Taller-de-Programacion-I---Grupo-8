#include "FakeAvionEnemigo.h"

FakeAvionEnemigo::FakeAvionEnemigo(int xInicial, int yInicial, int ancho, int alto, int velocidad){

	superficieOcupada = new SuperficieOcupada(xInicial,yInicial,ancho,alto);

	this->velocidad = velocidad;
	puntosDeVida = vidaMaximaFakeAvionEnemigo;
	this->frame = 0;
	id = 100;
	this->puntosQueOtorga = 100;
	velocidadX = rand() % velocidad - (velocidad/2);
	velocidadY = - rand() % velocidad - 1;
	if(rand() % 2 == 1)
		velocidadX = - velocidadX;
}

void FakeAvionEnemigo::continuarMovimiento(){
	//Voy bajando con el mapa
	superficieOcupada->desplazarEnYObteniendoHitbox(-1);
	if(superficieOcupada->obtenerPosicion().getPosY() < 640){
		//Activo todo el movimiento despues de que este en pantalla
		superficieOcupada->desplazarEnYObteniendoHitbox(velocidadY);
		superficieOcupada->desplazarEnXObteniendoHitbox(velocidadX);
	}
}

void FakeAvionEnemigo::reducirPuntosDeVidaEn(int puntosDeDanio){
	puntosDeVida =- puntosDeDanio;
}

bool FakeAvionEnemigo::estaDestruido(){
	return (puntosDeVida <= 0);
}

void FakeAvionEnemigo::recibeUnImpacto(){
	reducirPuntosDeVidaEn(1);
}
FakeAvionEnemigo::~FakeAvionEnemigo(){
	//Deberia eliminar la superficie, pero esta explotando si lo hago en las pruebas como estan ahora

	//delete superficieOcupada;
}

SuperficieOcupada FakeAvionEnemigo::obtenerSuperficieOcupada(){
	return (*superficieOcupada);
}

EstadoAvion* FakeAvionEnemigo::getEstado() {
	//Paso una cantidad de puntos de vida cualquiera hasta que lo programe
	int miPosicionEnY;
	miPosicionEnY = superficieOcupada->obtenerPosicion().getPosY();
	int miPosicionEnX;
	miPosicionEnX = superficieOcupada->obtenerPosicion().getPosX();
	EstadoAvion*  estado =  new EstadoAvion(id, frame, puntosDeVida,miPosicionEnX, miPosicionEnY);
	return estado;
}

int FakeAvionEnemigo::getPuntosQueOtorga(){
	return puntosQueOtorga;
}