#include "VentanaXml.h"
/* @autor sabris
 */
VentanaXml::VentanaXml()
{
	this->sizeBytes = -1;
	this->ancho = -1;
	this->alto = -1;
	this->velocidadCamara = -1;
}
VentanaXml::VentanaXml(int ancho,int alto,int velocidadCamara)
{
	this->sizeBytes = -1;
	this->ancho = ancho;
	this->alto = alto;
	this->velocidadCamara = velocidadCamara;
}

VentanaXml::~VentanaXml()
{
}
int VentanaXml::getSizeBytes(){
	return this->sizeBytes;
}
/**
 * como precondicion los VALORES char* deben estar cargado, de lo contrario No se calcula
 * correctamente el sizeBytes
 * como NO existe un setSizeBytes() este lo reemplaza
 */
void VentanaXml::calculateSizeBytes(){
	this->sizeBytes = sizeof(int) //sizeBytes
		+ sizeof(int)//ancho
		+ sizeof(int)//alto
		+ sizeof(int);//velocidadCamara
}

void VentanaXml::setAncho(int ancho){
	this->ancho = ancho;
}
int VentanaXml::getAncho(){
	return this->ancho;
}
void VentanaXml::setAlto(int alto){
	this->alto = alto;
}
int VentanaXml::getAlto(){
	return this->alto;
}
void VentanaXml::setVelocidadCamara(int velocidadCamara){
	this->velocidadCamara = velocidadCamara;
}
int VentanaXml::getVelocidadCamara(){
	return this->velocidadCamara;
}
VentanaXml & VentanaXml::operator = (const VentanaXml & source)
{
	this->ancho = source.ancho;
	this->alto = source.alto;
	this->velocidadCamara = source.velocidadCamara;
    return *this;
}
void VentanaXml::toString(TCadena1000 cadena){
	sprintf(cadena,"VentanaXml:ancho=%d,alto=%d,velocidadCamara=%d",ancho,alto,velocidadCamara);
}
