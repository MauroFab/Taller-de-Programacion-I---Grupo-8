
#include "FakeAvionDeFormacion.h"

 FakeAvionDeFormacion::FakeAvionDeFormacion(int y, int alturaDeLaQueSalgo) : 
					FakeAvionEnemigo(xInicial,y,anchoAvionMini,altoAvionMini,velocidadAvionMini){
	id = idAvionMini;
	puntosDeVida = puntosDeVidaMaximoMini;
	puntosQueOtorgaAlSerImpactado = 0;
	puntosQueOtorgaAlSerDestruido = 100;
	this->alturaDeLaQueSalgo = alturaDeLaQueSalgo;
	listoParaSalir = false;
	this->angulo = 0.0;
}

void FakeAvionDeFormacion::continuarMovimiento(std::list<SuperficieOcupada> superficiesAvionesJugadores){
	if(superficieOcupada->obtenerPosicion().getPosY() < alturaDeLaQueSalgo){
		listoParaSalir = true;
	}
	if(!listoParaSalir){
		//Me voy moviendo con el mapa
		superficieOcupada->desplazarEnYObteniendoHitbox(-1);
	}else{
		if (this->angulo < 100){
			this->angulo += DELTA_TITA;
			UtilJuego * utilJ = UtilJuego::getInstance();
			double pX = this->superficieOcupada->x;
			double pY = this->superficieOcupada->y;
			utilJ->updatePolarToCartesiana(V_RADIO,this->angulo,&pX,&pY);
			this->superficieOcupada->x = pX;
			this->superficieOcupada->y= pY;
		}
		else{
			superficieOcupada->desplazarEnXObteniendoHitbox(-velocidadAvionMini);
		//En algun x habria que empezar un giro. Junto con este hay que actualizar la frame.
		//incrementar el angulo
		}

	}
	
}
