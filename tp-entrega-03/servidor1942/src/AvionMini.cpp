#include "AvionMini.h"

 AvionMini::AvionMini(int x,int y) : 
					AvionEnemigo(x,y,anchoAvionMini,altoAvionMini,3){
	meMoviAbajoDeLaPantalla = false;
	id = idAvionMini;
	puntosDeVida = puntosDeVidaMaximoMiddle;
	puntosQueOtorgaAlSerImpactado = 0;
	puntosQueOtorgaAlSerDestruido = 50;
}
