#include "SuperficieOcupada.h"
#include "../../juego/EstadoAvion.h"

class FakeAvionEnemigo
{
public:
	//Primera version de un avion enemigo, hecha mas para probar colisiones que para armar un avion enemigo.
	//Por ahora se mueve siempre para abajo desde una posicion inicial.

	FakeAvionEnemigo(int xInicial, int yInicial, int ancho, int alto, int velocidad);

	//Si chequeamos las colisiones en todos los movimientos
	//este metodo deberia recibir una lista de cosas con las que puede colisionar
	//Por ahora quiero mirar colisiones solo cuando muevo el avion del jugador
	void continuarMovimiento();
	virtual ~FakeAvionEnemigo();
	
	//En la id devuelve siempre 100. El cliente la recibe asi. 
	//Luego se cambiara minimamente a una constante.
	EstadoAvion* getEstado(); 

	//Dania al avion. A ser usado cuando colisiona contra algo.
	void recibeUnImpacto();

	bool estaDestruido();

	SuperficieOcupada obtenerSuperficieOcupada();
private:

	void reducirPuntosDeVidaEn(int puntosDeDanio);
	SuperficieOcupada* superficieOcupada;
	static const int vidaMaximaFakeAvionEnemigo = 1;
	int puntosDeVida;
	int velocidad;
	int id;
	int frame;
};

