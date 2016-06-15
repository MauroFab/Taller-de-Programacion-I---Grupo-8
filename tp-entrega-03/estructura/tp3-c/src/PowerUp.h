#ifndef _POWERUP_H_
#define _POWERUP_H_
#define TIPO_MUERTE		1
#define TIPO_AMETRALLADORA	2
#define TIPO_PUNTOS		3
#include "Escenario.h"
#include "AvionJugador.h"

//forward declaration. NO usar si no se conoce el uso
class Escenario;
class PowerUp
{
public:
	int tipo;
	int puntaje;
	
public:
	PowerUp();
	PowerUp(int puntaje, int tipo);
	virtual ~PowerUp();
	void operar(AvionJugador * avionJugador,Escenario * escenario);
	void givePuntaje(AvionJugador * avionJugador);
	void killEnemigos(Escenario * escenario);
	void aumentarBala(AvionJugador * avionJugador);
};

#endif //_POWERUP_H_
