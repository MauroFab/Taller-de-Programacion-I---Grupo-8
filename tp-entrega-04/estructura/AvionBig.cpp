#include "AvionBig.h"

AvionBig::AvionBig():AvionEnemigo()
{	
	cout <<"AvionBig()" <<endl;
	pEscenario = NULL;
	puntos_derribo = 0;
	puntos_solo = 0;	
}
AvionBig::AvionBig(Escenario * escenario):AvionEnemigo()
{	
	cout <<"AvionBig()" <<endl;
	pEscenario = escenario;
	puntos_derribo = 0;
	puntos_solo = 0;	
}
AvionBig::AvionBig(int p_x,int p_y):AvionEnemigo(p_x,p_y){
	cout <<"AvionBig(p_x,p_y)" <<endl;
	pEscenario = NULL;
	puntos_derribo = 0;
	puntos_solo = 0;	
}
AvionBig::AvionBig(Escenario * escenario,int p_x,int p_y):AvionEnemigo(p_x,p_y){
	cout <<"AvionBig(p_x,p_y)" <<endl;
	pEscenario = escenario;
	puntos_derribo = 0;
	puntos_solo = 0;	
}
AvionBig::~AvionBig()
{
}
PowerUp * AvionBig::createPowerUp(){
	return new PowerUp();
}

BalaEnemigo * AvionBig::disparar(){
	return dispararMultiple();
}

BalaEnemigo * AvionBig::dispararMultiple(){
	return NULL;
}
void AvionBig::update() {
	UtilJuego *util = UtilJuego::getInstance();
	BalaEnemigo * loc1 = NULL;
	if (!onScreen()) {
		return;
	}
	if (bUnaVez && util->fRandom() < 0.500) {
		loc1 = new BalaEnemigo();
		loc1->x = x;//(int) (this->x + this->width * 0.45);
		loc1->y = y;//(int) (this->y + this->height * 0.5);
		loc1->velocity.y = 5;//(int) (this.velocity.y * 0.1);
		pEscenario->bala_layer->add(loc1);
		bUnaVez = false;
	}
	AvionEnemigo::update();
	cout <<",x="<<x<<",y="<<y<<endl;
	return;
}