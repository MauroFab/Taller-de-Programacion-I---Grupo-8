#ifndef _ESCENARIO_H_
#define _ESCENARIO_H_
#include <string.h>
#include "AvionJugador.h"
#include "AvionEnemigo.h"
#include "AvionBig.h"
#include "AvionFormacion.h"
#include "AvionMiddle.h"
#include "AvionMini.h"
#include "PowerUp.h"

#include <iostream>
using namespace std;

//forward declaration. NO usar si no se conoce el uso
class PowerUp;

class Escenario
{
public:
	int estado;
	char nombre[30];
	AvionEnemigo * listaEnemigos[100];
	int canEne;
	PowerUp * listaPowerUp[100];
	int canPows;
public:
	Escenario();
	Escenario(char * nombre);
	virtual ~Escenario();
	AvionJugador* createAvionJugador();
	AvionEnemigo* createAvionEnemigo(int tipoAvion);
	PowerUp* createPowerUp(int tipoPowerUp);
	void create();
	void generateItemsNivel();
};

#endif //_ESCENARIO_H_
