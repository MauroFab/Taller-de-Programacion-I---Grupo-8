#pragma once

#include "AvionEnemigo.h"

#define PI 3.14159265

class AvionDeFormacion :
	public AvionEnemigo
{
public:
	
	static const int velocidadAvionMini = 2;
	AvionDeFormacion(int y, int alturaDeLaQueSale);
	void continuarMovimiento(std::list<SuperficieOcupada> superficiesAvionesJugadores);
	~AvionDeFormacion();
private:
	//vienen desde la derecha y desde afuera

	static const int xInicial = 500;
	static const int puntosDeVidaMaximoMini = 1;
	static const int xDondeGiro = 200;
	static const int radioCirculo = 50;
	int alturaDeLaQueSalgo;
	bool listoParaSalir;
	bool estoyHaciendoElGiro;
	bool yaHiceElGiro;
	std::list<Posicion*> posicionesDelCirculo;
	bool yaTermineElGiro;
	void cargarPosicionesDelCirculo();

	int convertirFrameQueQuieroAFrameReal(int frameQueQuiero);
	//Y siendo que hay 360 posiciones
	void configurarFrameSabiendoQueQuedan(int cantidadDePosiciones);
public:
	//angulo de la rotacion del avion
	double angulo;
};
