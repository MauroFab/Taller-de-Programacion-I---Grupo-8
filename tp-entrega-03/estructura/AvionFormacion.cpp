#include "AvionFormacion.h"

AvionFormacion::AvionFormacion():AvionEnemigo()
{
	pEscenario = NULL;
	puntos_formacion = 0;
}
AvionFormacion::AvionFormacion(Escenario * escenario):AvionEnemigo()
{
	pEscenario = escenario;
	puntos_formacion = 0;
}
AvionFormacion::AvionFormacion(int p_x,int p_y):AvionEnemigo(p_x,p_y){
	cout <<"AvionFormacion(p_x,p_y)" <<endl;
	pEscenario = NULL;
	puntos_formacion = 0;
}
AvionFormacion::AvionFormacion(Escenario * escenario,int p_x,int p_y):AvionEnemigo(p_x,p_y){
	cout <<"AvionFormacion(p_x,p_y)" <<endl;
	pEscenario = escenario;
	puntos_formacion = 0;
}

AvionFormacion::~AvionFormacion()
{
}
