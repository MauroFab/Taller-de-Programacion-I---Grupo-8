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
		int xSDL, ySDL;
		xSDL = estado.getX();
		ySDL = ALTO_PANTALLA - estado.getY();
		SDL_Rect fotograma;
		fotograma.x = 0;
		fotograma.y = 0;
		fotograma.w = textura.getWidth();
		fotograma.h = textura.getHeight();
		textura.render(xSDL,ySDL,renderer,&fotograma);
	}
}

GraficadorPowerUp::~GraficadorPowerUp(void)
{
}
