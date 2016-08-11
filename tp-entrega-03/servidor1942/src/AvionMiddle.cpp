#include "AvionMiddle.h"

 AvionMiddle::AvionMiddle(int x,int y) : 
					AvionEnemigo(x,y,anchoAvionMiddle,altoAvionMiddle,velocidadAvionMiddle){
	meMoviAbajoDeLaPantalla = false;
	id = idAvionMiddle;
	puntosDeVida = puntosDeVidaMaximoMiddle;
	puntosQueOtorgaAlSerImpactado = 100;
	puntosQueOtorgaAlSerDestruido = 500;
}


