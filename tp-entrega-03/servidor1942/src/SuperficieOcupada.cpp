#include "SuperficieOcupada.h"
SuperficieOcupada::SuperficieOcupada(){

}
SuperficieOcupada::SuperficieOcupada(int x, int y, int ancho, int alto){
	this->x = x;
	this->y = y;
	this->ancho = ancho;
	this->alto = alto;
}

SuperficieOcupada SuperficieOcupada::moverAPosicionXObteniendoHitbox(int xNuevo){
	int xEnElQueEstaba;
	xEnElQueEstaba = x;
	x= xNuevo;

	int altoDeLaHitbox = alto;
	//El ancho de la hitbox es la distancia entre los dos x + ancho
	int anchoHitbox = abs(xEnElQueEstaba - xNuevo) + ancho;
	//El x siempre esta a la izquierda de la imagen
	int xHitbox = valorMinimoEntre(xEnElQueEstaba,  xNuevo);
	//En y no me movi
	int yHitbox = y;
	int altoHitbox = alto;
	return(SuperficieOcupada(xHitbox, yHitbox,anchoHitbox,altoHitbox));
}

SuperficieOcupada SuperficieOcupada::moverAPosicionYObteniendoHitbox(int yNuevo){
	int yEnElQueEstaba;
	yEnElQueEstaba = y;
	y = yNuevo;

	int altoDeLaHitbox = alto;
	//El ancho de la hitbox es la distancia entre los dos x + ancho
	int altoHitbox = abs(yEnElQueEstaba - yNuevo) + alto;
	//El y siempre esta abajo de la imagen
	int yHitbox = valorMinimoEntre(yEnElQueEstaba,  yNuevo);
	//En x no me movi
	int xHitbox = x;
	int anchoHitbox = ancho;
	return(SuperficieOcupada(xHitbox, yHitbox,anchoHitbox,altoHitbox));
}

SuperficieOcupada SuperficieOcupada::desplazarEnXObteniendoHitbox(int distanciaAMoverEnX){
	int xNuevo = x + distanciaAMoverEnX;
	SuperficieOcupada hitbox = moverAPosicionXObteniendoHitbox(xNuevo);
	return(hitbox);
}

SuperficieOcupada SuperficieOcupada::desplazarEnYObteniendoHitbox(int distanciaAMoverEnY){
	int yNuevo = y + distanciaAMoverEnY;
	SuperficieOcupada hitbox = moverAPosicionYObteniendoHitbox(yNuevo);
	return(hitbox);
}

bool SuperficieOcupada::compartoUnaRegionEnXCon(SuperficieOcupada otraSuperficieOcupada){
	bool meSolapo;
	//Si estoy a la izquierda
	if(x < otraSuperficieOcupada.x){
		meSolapo = (otraSuperficieOcupada.x > x && otraSuperficieOcupada.x < (x + ancho));
	}else{
		meSolapo = (x > otraSuperficieOcupada.x && x < (otraSuperficieOcupada.x + otraSuperficieOcupada.ancho));
	}
	return(meSolapo);
}

bool SuperficieOcupada::compartoUnaRegionEnYCon(SuperficieOcupada otraSuperficieOcupada){
	bool meSolapo;
	//Si estoy abajo
	if(y < otraSuperficieOcupada.y){
		meSolapo = (otraSuperficieOcupada.y > y && otraSuperficieOcupada.y < (y + alto));
	}else{
		meSolapo = (y > otraSuperficieOcupada.y && y < (otraSuperficieOcupada.y + otraSuperficieOcupada.alto));
	}
	return(meSolapo);
}

bool SuperficieOcupada::meSolapoCon(SuperficieOcupada otraSuperficieOcupada){
	return(compartoUnaRegionEnXCon(otraSuperficieOcupada) && compartoUnaRegionEnYCon(otraSuperficieOcupada));
}

int SuperficieOcupada::valorMinimoEntre(int a, int b){
	if(a < b){
		return a;
	}else{
		return b;
	}
}

int SuperficieOcupada::valorMaximoEntre(int a, int b){
	if(a > b){
		return a;
	}else{
		return b;
	}
}

Posicion SuperficieOcupada::obtenerPosicion(){
	return(Posicion(x,y));
}

void SuperficieOcupada::moverAPosicion(Posicion posicion){
	x = posicion.getPosX();
	y = posicion.getPosY();
}

void SuperficieOcupada::moverAX(int x){
	this->x = x;
}

void SuperficieOcupada::moverAY(int y){
	this->y = y;
}
