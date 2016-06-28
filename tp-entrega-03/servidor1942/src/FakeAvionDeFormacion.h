#pragma once
#include "FakeAvionEnemigo.h"
#include "../../estructura/UtilJuego.h"

#define PI 3.14159265

//la maxima cantidad de angulos a rotar
#define DOUBLE_MAX_CAN_ANG	45.0

#define DELTA_TITA (2.0*PI) / DOUBLE_MAX_CAN_ANG;

#define V_RADIO 20.0

class FakeAvionDeFormacion :
	public FakeAvionEnemigo
{
public:
	
	static const int velocidadAvionMini = 2;
	FakeAvionDeFormacion(int y, int alturaDeLaQueSale);
	void continuarMovimiento(std::list<SuperficieOcupada> superficiesAvionesJugadores);
private:
	//vienen desde la derecha y desde afuera

	static const int xInicial = 500;
	static const int puntosDeVidaMaximoMini = 1;
	int alturaDeLaQueSalgo;
	bool listoParaSalir;
	bool estoyHaciendoElGiro;
	bool yaHiceElGiro;
public:
	//angulo de la rotacion del avion
	double angulo;
};

