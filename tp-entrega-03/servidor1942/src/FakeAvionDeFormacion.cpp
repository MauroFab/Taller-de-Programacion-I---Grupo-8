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
			pXGiro = this->superficieOcupada->x;
			pYGiro = this->superficieOcupada->y;
		}

		if(estoyHaciendoElGiro){
			//continuoElGiro
			this->angulo += DELTA_TITA;
			UtilJuego * utilJ = UtilJuego::getInstance();
			utilJ->updatePolarToCartesiana(V_RADIO,this->angulo,&pXGiro,&pYGiro);
			this->superficieOcupada->moverAPosicion(Posicion(static_cast<int> (pXGiro),static_cast<int> (pYGiro)));
			if(angulo > 360)
				estoyHaciendoElGiro = false;
		}
	}
}
