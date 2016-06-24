#ifndef _ESCENARIO_H_
#define _ESCENARIO_H_
#include <string.h>
#include "NivelEstado.h"
#include "AvionJugador.h"
//#include "AvionEnemigo.h"
#include "AvionBig.h"
#include "AvionFormacion.h"
#include "AvionMiddle.h"
#include "AvionMini.h"
#include "PowerUp.h"
#include "UtilJuego.h"
#include "JuegoContainer.h"

#define BIG_KEY  1
#define FORMACION_KEY  2
#define MIDDLE_KEY  3
#define MINI_KEY  4
#define POWERUP_KEY  6
#define PLAYER_KEY  7

#include <iostream>
using namespace std;

//forward declaration. NO usar si no se conoce el uso
class PowerUp;
class AvionEnemigo;

class Escenario : public NivelEstado
{
public:
	int estado;
	char nombre[30];
	GrupoItems * item_layer;
	GrupoItems * bala_layer;
	GrupoItems * enemy_layer;
	AvionJugador * plane;
	
public:
	int TILE_WIDTH;
	int TILE_HEIGHT;
public:
	Escenario();
	Escenario(char * nombre);
	virtual ~Escenario();
	virtual void create();
	virtual void update();
	void generateItemsNivel();
	void add_ramdom_planes();
	void setung_up_vars();
};

#endif //_ESCENARIO_H_
