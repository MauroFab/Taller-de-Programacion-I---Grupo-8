#include "MensajeXml.h"
/* @autor sabris
 */
MensajeXml::MensajeXml()
{
	this->sizeBytes = Mensaje::getSizeBytes();
	this->id = -1;
	this->tipoValor = -1;
	this->valor = NULL;
}

MensajeXml::MensajeXml(int id,int tipo,char * valor){
	this->id = id;
	this->tipoValor = tipo;
	int len = strlen(valor);
	this->valor = new char[len + 1];
	strcpy(this->valor,valor);
	//sizeBytes + id  + tipo + valor[char] * (len + 1)
	//   int	+ int + int  + char * (len + 1)
	this->sizeBytes = Mensaje::getSizeBytes() + sizeof(int) + sizeof(char)*(len + 1);
}

MensajeXml::MensajeXml(const MensajeXml&mensaje){
	this->sizeBytes = mensaje.sizeBytes;
	this->id = mensaje.id;
	this->tipoValor = mensaje.tipoValor;
	int lenValor = strlen(mensaje.valor);
	this->valor = new char[lenValor +1];
	memcpy(this->valor,mensaje.valor,lenValor +1);
}

MensajeXml::~MensajeXml()
{
	delete [] this->valor;
}

MensajeXml & MensajeXml::operator = (const MensajeXml & source)
{
	this->sizeBytes = source.sizeBytes;
	this->id = source.id;
	this->tipoValor = source.tipoValor;
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
	this->sizeBytes =  Mensaje::getSizeBytes()
		+ sizeof(int) //tipo_valor
		+ sizeof(char) //len_valor
		//+ sizeof(char)*(len + 1);
		+ sizeof(char)*(len);//valor
}

int MensajeXml::getTipo(){
	return MENSAJE_TIPO_VALOR;
}

void MensajeXml::setId(int id){
	this->id = id;
}
int MensajeXml::getId(){
	return this->id;
}
void MensajeXml::setTipoValor(int tipo){
	this->tipoValor = tipo;
}

int MensajeXml::getTipoValor(){
	return this->tipoValor;
}

char * MensajeXml::getValor(){
	return this->valor;
}

void MensajeXml::setValor(char * valor,int lenValor){
	this->valor = new char[lenValor + 1];
	memcpy(this->valor,valor,lenValor + 1);
}

void MensajeXml::toString(TCadena1000 cadena){
	sprintf(cadena,"MensajeXml:sizeBytes=%d,id=%d,tipo valor=%d,valor=%s",sizeBytes,id,tipoValor,valor);
}