#include "Escenario.h"

Escenario::Escenario()
{
	this->canEne = 0;
	this->canPows = 0;
}
Escenario::Escenario(char * nombre)
{
	this->canEne = 0;
	this->canPows = 0;
}

Escenario::~Escenario()
{
}
AvionJugador * Escenario::createAvionJugador(){
	return new AvionJugador();
}
AvionEnemigo * Escenario::createAvionEnemigo(int tipoAvion){
	AvionEnemigo * avion_1 = NULL;
    switch (tipoAvion)
    {
        case TIPO_AVION_BIG:
        {
            avion_1 = new AvionBig();
            break;
        }
    }
    return avion_1;
}

PowerUp * Escenario::createPowerUp(int tipoPowerUp){
	int puntaje = 1500;
	PowerUp * p = new PowerUp(puntaje,tipoPowerUp);
	return p;
}
void Escenario::generateItemsNivel(){
	//creacion de aviones enemigos
	AvionEnemigo * avion_1 = createAvionEnemigo(TIPO_AVION_BIG);
	this->listaEnemigos[canEne] = avion_1;
	this->canEne++;
	//creacion de aviones powerUp
	PowerUp * pow_1 = createPowerUp(TIPO_MUERTE);
	this->listaPowerUp[canPows] = pow_1;
	this->canPows++;
}
void Escenario::create(){
	this->generateItemsNivel();
}
