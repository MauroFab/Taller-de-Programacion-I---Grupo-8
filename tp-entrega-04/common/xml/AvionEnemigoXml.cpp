#include "AvionEnemigoXml.h"

AvionEnemigoXml::AvionEnemigoXml()
{
}
AvionEnemigoXml::AvionEnemigoXml(int idSprite,char * strIdSprite,int coorX,int coorY,int tipo)
{
	this->sizeBytes = -1;
	this->id = -1;
	this->idSprite = idSprite;
	this->strIdSprite = new char[strlen(strIdSprite) + 1];
	strcpy(this->strIdSprite,strIdSprite);
	this->posicion.coorX = coorX;
	this->posicion.coorY = coorY;
	this->tipo = tipo;
}

AvionEnemigoXml::AvionEnemigoXml(const AvionEnemigoXml&avionEne){
	this->sizeBytes = avionEne.sizeBytes;
	this->id = avionEne.id;
	this->idSprite = avionEne.idSprite;
	this->strIdSprite = new char[strlen(avionEne.strIdSprite) + 1];
	strcpy(this->strIdSprite,avionEne.strIdSprite);
	this->posicion.coorX = avionEne.posicion.coorX;
	this->posicion.coorY = avionEne.posicion.coorY;
	this->tipo = avionEne.tipo;
}

AvionEnemigoXml::~AvionEnemigoXml()
{
	if (this->strIdSprite != NULL)
		delete []this->strIdSprite;
}
int AvionEnemigoXml::getSizeBytes(){
	return this->sizeBytes;
}
void AvionEnemigoXml::calculateSizeBytes(){
	this->sizeBytes = sizeof(int) //sizeBytes
		+ sizeof(int)//id
		+ sizeof(int)//idSprite
		+ sizeof(char)//len de strSpAvion
		+ sizeof(char)*(strlen(strIdSprite) + 1)
		+ sizeof(int)//coorX
		+ sizeof(int)//coorY
		+ sizeof(int);//tipo
}
void AvionEnemigoXml::setId(int id){
	this->id = id;
}
int AvionEnemigoXml::getId(){
	return this->id;
}
void AvionEnemigoXml::setIdSprite(int idSprite){
	this->idSprite = idSprite;
}
int AvionEnemigoXml::getIdSprite(){
	return this->idSprite;
}
void AvionEnemigoXml::setStrIdSprite(char * strIdSprite, int len_strIdSprite){
	this->strIdSprite = new char[len_strIdSprite + 1];
	memcpy(this->strIdSprite,strIdSprite,len_strIdSprite);
	this->strIdSprite[len_strIdSprite] = '\0';
}
char * AvionEnemigoXml::getStrIdSprite(){
	return this->strIdSprite;
}
void AvionEnemigoXml::setPosicion(TPosicion posicion){
	this->posicion.coorX = posicion.coorX;
	this->posicion.coorY = posicion.coorY;
}
TPosicion AvionEnemigoXml::getPosicion(){
	return this->posicion;
}
void AvionEnemigoXml::setTipo(int tipo){
	this->tipo = tipo;
}
int AvionEnemigoXml::getTipo(){
	return this->tipo;
}
AvionEnemigoXml & AvionEnemigoXml::operator = (const AvionEnemigoXml & source)
{
	this->sizeBytes = source.sizeBytes;
	this->id = source.id;
	this->idSprite = source.idSprite;
	this->strIdSprite = new char[strlen(source.strIdSprite) + 1];
	strcpy(this->strIdSprite,source.strIdSprite);
	this->posicion.coorX = source.posicion.coorX;
	this->posicion.coorY = source.posicion.coorY;
	this->tipo = source.tipo;
    return *this;
}

void AvionEnemigoXml::toString(TCadena1000 cadena){
	sprintf(cadena,"AvionEnemigoXml:sizeBytes=%d,id=%d,idSprite=%d,strIdSprite=%s,posicion.coorX=%d,posicion.coorY=%d,tipo=%d",
		sizeBytes,id,idSprite,strIdSprite,posicion.coorX,posicion.coorY,tipo);
}
