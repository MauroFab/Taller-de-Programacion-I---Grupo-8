#include "GraficadorPowerUp.h"


GraficadorPowerUp::GraficadorPowerUp(SDL_Renderer* renderer){
	Textura* textura = new Textura();
	textura->cargarDeArchivo("../cliente1942/power_up_puntos.bmp",renderer);
	mapaTexturasPowerUps[TIPO_PUNTOS] = textura;
	this->renderer = renderer;
}


void GraficadorPowerUp::graficarPowerUps(std::list<EstadoPowerUp> &estadoPowerUps){
	std::list<EstadoPowerUp>::iterator it;
	for(it = estadoPowerUps.begin(); it != estadoPowerUps.end(); it++){
		EstadoPowerUp estado = (*it);
		if(!estado.fueUsadoElPowerUp()){
			Textura* textura;
			textura = mapaTexturasPowerUps[estado.getTipo()];
			int xSDL, ySDL;
			xSDL = estado.getX();
			ySDL = ALTO_PANTALLA - estado.getY() - textura->getHeight();
			SDL_Rect fotograma;
			fotograma.x = 0;
			fotograma.y = 0;
			fotograma.w = textura->getWidth();
			fotograma.h = textura->getHeight();
			textura->render(xSDL,ySDL,renderer,&fotograma);
		}
	}
}

GraficadorPowerUp::~GraficadorPowerUp(void){

	
}
