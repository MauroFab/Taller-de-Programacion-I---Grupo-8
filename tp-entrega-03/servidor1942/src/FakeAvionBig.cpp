
#include "FakeAvionBig.h"

 FakeAvionBig::FakeAvionBig(int x,int y) : 
					FakeAvionEnemigo(x,y,anchoAvionBig,altoAvionBig,velocidadAvionBig){
	meMoviAbajoDeLaPantalla = false;
	id = idAvionBig;
	puntosDeVida = puntosDeVidaMaximoBig;
	puntosQueOtorgaAlSerImpactado = 100;
	puntosQueOtorgaAlSerDestruido = 1000;
}

void FakeAvionBig::continuarMovimiento(std::list<SuperficieOcupada> superficiesAvionesJugadores){
	
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


bool FakeAvionBig::dejaUnPowerUpAlSerDestruido(){
	return true;
}

PowerUp FakeAvionBig::getPowerUpQueDejaAlSerDestruido(){
	int x, y;
	x = superficieOcupada->obtenerPosicion().getPosX() + anchoAvionBig/2;
	y = superficieOcupada->obtenerPosicion().getPosY() + altoAvionBig/2;
	return PowerUp(x,y,1500,TIPO_PUNTOS);
}