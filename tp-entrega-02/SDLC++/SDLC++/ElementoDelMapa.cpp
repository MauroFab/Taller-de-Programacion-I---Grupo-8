#include "ElementoDelMapa.h"


ElementoDelMapa::ElementoDelMapa(int xInicial, int yInicial, SDL_Renderer* gRendererRecibido, Textura* texturaRecibida)
{
	x = xInicial;
	y = yInicial;
	offset = 0;
	gRenderer = gRendererRecibido;
	textura = texturaRecibida;
}


ElementoDelMapa::~ElementoDelMapa(void)
{
}

bool ElementoDelMapa::estaEnPantalla(int yMaxPantalla,int  yMinPantalla){
	bool estaEnPantalla;
	return ((y - textura->getHeight() < yMaxPantalla)
			&& (y + offset > yMinPantalla));
}

void ElementoDelMapa::graficarseSiEstaEnPantalla(int yMaxPantalla,int  yMinPantalla){
	if(estaEnPantalla(yMaxPantalla, yMinPantalla)){
		int tamanioVertical;
		tamanioVertical = (yMaxPantalla - yMinPantalla);
		//Para el render y = 0 es el tope de la pantalla
		//La imagen comienza a verse no en 0, si no cuando solo una parte de la imagen ya entra
		//por eso, recien entramos 
		//textura->render(x, offset - textura->getHeight() ,gRenderer);
		textura->render(x, offset - textura->getHeight() ,gRenderer);
		offset++;
	}
}