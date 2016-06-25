#include "GraficadorPowerUp.h"


GraficadorPowerUp::GraficadorPowerUp(SDL_Renderer* renderer){
	Textura textura;
	textura.cargarDeArchivo("../cliente1942/power_up_arma.bmp",renderer);
	mapaTexturasPowerUps[TIPO_PUNTOS] = textura;
	this->renderer = renderer;
}


void GraficadorPowerUp::graficarPowerUps(std::list<EstadoPowerUp> &estadoPowerUps){
	std::list<EstadoPowerUp>::iterator it;
	for(it = estadoPowerUps.begin(); it != estadoPowerUps.end(); it++){
		Textura textura;
		EstadoPowerUp estado = (*it);
		textura = mapaTexturasPowerUps[estado.getTipo()];
		//Me olvide de pasar la x y la y en el estado
		int x = 50,y = 200;
		SDL_Rect fotograma;
		fotograma.x = fotograma.y = 0;
		fotograma.w = textura.getWidth();
		fotograma.h = textura.getHeight();
		textura.render(x,y,renderer,&fotograma);
	}
}

GraficadorPowerUp::~GraficadorPowerUp(void)
{
}
