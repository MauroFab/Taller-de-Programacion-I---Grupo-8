#include "FakeAvionMiddle.h"

 FakeAvionMiddle::FakeAvionMiddle(int x,int y) : 
					FakeAvionEnemigo(x,y,anchoAvionMiddle,altoAvionMiddle,velocidadAvionMiddle){
	meMoviAbajoDeLaPantalla = false;
	id = idAvionMiddle;
	puntosDeVida = puntosDeVidaMaximoMiddle;
	puntosQueOtorgaAlSerImpactado = 100;
	puntosQueOtorgaAlSerDestruido = 500;
}
