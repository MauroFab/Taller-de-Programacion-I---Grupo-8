#ifndef _POWERUP_H_
#define _POWERUP_H_
#define PUNTOS_A		500
#define PUNTOS_B		1000
#define PUNTOS_C		1500

#include "../../servidor1942/src/SuperficieOcupada.h"
#include "../../juego/EstadoPowerUp.h"
/* El diseño de la estructura me gustaba, hubiese quedado mejor. No lo use por dos motivos
   El avion debía conocer al power up (Porque maneja las colisiones) y el power up al avion.
   Y luego tenía que usar un double dispatch, y el double dispatch en c++ no queda muy bien.
   Algunas de las dos cosas me estaban trayendo problemas, y no me funcionaba.
*/

class PowerUp {

public:
	int tipo;
	int puntos;
public:
	PowerUp();
	PowerUp(int p_x,int p_y,int puntos, int tipo);
	virtual ~PowerUp();
	bool esDePuntos();
	bool fueUsado();
	void marcarComoUsado();
	SuperficieOcupada obtenerSuperficieOcupada();
	bool esDeAmetralladora();
	bool esDeMuerte();
	int obtenerPuntosQueOtorga();	
	EstadoPowerUp getEstado();
	void continuarMovimiento();
private:
	//El ancho y alto es el que corresponde a la sprite
	//Como se que es 30 para cualquiera lo hardcodeo por ahora
	static const int ANCHO = 30;
	static const int ALTO = 30;
	SuperficieOcupada superficieOcupada;
	//void killEnemigos(Escenario * escenario);
	//void aumentarBala(AvionJugador * avionJugador);
	bool usado;
};

#endif //_POWERUP_H_
