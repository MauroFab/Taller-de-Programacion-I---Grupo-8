#include "ElementoDelMapa.h"

ElementoDelMapa::ElementoDelMapa(int xInicial, int yInicial, SDL_Renderer* gRendererRecibido, Textura* texturaRecibida)
{
	x = xInicial;
	y = yInicial;
	offset = 0;
	gRenderer = gRendererRecibido;
	textura = texturaRecibida;
	meHanGraficadoAlgunaVez = false;
}

ElementoDelMapa::~ElementoDelMapa(void){
	delete textura;
}

void ElementoDelMapa::reiniciar(){
	meHanGraficadoAlgunaVez = false;
}

bool ElementoDelMapa::estaEnPantalla(int yMaxPantalla,int  yMinPantalla){
	return ((y - textura->getHeight() < yMaxPantalla) && (y + textura->getHeight() > yMinPantalla));
}

bool ElementoDelMapa::apareceDesdeAfuera(int yMaxPantalla, int yMinPantalla){
	//calcula el alto de la pantalla
	int tamanioVertical = (yMaxPantalla - yMinPantalla);
	return (y > tamanioVertical);
}

void ElementoDelMapa::graficarseSiEstaEnPantalla(int yMaxPantalla,int  yMinPantalla, int cantidadDePixeles){
	if(!meHanGraficadoAlgunaVez){
		aparezcoDesdeAfuera = (y > yMaxPantalla);
		posicionInicialPantalla = yMinPantalla;
	}
	if(estaEnPantalla(yMaxPantalla, yMinPantalla)){
		if(aparezcoDesdeAfuera){
			//Para el render y = 0 es el tope de la pantalla
			//La imagen comienza a verse no en 0, si no cuando solo una parte de la imagen ya entra, y desde arriba
			textura->render(x, cantidadDePixeles - textura->getHeight() ,gRenderer);
		}else{
			int tamanioVertical;
			tamanioVertical = (yMaxPantalla - yMinPantalla);
			int posicionInicial = (tamanioVertical - y + posicionInicialPantalla);
			textura->render(x, cantidadDePixeles - textura->getHeight() + posicionInicial ,gRenderer);
		}
	}
	meHanGraficadoAlgunaVez = true;
}