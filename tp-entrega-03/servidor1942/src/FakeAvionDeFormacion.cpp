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
	yaTermineElGiro = false;
	cargarPosicionesDelCirculo();
}

void FakeAvionDeFormacion::cargarPosicionesDelCirculo(){
	double xi, yi;
	for(double i = 270; i <= 630 ; i++){
		xi = radioCirculo*cos(i*PI/180) + xDondeGiro;
		yi = radioCirculo*sin(i*PI/180) + radioCirculo + alturaDeLaQueSalgo;
		Posicion* posicionCirculo = new Posicion(static_cast<int> (xi),static_cast<int> (yi));
		posicionesDelCirculo.push_back(posicionCirculo);
	}
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
		if(superficieOcupada->obtenerPosicion().getPosX() == 200 && !yaTermineElGiro){
			estoyHaciendoElGiro = true;
		}

		if(estoyHaciendoElGiro && !yaTermineElGiro){
			Posicion* nuevaPosicion = posicionesDelCirculo.back();
			posicionesDelCirculo.pop_back();
			this->superficieOcupada->moverAPosicion(*nuevaPosicion);
			delete nuevaPosicion;
			yaTermineElGiro = posicionesDelCirculo.empty();
			estoyHaciendoElGiro = !yaTermineElGiro;
		}
	}
}