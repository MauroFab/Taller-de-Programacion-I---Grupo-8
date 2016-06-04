#include "SpriteXml.h"
/* @autor sabris
 */
SpriteXml::SpriteXml()
{
	this->sizeBytes = -1;
	this->id = -1;
	this->strId = NULL;
	this->path = NULL;
	this->cantidad = -1;
	this->ancho = -1;
	this->alto = -1;
}
SpriteXml::SpriteXml(int id,char * strId,char * path,int cantidad, int ancho, int alto){
	this->sizeBytes = -1;
	this->id = id;
	this->strId = new char[strlen(strId) + 1];
	strcpy(this->strId,strId);
	this->path = new char[strlen(path) + 1];
	strcpy(this->path,path);
	this->cantidad = cantidad;
	this->ancho = ancho;
	this->alto = alto;
}

SpriteXml::~SpriteXml()
{
	if (this->strId != NULL)
		delete [] this->strId;
	if (this->path != NULL)
		delete [] this->path;
}
int SpriteXml::getSizeBytes(){
	return this->sizeBytes;
}
/**
 * como precondicion los VALORES char* deben estar cargado, de lo contrario No se calcula
 * correctamente el sizeBytes
 * como NO existe un setSizeBytes() este lo reemplaza
 */
void SpriteXml::calculateSizeBytes(){
	this->sizeBytes = sizeof(int) //sizeBytes
		+ sizeof(int)//id
		+ sizeof(char)//len de strId
		+ sizeof(char)*(strlen(strId) + 1)
		+ sizeof(char)//len de path
		+ sizeof(char)*(strlen(path) + 1)
		+ sizeof(int)//cantidad
		+ sizeof(int)//ancho
		+ sizeof(int);//alto
}
void SpriteXml::setId(int id){
	this->id = id;
}
int SpriteXml::getId(){
	return this->id;
}
void SpriteXml::setStrId(char * strId,char len_strId){
	this->strId = new char[len_strId + 1];
	memcpy(this->strId,strId,len_strId);
	this->strId[len_strId] = '\0';
}
char * SpriteXml::getStrId(){
	return this->strId;
}
void SpriteXml::setPath(char * path,char len_path){
	if (this->path != NULL)
		delete [] this->path;	
	this->path = new char[len_path + 1];
	memcpy(this->path,path,len_path);
	this->path[len_path] = '\0';
}

void SpriteXml::resetPath(char * path,char len_path){
	this->path = new char[len_path + 1];
	memcpy(this->path,path,len_path);
	this->path[len_path] = '\0';
}
char * SpriteXml::getPath(){
	return this->path;
}
void SpriteXml::setCantidad(int cantidad){
	this->cantidad = cantidad;
}
int SpriteXml::getCantidad(){
	return this->cantidad;
}
void SpriteXml::setAncho(int ancho){
	this->ancho = ancho;
}
int SpriteXml::getAncho(){
	return this->ancho;
}
void SpriteXml::setAlto(int alto){
	this->alto = alto;
}
int SpriteXml::getAlto(){
	return this->alto;
}
SpriteXml * SpriteXml::findSpriteById(int idSprite,SpriteXml ** listSpriteXml,int cantS){
	SpriteXml * spriteX = NULL;
	int bOut = false;
	for (int j = 0;j <cantS && !bOut;j++){
		spriteX = listSpriteXml[j];
		if (idSprite == spriteX->getId()){
			bOut = true;
			return spriteX;
		}
	}
	return NULL;
}

void SpriteXml::toString(TCadena1000 cadena){
	sprintf(cadena,"SpriteXml:id=%d,strId=%s,path=%s,cantidad=%d,ancho=%d,ancho=%d",
		id,strId,path,cantidad,ancho,alto);
}
