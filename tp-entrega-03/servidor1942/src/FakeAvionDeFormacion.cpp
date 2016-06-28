#include "FakeAvionDeFormacion.h"

 FakeAvionDeFormacion::FakeAvionDeFormacion(int y, int alturaDeLaQueSalgo) : 
					FakeAvionEnemigo(xInicial,y,anchoAvionMini,altoAvionMini,velocidadAvionMini){
	id = idAvionMini;
	puntosDeVida = puntosDeVidaMaximoMini;
	puntosQueOtorgaAlSerImpactado = 0;
	puntosQueOtorgaAlSerDestruido = 100;
	this->alturaDeLaQueSalgo = alturaDeLaQueSalgo;
	listoParaSalir = false;
	this->estoyHaciendoElGiro = false;
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
		if(!estoyHaciendoElGiro){
			superficieOcupada->desplazarEnXObteniendoHitbox(-velocidadAvionMini);
		}
		if(superficieOcupada->obtenerPosicion().getPosX() == 200){
			estoyHaciendoElGiro = true;
		}

		if(estoyHaciendoElGiro){
			//continuoElGiro
			this->angulo += DELTA_TITA;
			UtilJuego * utilJ = UtilJuego::getInstance();
			double pX = this->superficieOcupada->x;
			double pY = this->superficieOcupada->y;
			utilJ->updatePolarToCartesiana(V_RADIO,this->angulo,&pX,&pY);
			this->superficieOcupada->moverAPosicion(Posicion(static_cast<int> (pX),static_cast<int> (pY)));
			if(angulo > 360)
				estoyHaciendoElGiro = false;
		}
		/*if (this->angulo < 100){
			
			
			
			
			this->superficieOcupada->x = pX;
			this->superficieOcupada->y= pY;
		}
		else{
			
		}*/

	}
	
}
