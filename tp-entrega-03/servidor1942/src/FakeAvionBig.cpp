
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
	if(!meMoviAbajoDeLaPantalla){
		superficieOcupada->desplazarEnYObteniendoHitbox(-1);
	}else if(superficieOcupada->obtenerPosicion().getPosY() < 640 - altoAvionBig){
		superficieOcupada->desplazarEnYObteniendoHitbox(velocidadAvionBig);
	}
	if(superficieOcupada->obtenerPosicion().getPosY() < 640 && !meMoviAbajoDeLaPantalla){
		//Aparezco desde abajo
		superficieOcupada->moverAPosicionYObteniendoHitbox(-FakeAvionBig::altoAvionBig);
		meMoviAbajoDeLaPantalla = true;
	}
}
