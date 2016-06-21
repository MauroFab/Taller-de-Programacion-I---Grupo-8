#include "FakeAvionEnemigo.h"

FakeAvionEnemigo::FakeAvionEnemigo(int xInicial, int yInicial, int ancho, int alto, int velocidad){

	superficieOcupada = new SuperficieOcupada(xInicial,yInicial,ancho,alto);
	this->velocidad = velocidad;
	puntosDeVida = vidaMaximaAvionEnemigo;
}

void FakeAvionEnemigo::continuarMovimiento(){
	superficieOcupada->desplazarEnYObteniendoHitbox(-velocidad);
}

void FakeAvionEnemigo::reducirPuntosDeVidaEn(int puntosDeDanio){
	puntosDeVida =- puntosDeDanio;
}

bool FakeAvionEnemigo::estaDestruido(){
	return (puntosDeVida < 0);
}

FakeAvionEnemigo::~FakeAvionEnemigo(){
	//Deberia eliminar la superficie, pero esta explotando si lo hago en las pruebas como estan ahora

	//delete superficieOcupada;
}

SuperficieOcupada FakeAvionEnemigo::obtenerSuperficieOcupada(){
	return (*superficieOcupada);
}