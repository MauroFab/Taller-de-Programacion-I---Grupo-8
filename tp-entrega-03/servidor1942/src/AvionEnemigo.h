#include "SuperficieOcupada.h"

class AvionEnemigo
{
public:
	//Primera version de un avion enemigo, hecha mas para probar colisiones que para armar un avion enemigo.
	//Por ahora se mueve siempre para abajo desde una posicion inicial.

	AvionEnemigo(int xInicial, int yInicial, int ancho, int alto, int velocidad);

	//Si chequeamos las colisiones en todos los movimientos
	//este metodo deberia recibir una lista de cosas con las que puede colisionar
	//Por ahora quiero mirar colisiones solo cuando muevo el avion del jugador
	void continuarMovimiento();

	~AvionEnemigo(void);
	void reducirPuntosDeVidaEn(int puntosDeDanio);
	bool estaDestruido();

	SuperficieOcupada obtenerSuperficieOcupada();
private:
	SuperficieOcupada* superficieOcupada;
	static const int vidaMaximaAvionEnemigo = 1;
	int puntosDeVida;
	int velocidad;
};

