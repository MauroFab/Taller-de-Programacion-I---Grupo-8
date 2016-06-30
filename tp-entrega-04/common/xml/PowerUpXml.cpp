#include "PowerUpXml.h"

PowerUpXml::PowerUpXml()
{
}
PowerUpXml::PowerUpXml(int idSprite,char * strIdSprite,int coorX,int coorY,int tipo)
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

PowerUpXml::PowerUpXml(const PowerUpXml&powerUp){
	this->sizeBytes = powerUp.sizeBytes;
	this->id = powerUp.id;
	this->idSprite = powerUp.idSprite;
	this->strIdSprite = new char[strlen(powerUp.strIdSprite) + 1];
	strcpy(this->strIdSprite,powerUp.strIdSprite);
	this->posicion.coorX = powerUp.posicion.coorX;
	this->posicion.coorY = powerUp.posicion.coorY;
	this->tipo = powerUp.tipo;
}

PowerUpXml::~PowerUpXml()
{
	if (this->strIdSprite != NULL)
		delete []this->strIdSprite;
}
int PowerUpXml::getSizeBytes(){
	return this->sizeBytes;
}
void PowerUpXml::calculateSizeBytes(){
	this->sizeBytes = sizeof(int) //sizeBytes
		+ sizeof(int)//id
		+ sizeof(int)//idSprite
		+ sizeof(char)//len de strSpAvion
		+ sizeof(char)*(strlen(strIdSprite) + 1)
		+ sizeof(int)//coorX
		+ sizeof(int)//coorY
		+ sizeof(int);//tipo
}
void PowerUpXml::setId(int id){
	this->id = id;
}
int PowerUpXml::getId(){
	return this->id;
}
void PowerUpXml::setIdSprite(int idSprite){
	this->idSprite = idSprite;
}
int PowerUpXml::getIdSprite(){
	return this->idSprite;
}
void PowerUpXml::setStrIdSprite(char * strIdSprite, int len_strIdSprite){
	this->strIdSprite = new char[len_strIdSprite + 1];
	memcpy(this->strIdSprite,strIdSprite,len_strIdSprite);
	this->strIdSprite[len_strIdSprite] = '\0';
}
char * PowerUpXml::getStrIdSprite(){
	return this->strIdSprite;
}
void PowerUpXml::setPosicion(TPosicion posicion){
	this->posicion.coorX = posicion.coorX;
	this->posicion.coorY = posicion.coorY;
}
TPosicion PowerUpXml::getPosicion(){
	return this->posicion;
}
void PowerUpXml::setTipo(int tipo){
	this->tipo = tipo;
}
int PowerUpXml::getTipo(){
	return this->tipo;
}
PowerUpXml & PowerUpXml::operator = (const PowerUpXml & source)
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

void PowerUpXml::toString(TCadena1000 cadena){
	sprintf(cadena,"PowerUpXml:sizeBytes=%d,id=%d,idSprite=%d,strIdSprite=%s,posicion.coorX=%d,posicion.coorY=%d,tipo=%d",
		sizeBytes,id,idSprite,strIdSprite,posicion.coorX,posicion.coorY,tipo);
}
