#include "MensajeXml.h"

MensajeXml::MensajeXml()
{
	this->sizeBytes = -1;
	this->id = -1;
	this->tipo = -1;
	this->valor = NULL;
}
MensajeXml::MensajeXml(int id,int tipo,void * valor){
	this->id = id;
	this->tipo = tipo;
	switch (tipo)
	{
		case TIPO_CHAR:{
			this->valor = new char[1];
			*((char*)this->valor) = *((char*)valor);
			//sizeBytes + id  + tipo + valor[char]
			//   int	+ int + int  + char
			this->sizeBytes = sizeof(int) + sizeof(int) + sizeof(int) + sizeof(char);
		}
		break;
		case TIPO_STRING:{
			int len = strlen((char*)valor);
			this->valor = new char[len + 1];
			strcpy((char*)this->valor, (char*)valor);
			//sizeBytes + id  + tipo + valor[char] * (len + 1)
			//   int	+ int + int  + char * (len + 1)
			this->sizeBytes = sizeof(int) + sizeof(int) + sizeof(int) + sizeof(char)*(len + 1);

		}
		break;
		case TIPO_DOUBLE:{
			this->valor = new double;
			*((double*)this->valor) = *((double*)valor);
			//sizeBytes + id  + tipo + valor[double]
			//   int	+ int + int  + double
			this->sizeBytes = sizeof(int) + sizeof(int) + sizeof(int) + sizeof(double);
		}
		break;
		case TIPO_INT:{
			this->valor = new int;
			*((int*)this->valor) = *((int*)valor);
			//sizeBytes + id  + tipo + valor[int]
			//   int	+ int + int  + int
			this->sizeBytes = sizeof(int) + sizeof(int) + sizeof(int) + sizeof(int);
		}
		break;
		default:
		break;
	}

}
MensajeXml::~MensajeXml()
{
	switch (tipo)
	{
		case TIPO_CHAR:{
			char * p = (char*)this->valor;
			delete [] p;
		}
		break;
		case TIPO_STRING:{
			char * p = (char*)this->valor;
			delete [] p;
		}
		break;
		case TIPO_DOUBLE:{
			double * p = (double*)this->valor;
			delete p;
		}
		break;
		case TIPO_INT:{
			int * p = (int*)this->valor;
			delete p;
		}
		break;
		default:
		break;
	}
}
int MensajeXml::getSizeBytes(){
	return this->sizeBytes;
}
void MensajeXml::setId(int id){
	this->id = id;
}
int MensajeXml::getId(){
	return this->id;
}
void MensajeXml::setTipo(int tipo){
	this->tipo = tipo;
}
int MensajeXml::getTipo(){
	return this->tipo;
}

void * MensajeXml::getValor(){
	return this->valor;
}

