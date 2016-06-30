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
	this->frame = convertirFrameQueQuieroAFrameReal(12);
}

//El avion le daba varios numeros a las frames para demorar el giro, por esas cosas ahora aca
//hay que hacer un ajuste con esta funcion
//las frames aca van de la 0 a la 12
int FakeAvionDeFormacion::convertirFrameQueQuieroAFrameReal(int frameQueQuiero){
	//16 es la cantidad de frames que tiene la sprite
	return ((frameQueQuiero)*16);
}

void FakeAvionDeFormacion::cargarPosicionesDelCirculo(){
	double xi, yi;
	//Cargo 360 posiciones, cada una corresponde a un angulo
	for(double i = 270; i <= 630 ; i++){
		xi = radioCirculo*cos(i*PI/180) + xDondeGiro;
		yi = radioCirculo*sin(i*PI/180) + radioCirculo + alturaDeLaQueSalgo;
		Posicion* posicionCirculo = new Posicion(static_cast<int> (xi),static_cast<int> (yi));
		posicionesDelCirculo.push_back(posicionCirculo);
	}
}

void FakeAvionDeFormacion::configurarFrameSabiendoQueQuedan(int cantidadDePosiciones){
	//Hay muchas conversion, basandome que recorro 360 posiciones, que tengo 19 frames, que la original esta en la 16, 
	//y giro moviendome para la izquierda
	if(cantidadDePosiciones != 0){
		//16 es la cantidad de frames
		int tamanioDeIntervalos = 360/16;
		if(cantidadDePosiciones/tamanioDeIntervalos >= 4){
			this->frame = convertirFrameQueQuieroAFrameReal(cantidadDePosiciones/tamanioDeIntervalos - 4);
		}else{
			this->frame = convertirFrameQueQuieroAFrameReal(12 + cantidadDePosiciones/tamanioDeIntervalos);
		}
	}else{
		this->frame = convertirFrameQueQuieroAFrameReal(12);
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
			configurarFrameSabiendoQueQuedan(posicionesDelCirculo.size());
			yaTermineElGiro = posicionesDelCirculo.empty();
			estoyHaciendoElGiro = !yaTermineElGiro;
		}
	}
}