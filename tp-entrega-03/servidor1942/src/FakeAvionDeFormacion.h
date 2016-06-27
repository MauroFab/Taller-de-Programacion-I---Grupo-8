#pragma once
#include "FakeAvionEnemigo.h"

#define PI 3.14159265

//la maxima cantidad de angulos a rotar
#define DOUBLE_MAX_CAN_ANG	16.0

#define DELTA_TITA (2.0*PI) / DOUBLE_MAX_CAN_ANG;

class FakeAvionDeFormacion :
	public FakeAvionEnemigo
{
public:
	
	static const int velocidadAvionMini = 2;
	FakeAvionDeFormacion(int y, int alturaDeLaQueSale);
	void continuarMovimiento();
private:
	//vienen desde la derecha y desde afuera

	static const int xInicial = 500;
	static const int puntosDeVidaMaximoMini = 1;
	int alturaDeLaQueSalgo;
	bool listoParaSalir;
public:
	//angulo de la rotacion del avion
	double angulo;
};

