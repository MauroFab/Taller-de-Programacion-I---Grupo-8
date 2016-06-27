
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

void FakeAvionDeFormacion::continuarMovimiento(){
	if(superficieOcupada->obtenerPosicion().getPosY() < alturaDeLaQueSalgo){
		listoParaSalir = true;
	}
	if(!listoParaSalir){
		//Me voy moviendo con el mapa
		superficieOcupada->desplazarEnYObteniendoHitbox(-1);
	}else{
		superficieOcupada->desplazarEnXObteniendoHitbox(-velocidadAvionMini);
		//En algun x habria que empezar un giro. Junto con este hay que actualizar la frame.
	}
	//incrementar el angulo
}
