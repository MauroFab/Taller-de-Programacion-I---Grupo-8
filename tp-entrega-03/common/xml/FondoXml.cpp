#include "FondoXml.h"
/* @autor sabris
 */
FondoXml::FondoXml()
{
	this->sizeBytes = -1;
	this->idSprite = -1;
	this->strIdSprite = NULL;
	this->ancho = -1;
	this->alto = -1;
}

FondoXml::FondoXml(int idSprite,char * strIdSprite,int ancho,int alto)
{
	this->sizeBytes = -1;
	this->idSprite = idSprite;
	this->strIdSprite = new char[strlen(strIdSprite) + 1];
	strcpy(this->strIdSprite,strIdSprite);
	this->ancho = ancho;
	this->alto = alto;
}

FondoXml::~FondoXml()
{
	if (this->strIdSprite != NULL)
		delete []this->strIdSprite;
}
int FondoXml::getSizeBytes(){
	return this->sizeBytes;
}
/**
 * como precondicion los VALORES char* deben estar cargado, de lo contrario No se calcula
 * correctamente el sizeBytes
 * como NO existe un setSizeBytes() este lo reemplaza
 */
void FondoXml::calculateSizeBytes(){
	this->sizeBytes = sizeof(int) //sizeBytes
		+ sizeof(char)//len de strIdSprite
		+ sizeof(char)*(strlen(strIdSprite) + 1)
		+ sizeof(int)//ancho
		+ sizeof(int);//alto
}
void FondoXml::setIdSprite(int idSprite){
	this->idSprite = idSprite;
}
int FondoXml::getIdSprite(){
	return this->idSprite;
}
void FondoXml::setStrIdSprite(char * strIdSprite,int len_strIdSprite){
	this->strIdSprite = new char[len_strIdSprite + 1];
	memcpy(this->strIdSprite,strIdSprite,len_strIdSprite);
	this->strIdSprite[len_strIdSprite] = '\0';
}
char * FondoXml::getStrIdSprite(){
	return this->strIdSprite;
}
void FondoXml::setAncho(int ancho){
	this->ancho = ancho;
}
int FondoXml::getAncho(){
	return this->ancho;
}
void FondoXml::setAlto(int alto){
	this->alto = alto;
}
int FondoXml::getAlto(){
	return this->alto;
}

FondoXml & FondoXml::operator = (const FondoXml & source)
{
	this->idSprite = source.idSprite;
	this->ancho = source.ancho;
	this->alto = source.alto;
	this->strIdSprite = new char[strlen(source.strIdSprite) + 1];
	strcpy(this->strIdSprite,source.strIdSprite);
    return *this;
}

void FondoXml::toString(TCadena1000 cadena){
	sprintf(cadena,"FondoXml:idSprite=%d,strIdSprite=%s,ancho=%d,alto=%d",idSprite,strIdSprite,ancho,alto);
}
