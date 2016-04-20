#include "MensajeXml.h"

MensajeXml::MensajeXml() {

	this->sizeBytes = -1;
	this->id = -1;
	this->tipo = -1;
	this->valor = NULL;
}

MensajeXml::MensajeXml(int id,int tipo,char * valor){

	this->id = id;
	this->tipo = tipo;
	int len = strlen(valor);
	this->valor = new char[len + 1];
	strcpy(this->valor,valor);
	//sizeBytes + id  + tipo + valor[char] * (len + 1)
	//   int	+ int + int  + char * (len + 1)
	this->sizeBytes = sizeof(int) + sizeof(int) + sizeof(int) + sizeof(char)*(len + 1);	
}

MensajeXml::MensajeXml(const MensajeXml&mensaje){
	this->sizeBytes = mensaje.sizeBytes;
	this->id = mensaje.id;
	this->tipo = mensaje.tipo;
	int lenValor = strlen(mensaje.valor);
	this->valor = new char[lenValor +1];
	memcpy(this->valor,mensaje.valor,lenValor +1);	
}

MensajeXml::~MensajeXml() {

	delete [] this->valor;
}

MensajeXml & MensajeXml::operator = (const MensajeXml & source)
{
	this->sizeBytes = source.sizeBytes;
	this->id = source.id;
	this->tipo = source.tipo;
	this->id = source.id;
	int lenValor = strlen(source.valor);
	this->valor = new char[lenValor +1];
	memcpy(this->valor,source.valor,lenValor +1);	
    return *this;
};

int MensajeXml::getSizeBytes(){
	return this->sizeBytes;
}
/**
 * como precondicion el VALOR debe estar cargado, de lo contrario No se calcula
 * correctamente el sizeBytes
 * como NO exite un setSizeBytes() este lo reemplaza
 */
void MensajeXml::calculateSizeBytes(){
	int len = strlen(this->valor);
	this->sizeBytes =  sizeof(int) + sizeof(int) + sizeof(int) + sizeof(char)*(len + 1);	
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

char * MensajeXml::getValor(){
	return this->valor;
}

void MensajeXml::setValor(char * valor,int lenValor){
	this->valor = new char[lenValor];
	memcpy(this->valor,valor,lenValor);
}
