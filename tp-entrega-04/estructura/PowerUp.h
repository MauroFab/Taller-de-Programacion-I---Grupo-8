#ifndef _POWERUP_H_
#define _POWERUP_H_
#define TIPO_MUERTE		1
#define TIPO_AMETRALLADORA	2
#define TIPO_PUNTOS		3
#define PUNTOS_A		500
#define PUNTOS_B		1000
#define PUNTOS_C		1500
#include "Escenario.h"
#include "ObjetoItem.h"
#include "AvionJugador.h"

//forward declaration. NO usar si no se conoce el uso
class Escenario;
class PowerUp : public ObjetoItem
{
public:
	int tipo;
	int puntos;
public:
	PowerUp();
	PowerUp(int puntos, int tipo);
	PowerUp(int p_x,int p_y,int puntos, int tipo);
	virtual ~PowerUp();
	void operar(AvionJugador * avionJugador,Escenario * escenario);
	void givePuntos(AvionJugador * avionJugador);
	void killEnemigos(Escenario * escenario);
	void aumentarBala(AvionJugador * avionJugador);
};

#endif //_POWERUP_H_
