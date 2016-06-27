#include "FakeAvionEnemigo.h"

FakeAvionEnemigo::FakeAvionEnemigo(int xInicial, int yInicial, int ancho, int alto, int velocidad){

	superficieOcupada = new SuperficieOcupada(xInicial,yInicial,ancho,alto);

	this->velocidad = velocidad;
	puntosDeVida = vidaMaximaFakeAvionEnemigo;
	this->frame = 0;
	id = idAvionMiddle;
	this->puntosQueOtorgaAlSerDestruido = 100;
	this->puntosQueOtorgaAlSerImpactado = 0;
	velocidadX = rand() % velocidad - (velocidad/2);
	velocidadY = - rand() % velocidad - 1;
	if(rand() % 2 == 1)
		velocidadX = - velocidadX;
}
bool FakeAvionEnemigo::elijoAlAzarSiDisparo(){
	double probabilidadDeDisparo = 0.01;
	int esperanzaPrimerDisparo = static_cast<int> (1/probabilidadDeDisparo);
	//En este caso la esperanza seria 100,
	//Quiero que una de cada 100 veces que me muevo dispare en promedio
	int numeroAlAzar;
	numeroAlAzar = rand() % esperanzaPrimerDisparo;
	//numero al azar es un numero entre 0 y 99 en este caso
	//Si toca el 0 elijo disparar
	return(numeroAlAzar == 0);
}

void FakeAvionEnemigo::disparar(){
	int miPosicionEnY;
	miPosicionEnY = superficieOcupada->obtenerPosicion().getPosY();
	int miPosicionEnX;
	miPosicionEnX = superficieOcupada->obtenerPosicion().getPosX();
	int posXProyectil = miPosicionEnX;
	int posYProyectil = miPosicionEnY;
	int velocidadYProyectil = velocidadY - 1;
	proyectiles.push_back(new ProyectilEnemigo(posXProyectil,posYProyectil,0, velocidadYProyectil));
}

void FakeAvionEnemigo::moverProyectiles(){
	std::list<ProyectilEnemigo*>::iterator it;
	for(it = proyectiles.begin(); it != proyectiles.end(); it++){
		(*it)->mover();
	}
}

void FakeAvionEnemigo::continuarMovimiento(){
	//Voy bajando con el mapa
	SuperficieOcupada superficiePantalla(0,0,480,640);
	//Si estoy en pantalla
	if(this->superficieOcupada->meSolapoCon(superficiePantalla)){
		//Activo todo el movimiento
		superficieOcupada->desplazarEnYObteniendoHitbox(velocidadY);
		superficieOcupada->desplazarEnXObteniendoHitbox(velocidadX);
		if(elijoAlAzarSiDisparo() == true){
			disparar();
		}	
	}else{//si no estoy en pantalla
		//bajo con el mapa
		superficieOcupada->desplazarEnYObteniendoHitbox(-1);
	}
	moverProyectiles();
}

void FakeAvionEnemigo::reducirPuntosDeVidaEn(int puntosDeDanio){
	puntosDeVida = puntosDeVida - puntosDeDanio;
}

bool FakeAvionEnemigo::estaDestruido(){
	return (puntosDeVida <= 0);
}

void FakeAvionEnemigo::recibeUnImpacto(int idDelJugadorQueLoDanio){
	reducirPuntosDeVidaEn(1);
	//Si me destruyen guardo quien fue
	if(this->estaDestruido())
		idDelQueMeDestruyo = idDelJugadorQueLoDanio;
}
FakeAvionEnemigo::~FakeAvionEnemigo(){
	//Deberia eliminar la superficie, pero esta explotando si lo hago en las pruebas como estan ahora

	//delete superficieOcupada;
}

SuperficieOcupada FakeAvionEnemigo::obtenerSuperficieOcupada(){
	return (*superficieOcupada);
}

EstadoAvion* FakeAvionEnemigo::getEstado() {
	//Paso una cantidad de puntos de vida cualquiera hasta que lo programe
	int miPosicionEnY;
	miPosicionEnY = superficieOcupada->obtenerPosicion().getPosY();
	int miPosicionEnX;
	miPosicionEnX = superficieOcupada->obtenerPosicion().getPosX();
	EstadoAvion*  estado =  new EstadoAvion(id, frame, puntosDeVida,miPosicionEnX, miPosicionEnY);

	std::list<ProyectilEnemigo*>::iterator it;
	for(it = proyectiles.begin(); it != proyectiles.end(); it++){
		estado->agregarEstadoProyectil((*it)->createEstado());
	}
	return estado;
}

int FakeAvionEnemigo::getPuntosQueOtorgaAlSerDestruido(){
	return puntosQueOtorgaAlSerDestruido;
}

int FakeAvionEnemigo::getPuntosQueOtorgaAlSerImpactado(){
	return puntosQueOtorgaAlSerImpactado;
}

//Por defecto no dejan power ups
bool FakeAvionEnemigo::dejaUnPowerUpAlSerDestruido(){
	return false;
}
//No debe ser llamado si no deja un power up
PowerUp FakeAvionEnemigo::getPowerUpQueDejaAlSerDestruido(){
	return PowerUp(-1,-1,-1,-1);
}

void FakeAvionEnemigo::destruir(){
	this->puntosDeVida = 0;
}

bool FakeAvionEnemigo::estaEnPantalla(){
	SuperficieOcupada superficieDelJuego(0,0,anchoPantalla,altoPantalla);
	return(this->superficieOcupada->meSolapoCon(superficieDelJuego));
}

std::list<ProyectilEnemigo*> FakeAvionEnemigo::getProyectiles(){
	return proyectiles;
}