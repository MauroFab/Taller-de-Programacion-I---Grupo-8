#include "FakeAvionEnemigo.h"

FakeAvionEnemigo::FakeAvionEnemigo(int xInicial, int yInicial, int ancho, int alto, int velocidad){

	superficieOcupada = new SuperficieOcupada(xInicial,yInicial,ancho,alto);
	this->velocidad = velocidad;
	puntosDeVida = vidaMaximaFakeAvionEnemigo;
	this->frame = 0;
	id = 100;
}

void FakeAvionEnemigo::continuarMovimiento(){
	superficieOcupada->desplazarEnYObteniendoHitbox(-velocidad);
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