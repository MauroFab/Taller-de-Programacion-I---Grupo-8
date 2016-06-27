
#include "FakeAvionBig.h"

 FakeAvionBig::FakeAvionBig(int x,int y) : 
					FakeAvionEnemigo(x,y,anchoAvionBig,altoAvionBig,velocidadAvionBig){
	meMoviAbajoDeLaPantalla = false;
	id = idAvionBig;
	puntosDeVida = puntosDeVidaMaximoBig;
	puntosQueOtorga = 100;
}

void FakeAvionBig::continuarMovimiento(){
	
	//Voy bajando con el mapa
	superficieOcupada->desplazarEnYObteniendoHitbox(-1);
	if(superficieOcupada->obtenerPosicion().getPosY() < 640){
		//Aparezco desde abajo
		superficieOcupada->moverAPosicionYObteniendoHitbox(FakeAvionBig::altoAvionBig);
		meMoviAbajoDeLaPantalla = true;
	}
	if(meMoviAbajoDeLaPantalla){
		superficieOcupada->desplazarEnYObteniendoHitbox(velocidadAvionBig);
	}
}
