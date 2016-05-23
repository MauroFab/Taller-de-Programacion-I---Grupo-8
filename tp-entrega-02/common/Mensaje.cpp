#include "Mensaje.h"

Mensaje::Mensaje()
{
	// sizeof - tipo mensaje - id 
	this->sizeBytes = sizeof(int) + sizeof(int)+ sizeof(int);
	this->id = -1;
}

Mensaje::~Mensaje(){

}

int Mensaje::getTipo(){
	return 0;
}

void Mensaje::setId(int id){
	this->id = id;
}

int Mensaje::getId(){
	return this->id;
}

int Mensaje::getSizeBytes(){
	return this->sizeBytes;
}

void Mensaje::calculateSizeBytes(){
	this->sizeBytes =  sizeof(int) //sizeBytes
		+ sizeof(int) // tipo de mensaje
		+ sizeof(int);  //id
}

void Mensaje::toString(TCadena1000 cadena){


}
