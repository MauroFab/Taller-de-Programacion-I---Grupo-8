#pragma once

#include <cmath>
#include "../../common/Posicion.h"

class SuperficieOcupada
{
public:
	//Por ahora toda superficie ocupada es un rectangulo
	//Sin embargo, nada impide a un objeto tener varios rectangulos para representar la superficie que ocupa. 
	//Se podría pulir con un patrón composite para armar directamente una superficie que incluya varios rectangulos.


	SuperficieOcupada();
	//Siguiendo con el sistema coordenado usado por el modelo y los graficadores
	// x, y son la esquina inferior izquierda de la superficie
	SuperficieOcupada(int x, int y, int ancho, int alto);

	//La hitbox para chequear colisiones con otras cosas, es una superficie
	//Que une la superficie inicial y la final
	//Se suelen hacer rectangulares, por eso permito unicamente mover de a una coordenada a la vez
	//Las movimientos bidimensionales se descomponen en movimientos unidimensionales
	SuperficieOcupada moverAPosicionXObteniendoHitbox(int x);
	SuperficieOcupada moverAPosicionYObteniendoHitbox(int y);

	SuperficieOcupada desplazarEnXObteniendoHitbox(int distanciaAMoverEnX);
	SuperficieOcupada desplazarEnYObteniendoHitbox(int distanciaAMoverEnY);

	void moverAPosicion(Posicion posicion);
	void moverAX(int x);
	void moverAY(int y);

	Posicion obtenerPosicion();

	bool meSolapoCon(SuperficieOcupada otraSuperficieOcupada);

public:
	
	int x;
	int y;
private:
	int ancho;
	int alto;
	int valorMinimoEntre(int a, int b);
	int valorMaximoEntre(int a, int b);
	bool compartoUnaRegionEnXCon(SuperficieOcupada otraSuperficieOcupada);
	bool compartoUnaRegionEnYCon(SuperficieOcupada otraSuperficieOcupada);
};

