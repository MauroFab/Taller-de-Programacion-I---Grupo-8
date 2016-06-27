
#ifndef _FAKEAVIONENEMIGO_H_
#define _FAKEAVIONENEMIGO_H_
#include "SuperficieOcupada.h"
#include "../../juego/EstadoAvion.h"
#include "PowerUp.h"
class FakeAvionEnemigo
{
public:
	//Primera version de un avion enemigo, hecha mas para probar colisiones que para armar un avion enemigo.
	//Por ahora se mueve siempre para abajo desde una posicion inicial.

	FakeAvionEnemigo(int xInicial, int yInicial, int ancho, int alto, int velocidad);

	//Voy a mirar colisiones solo cuando muevo el avion del jugador (y sus proyectiles), 
	//este movimiento solo necesita mover el avionEnemigo
	//Si no se redefine en las clases que heredan de esta, el avion viene de arriba
	//Y toma una trayectoria al azar
	virtual void continuarMovimiento();
	~FakeAvionEnemigo();
	
	virtual EstadoAvion* getEstado(); 

	virtual void recibeUnImpacto(int idDelJugadorQueLoDanio);

	virtual bool estaDestruido();

	virtual SuperficieOcupada obtenerSuperficieOcupada();

	virtual int getPuntosQueOtorgaAlSerDestruido();
	virtual int getPuntosQueOtorgaAlSerImpactado();

	virtual bool dejaUnPowerUpAlSerDestruido();
	//No llamar si dejaUnPowerUpAlSerDestruido indica false
	virtual PowerUp getPowerUpQueDejaAlSerDestruido();

	static const int idAvionBig = 100;
	static const int idAvionMiddle = 101;
	static const int idAvionMini = 102;

protected:
	static const int altoAvionBig = 200;
	static const int anchoAvionBig = 118;
	static const int altoAvionMiddle = 120;
	static const int anchoAvionMiddle = 68;
	static const int altoAvionMini = 16;
	static const int anchoAvionMini = 19;
	int puntosQueOtorgaAlSerImpactado;
	int puntosQueOtorgaAlSerDestruido;
	void reducirPuntosDeVidaEn(int puntosDeDanio);
	SuperficieOcupada* superficieOcupada;
	static const int vidaMaximaFakeAvionEnemigo = 1;
	int puntosDeVida;
	int velocidad;
	int velocidadX;
	int velocidadY;
	int id;
	int frame;
	int idDelQueMeDestruyo;
};

#endif //_FAKEAVIONENEMIGO_H_