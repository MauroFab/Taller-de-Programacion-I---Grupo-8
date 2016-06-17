#include "AvionEnemigo.h"


AvionEnemigo::AvionEnemigo(int xInicial, int yInicial, int ancho, int alto, int velocidad){

	superficieOcupada = new SuperficieOcupada(xInicial,yInicial,ancho,alto);
	this->velocidad = velocidad;
	puntosDeVida = vidaMaximaAvionEnemigo;
}

void AvionEnemigo::continuarMovimiento(){
	superficieOcupada->desplazarEnYObteniendoHitbox(-velocidad);
}

void AvionEnemigo::reducirPuntosDeVidaEn(int puntosDeDanio){
	puntosDeVida =- puntosDeDanio;
}

bool AvionEnemigo::estaDestruido(){
	return (puntosDeVida < 0);
}

AvionEnemigo::~AvionEnemigo(){
	//Deberia eliminar la superficie, pero esta explotando si lo hago en las pruebas como estan ahora

	//delete superficieOcupada;
}

SuperficieOcupada AvionEnemigo::obtenerSuperficieOcupada(){
	return (*superficieOcupada);
}