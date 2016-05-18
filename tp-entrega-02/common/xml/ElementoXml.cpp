#include "ElementoXml.h"
/* @autor sabris
 */
ElementoXml::ElementoXml()
{
	this->sizeBytes = -1;
	this->id = -1;
	this->idSprite = -1;
	this->strIdSprite = NULL;
	this->posicion.coorX = -1;
	this->posicion.coorY = -1;
}
ElementoXml::ElementoXml(int idSprite,char * strIdSprite,int coorX,int coorY)
{
	this->sizeBytes = -1;
	this->id = -1;
	this->idSprite = idSprite;
	this->strIdSprite = new char[strlen(strIdSprite) + 1];
	strcpy(this->strIdSprite,strIdSprite);
	this->posicion.coorX = coorX;
	this->posicion.coorY = coorY;
}

ElementoXml::ElementoXml(const ElementoXml&elemento){
	this->sizeBytes = elemento.sizeBytes;
	this->id = elemento.id;
	this->idSprite = elemento.idSprite;
	this->strIdSprite = new char[strlen(elemento.strIdSprite) + 1];
	strcpy(this->strIdSprite,elemento.strIdSprite);
	this->posicion.coorX = elemento.posicion.coorX;
	this->posicion.coorY = elemento.posicion.coorY;
}

ElementoXml::~ElementoXml()
{
	if (this->strIdSprite != NULL)
		delete []this->strIdSprite;
}
int ElementoXml::getSizeBytes(){
	return this->sizeBytes;
}
/**
 * como precondicion el VALOR debe estar cargado, de lo contrario No se calcula
 * correctamente el sizeBytes
 * como NO exite un setSizeBytes() este lo reemplaza
 */
void ElementoXml::calculateSizeBytes(){
	this->sizeBytes = sizeof(int) //sizeBytes
		+ sizeof(int)//id
		+ sizeof(int)//idSprite
		+ sizeof(char)//len de strSpAvion
		+ sizeof(char)*(strlen(strIdSprite) + 1)
		+ sizeof(int)//coorX
		+ sizeof(int);//coorY
}
void ElementoXml::setId(int id){
	this->id = id;
}
int ElementoXml::getId(){
	return this->id;
}
void ElementoXml::setIdSprite(int idSprite){
	this->idSprite = idSprite;
}
int ElementoXml::getIdSprite(){
	return this->idSprite;
}
void ElementoXml::setStrIdSprite(char * strIdSprite, int len_strIdSprite){
	this->strIdSprite = new char[len_strIdSprite + 1];
	memcpy(this->strIdSprite,strIdSprite,len_strIdSprite);
	this->strIdSprite[len_strIdSprite] = '\0';
}
char * ElementoXml::getStrIdSprite(){
	return this->strIdSprite;
}
void ElementoXml::setPosicion(TPosicion posicion){
	this->posicion.coorX = posicion.coorX;
	this->posicion.coorY = posicion.coorY;
}
TPosicion ElementoXml::getPosicion(){
	return this->posicion;
}

ElementoXml & ElementoXml::operator = (const ElementoXml & source)
{
	this->sizeBytes = source.sizeBytes;
	this->id = source.id;
	this->idSprite = source.idSprite;
	this->strIdSprite = new char[strlen(source.strIdSprite) + 1];
	strcpy(this->strIdSprite,source.strIdSprite);
	this->posicion.coorX = source.posicion.coorX;
	this->posicion.coorY = source.posicion.coorY;
    return *this;
}

void ElementoXml::toString(TCadena1000 cadena){
	sprintf(cadena,"ElementoXml:sizeBytes=%d,id=%d,idSprite=%d,strIdSprite=%s,posicion.coorX=%d,posicion.coorY=%d",
		sizeBytes,id,idSprite,strIdSprite,posicion.coorX,posicion.coorY);
}

