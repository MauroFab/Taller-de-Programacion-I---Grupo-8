#pragma once
#include "SuperficieOcupada.h"
#include "../../juego/EstadoProyectil.h"
class ProyectilEnemigo
{
public:
	//Luego haer otro para que apunten solos a una posicion
	ProyectilEnemigo(int x, int y, double velocidadX,double velocidadY);
	void mover();
	ProyectilEnemigo(void);
	~ProyectilEnemigo(void);
	EstadoProyectil* createEstado();
	SuperficieOcupada getSuperficieOcupada();
	void destruir();
	bool estaDestruido();
private:
	static const int anchoBala = 7;
	static const int altoBala = 16;
	SuperficieOcupada superficieQueOcupo;
	bool destruido;
	//Para apuntar bien voy a usar doubles
	//Pero la posicion de la superficie sera siempre un entero
	//La ire redondeando
	double posX;
	double posY;
	double velocidadEnX;
	double velocidadEnY;
};

