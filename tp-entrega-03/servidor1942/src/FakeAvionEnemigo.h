
#ifndef _FAKEAVIONENEMIGO_H_
#define _FAKEAVIONENEMIGO_H_
#include "SuperficieOcupada.h"
#include "../../juego/EstadoAvion.h"

class FakeAvionEnemigo
{
public:
	//Primera version de un avion enemigo, hecha mas para probar colisiones que para armar un avion enemigo.
	//Por ahora se mueve siempre para abajo desde una posicion inicial.

	FakeAvionEnemigo(int xInicial, int yInicial, int ancho, int alto, int velocidad);

	//Voy a mirar colisiones solo cuando muevo el avion del jugador (y sus proyectiles), 
	//este movimiento solo necesita mover el avionEnemigo
	virtual void continuarMovimiento();
	virtual ~FakeAvionEnemigo();
	
	//En la id devuelve siempre 100. El cliente la recibe asi. 
	//Luego se cambiara minimamente a una constante.
	virtual EstadoAvion* getEstado(); 

	//Dania al avion. A ser usado cuando colisiona contra algo.
	virtual void recibeUnImpacto();

	virtual bool estaDestruido();

	virtual SuperficieOcupada obtenerSuperficieOcupada();

	virtual int getPuntosQueOtorga();
private:
	int puntosQueOtorga;
	void reducirPuntosDeVidaEn(int puntosDeDanio);
	SuperficieOcupada* superficieOcupada;
	static const int vidaMaximaFakeAvionEnemigo = 1;
	int puntosDeVida;
	int velocidad;
	int id;
	int frame;
};

#endif //_FAKEAVIONENEMIGO_H_