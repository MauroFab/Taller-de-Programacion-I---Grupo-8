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

SuperficieOcupada FakeAvionEnemigo::obtenerElementoiDeLaLista(int i, std::list<SuperficieOcupada> lista){
	std::list<SuperficieOcupada>::iterator it;
	it = lista.begin();
	std::advance(it, i);
	return((*it));
}


void FakeAvionEnemigo::ajustarLaNormaDelVector(double &xVector, double &yVector, double norma){
	double coeficienteParaAjustarElModulo;
	//Esto sale de plantear que la norma debe ser igual a un numero
	//Y que el x nuevo y el y nuevo deben ser un multiplo de los viejos
	coeficienteParaAjustarElModulo = sqrt(norma/(xVector*xVector+yVector*yVector));
	xVector = xVector * coeficienteParaAjustarElModulo;
	yVector = yVector * coeficienteParaAjustarElModulo;
}

void FakeAvionEnemigo::disparar(std::list<SuperficieOcupada> superficiesAvionesJugadores){

	int posXProyectil = superficieOcupada->obtenerPosicionCentro().getPosX();
	int posYProyectil = superficieOcupada->obtenerPosicion().getPosY();
	int avionAlQueApunto = rand() % superficiesAvionesJugadores.size();

	SuperficieOcupada superficieEnemigoApuntado;
	superficieEnemigoApuntado = obtenerElementoiDeLaLista(avionAlQueApunto, superficiesAvionesJugadores); 

	int xAlQueApunto = superficieEnemigoApuntado.obtenerPosicionCentro().getPosX();
	int yAlQueApunto = superficieEnemigoApuntado.obtenerPosicionCentro().getPosY();

	//Calculo primero para donde apunta el vector velocidad, luego ajusto su norma
	//Esto es la resta entre los vectores posicion
	double xVectorVelocidad = (xAlQueApunto - posXProyectil );
	double yVectorVelocidad = (yAlQueApunto - posYProyectil );

	int norma = 8;
	ajustarLaNormaDelVector(xVectorVelocidad, yVectorVelocidad, norma);

	proyectiles.push_back(new ProyectilEnemigo(posXProyectil,posYProyectil,xVectorVelocidad, yVectorVelocidad));
}

void FakeAvionEnemigo::moverProyectiles(){
	std::list<ProyectilEnemigo*>::iterator it;
	for(it = proyectiles.begin(); it != proyectiles.end(); it++){
		(*it)->mover();
	}
}

void FakeAvionEnemigo::continuarMovimiento(std::list<SuperficieOcupada> superficiesAvionesJugadores){
	if(!this->estaDestruido()){
		SuperficieOcupada superficiePantalla(0,0,480,640);
		//Si estoy en pantalla
		if(this->superficieOcupada->meSolapoCon(superficiePantalla)){
			//Activo todo el movimiento
			superficieOcupada->desplazarEnYObteniendoHitbox(velocidadY);
			superficieOcupada->desplazarEnXObteniendoHitbox(velocidadX);
			if(elijoAlAzarSiDisparo() == true){
				disparar(superficiesAvionesJugadores);
			}	
		}else{//si no estoy en pantalla
			//bajo con el mapa
			superficieOcupada->desplazarEnYObteniendoHitbox(-1);
		}
	}
	moverProyectiles();
	//La libero de a poco. Se llama muchas veces a este metodo.
	//Con esto descargo algo de trabajo revisando todo el tiempo todos los proyectiles
	revisoMemoriaDelProyectilMasNuevo();
}

void FakeAvionEnemigo::revisoMemoriaDelProyectilMasNuevo(){
	if(!proyectiles.empty()){
		SuperficieOcupada superficiePantalla(0,0,480,640);
		ProyectilEnemigo* proyectil;
		proyectil = proyectiles.front();
		//Si esta destruido o no esta en pantalla, se puede borrar
		if(proyectil->estaDestruido() || !superficiePantalla.meSolapoCon(proyectil->getSuperficieOcupada())){
			proyectiles.pop_front();
			delete proyectil;
		}
	}
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