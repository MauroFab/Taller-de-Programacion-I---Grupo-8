#include "AvionMiddle.h"

AvionMiddle::AvionMiddle():AvionEnemigo()
{
	pEscenario = NULL;
	puntos_derribo = 0;
	puntos_solo = 0;
}
AvionMiddle::AvionMiddle(Escenario * escenario):AvionEnemigo()
{
	pEscenario = escenario;
	puntos_derribo = 0;
	puntos_solo = 0;
}

AvionMiddle::AvionMiddle(int p_x,int p_y):AvionEnemigo(p_x,p_y){
	cout <<"AvionMiddle(p_x,p_y)" <<endl;
	pEscenario = NULL;
	puntos_derribo = 0;
	puntos_solo = 0;
}
AvionMiddle::AvionMiddle(Escenario * escenario,int p_x,int p_y):AvionEnemigo(p_x,p_y){
	cout <<"AvionMiddle(p_x,p_y)" <<endl;
	pEscenario = escenario;
	puntos_derribo = 0;
	puntos_solo = 0;
}

AvionMiddle::~AvionMiddle()
{
}
