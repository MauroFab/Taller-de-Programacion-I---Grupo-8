
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
	if(!estaDestruido()){
		//Si no entre en la pantalla
		//Voy bajando con el mapa
		if(!meMoviAbajoDeLaPantalla){
			superficieOcupada->desplazarEnYObteniendoHitbox(-1);
		}

		//Cuando entro en la pantalla
		if(superficieOcupada->obtenerPosicion().getPosY() < 640 && !meMoviAbajoDeLaPantalla){
			//Me muevo por debajo de ella
			superficieOcupada->moverAPosicionYObteniendoHitbox(-FakeAvionBig::altoAvionBig);
			//Marco que estoy por debajo de ella
			meMoviAbajoDeLaPantalla = true;
		}

		//Si no llegue arriba de todo de la pantalla, pero ya me coloque por debajo, me muevo hacia arriba
		if(meMoviAbajoDeLaPantalla && superficieOcupada->obtenerPosicion().getPosY() < 640 - altoAvionBig){
			superficieOcupada->desplazarEnYObteniendoHitbox(velocidadAvionBig);
		}

		//Si llegue arriba de todo (posicionFinal);
		if(superficieOcupada->obtenerPosicion().getPosY() == 640 - altoAvionBig){
			if(elijoAlAzarSiDisparo() == true){
				disparar();
			}
		}
	}
	moverProyectiles();
}

void FakeAvionBig::disparar(){
	int posXProyectil1 = superficieOcupada->obtenerPosicionCentro().getPosX();
	int posYProyectil1 = superficieOcupada->obtenerPosicion().getPosY();
	int velXProyectil1 = 0;
	int velYProyectil1 = -2;

	int posXProyectil2 = superficieOcupada->obtenerPosicionCentro().getPosX();
	int posYProyectil2 = superficieOcupada->obtenerPosicion().getPosY();
	int velXProyectil2 = -1;
	int velYProyectil2 = -2;

	int posXProyectil3 = superficieOcupada->obtenerPosicionCentro().getPosX();
	int posYProyectil3 = superficieOcupada->obtenerPosicion().getPosY();
	int velXProyectil3 = 1;
	int velYProyectil3 = -2;

	proyectiles.push_back(new ProyectilEnemigo(posXProyectil1,posYProyectil1,velXProyectil1, velYProyectil1));
	proyectiles.push_back(new ProyectilEnemigo(posXProyectil2,posYProyectil2,velXProyectil2, velYProyectil2));
	proyectiles.push_back(new ProyectilEnemigo(posXProyectil3,posYProyectil3,velXProyectil3, velYProyectil3));

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