#include "ElementoDelMapa.h"

ElementoDelMapa::ElementoDelMapa(int xInicial, int yInicial, SDL_Renderer* gRendererRecibido, Textura* texturaRecibida)
{
	x = xInicial;
	y = yInicial;
	gRenderer = gRendererRecibido;
	textura = texturaRecibida;
}

ElementoDelMapa::~ElementoDelMapa(void){
	delete textura;
}

void ElementoDelMapa::reiniciar(){
	
}

bool ElementoDelMapa::estaEnPantalla(int yMaxPantalla,int  yMinPantalla){
	return ((y - textura->getHeight() < yMaxPantalla) && (y + textura->getHeight() > yMinPantalla));
}

void ElementoDelMapa::graficarseSiEstaEnPantalla(int yMaxPantalla,int  yMinPantalla){
	if(estaEnPantalla(yMaxPantalla, yMinPantalla)){
			textura->render(x, yMaxPantalla - y - textura->getHeight() ,gRenderer);
	}
}