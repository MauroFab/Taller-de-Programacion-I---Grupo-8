#pragma once

#include <cmath>
class SuperficieOcupada
{
public:
	//Por ahora toda superficie ocupada es un rectangulo
	//Sin embargo, nada impide a un objeto tener varios rectangulos para representar la superficie que ocupa. 
	//Se podría pulir con un patrón composite para armar directamente una superficie que incluya varios rectangulos.

	//Siguiendo con el sistema coordenado usado por el modelo y los graficadores
	// x, y son la esquina inferior izquierda de la superficie
	SuperficieOcupada(int x, int y, int ancho, int alto);

	//La hitbox para chequear colisiones con otras cosas, es una superficie
	//Que une la superficie inicial y la final
	//Se suelen hacer rectangulares, por eso permito unicamente mover de a una coordenada a la vez
	//Las movimientos bidimensionales se descomponen en movimientos unidimensionales
	SuperficieOcupada moverAPosicionXObteniendoHitbox(int x);
	SuperficieOcupada moverAPosicionYObteniendoHitbox(int y);
	bool meSolapoCon(SuperficieOcupada otraSuperficieOcupada);

private:
	int x;
	int y;
	int ancho;
	int alto;
	int valorMinimoEntre(int a, int b);
	int valorMaximoEntre(int a, int b);
	bool compartoUnaRegionEnXCon(SuperficieOcupada otraSuperficieOcupada);
	bool compartoUnaRegionEnYCon(SuperficieOcupada otraSuperficieOcupada);
};

