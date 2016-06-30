#include "Escenario.h"

Escenario::Escenario():NivelEstado()
{
	this->item_layer = NULL;
	this->bala_layer = NULL;
	this->enemy_layer = NULL;
	this->plane = NULL;
	this->TILE_WIDTH = 32;
	this->TILE_HEIGHT = 32;
}
Escenario::Escenario(char * nombre)
{
	this->item_layer = NULL;
	this->bala_layer = NULL;
	this->enemy_layer = NULL;
	this->plane = NULL;
}

Escenario::~Escenario()
{
}

void Escenario::generateItemsNivel(){
	AvionBig * plane_1 = NULL;
	AvionMini * plane_2= NULL;
	AvionMiddle * plane_3= NULL;
	AvionFormacion * plane_6= NULL;
	PowerUp * power= NULL;

	int x_item_pos = 0;
	int y_item_pos = 0;

	int matrizItem[] = {PLAYER_KEY,BIG_KEY,MINI_KEY,FORMACION_KEY,MIDDLE_KEY,MINI_KEY};
	int widthInTiles = 6;
	add(item_layer);
	add(enemy_layer);
	add(bala_layer);
	int c = 0;
	while (c < widthInTiles) {
		x_item_pos = x_item_pos + this->TILE_WIDTH;
		y_item_pos = y_item_pos + this->TILE_HEIGHT;
		int idElem = matrizItem[c];
		switch (idElem) {
			case PLAYER_KEY: {
				this->plane = new AvionJugador(x_item_pos - this->TILE_WIDTH, y_item_pos - this->TILE_HEIGHT);
				add(plane);
				break;
			}
			case BIG_KEY: {
				plane_1 = new AvionBig(this,x_item_pos - this->TILE_WIDTH, y_item_pos - this->TILE_HEIGHT);
				enemy_layer->add(plane_1);
				break;
			}
			case MINI_KEY: {
				plane_2 = new AvionMini(this,x_item_pos - this->TILE_WIDTH, y_item_pos - this->TILE_HEIGHT);
				enemy_layer->add(plane_2);
				break;
			}
			case MIDDLE_KEY: {
				plane_3 = new AvionMiddle(this,x_item_pos - this->TILE_WIDTH, y_item_pos - this->TILE_HEIGHT);
				enemy_layer->add(plane_3);
				break;
			}
			case FORMACION_KEY: {
				plane_6 = new AvionFormacion(this,x_item_pos - this->TILE_WIDTH, y_item_pos - this->TILE_HEIGHT);
				enemy_layer->add(plane_6);
				break;
			}
			case POWERUP_KEY: {
				power = new PowerUp(PUNTOS_A,TIPO_PUNTOS,x_item_pos - this->TILE_WIDTH, y_item_pos - this->TILE_HEIGHT);
				item_layer->add(power);
				break;
			}
		}
		c++;
	}	
	return;

}
void Escenario::create(){
	this->setung_up_vars();
	this->generateItemsNivel();
}
void Escenario::update(){
	if (false)
	{
		this->add_ramdom_planes();
	}

	NivelEstado::update();
	return;
}

void Escenario::add_ramdom_planes() {
	UtilJuego *util = UtilJuego::getInstance();
	JuegoContainer *cont = JuegoContainer::getInstance();
	int loc1 = 0;
	ObjetoItem * loc2 = NULL;
	//si le da la probabilidad
	if (util->fRandom() < 1.005) {
		loc1 = 0;
		double val_rand = util->fRandom();
		//se generan a lo mucho 10 aviones
		while (loc1 < (val_rand * 10))
		{
			loc2 = new AvionBig(this,(int) (util->fRandom() * cont->get_GAME_WIDTH() - 64 + 32),0);
			enemy_layer->add(loc2);
			++loc1;
		}
	}
	return;
}

void Escenario::setung_up_vars() {
	item_layer = new GrupoItems();
	bala_layer = new GrupoItems();
	enemy_layer = new GrupoItems();
	return;
}
