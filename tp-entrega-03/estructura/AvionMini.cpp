#include "AvionMini.h"

AvionMini::AvionMini():AvionEnemigo()
{
	pEscenario = NULL;
}
AvionMini::AvionMini(Escenario * escenario):AvionEnemigo()
{
	cout <<"AvionMini()" <<endl;
	pEscenario = escenario;
}
AvionMini::AvionMini(int p_x,int p_y):AvionEnemigo(p_x,p_y){
	cout <<"AvionMini(p_x,p_y)" <<endl;
	pEscenario = NULL;
}
AvionMini::AvionMini(Escenario * escenario,int p_x,int p_y):AvionEnemigo(p_x,p_y){
	cout <<"AvionMini(p_x,p_y)" <<endl;
	pEscenario = escenario;
}
AvionMini::~AvionMini()
{
}
void AvionMini::update() {
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
