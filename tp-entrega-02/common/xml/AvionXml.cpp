#include "AvionXml.h"
/* @autor sabris
 */
AvionXml::AvionXml()
{
	this->sizeBytes = -1;
	this->id = -1;
	this->velAvion = -1;
	this->velBala = -1;
	this->idSpAvion = -1;
	this->strSpAvion = NULL;
	this->idSpVuelta = -1;
	this->strSpVuelta = NULL;
	this->idSpBala = -1;
	this->strSpBala = NULL;
}
AvionXml::AvionXml(int velAvion,int velBala,int idSpAvion,char * strSpAvion,int idSpVuelta,char * strSpVuelta,int idSpBala,char * strSpBala)
{
	this->sizeBytes = -1;
	this->id = -1;
	this->velAvion = velAvion;
	this->velBala = velBala;
	this->idSpAvion = idSpAvion;
	this->strSpAvion = new char[strlen(strSpAvion) + 1];
	strcpy(this->strSpAvion,strSpAvion);
	this->idSpVuelta = idSpVuelta;
	this->strSpVuelta = new char[strlen(strSpVuelta) + 1];
	strcpy(this->strSpVuelta,strSpVuelta);
	this->idSpBala = idSpBala;
	this->strSpBala = new char[strlen(strSpBala) + 1];
	strcpy(this->strSpBala,strSpBala);
}

AvionXml::~AvionXml()
{
	if (this->strSpAvion != NULL)
		delete []this->strSpAvion;
	if (this->strSpVuelta != NULL)
		delete []this->strSpVuelta;
	if (this->strSpBala != NULL)
		delete []this->strSpBala;
}
int AvionXml::getSizeBytes(){
	return this->sizeBytes;
}
/**
 * como precondicion los VALORES char* deben estar cargado, de lo contrario No se calcula
 * correctamente el sizeBytes
 * como NO existe un setSizeBytes() este lo reemplaza
 */
void AvionXml::calculateSizeBytes(){
	this->sizeBytes = sizeof(int) //sizeBytes
		+ sizeof(int)//id
		+ sizeof(int)//velAvion
		+ sizeof(int)//velBala
		+ sizeof(char)//len de strSpAvion
		+ sizeof(char)*(strlen(strSpAvion) + 1)
		+ sizeof(char)//len de strSpVuelta
		+ sizeof(char)*(strlen(strSpVuelta) + 1)
		+ sizeof(char)//len de strSpBala
		+ sizeof(char)*(strlen(strSpBala) + 1);
}
void AvionXml::setId(int id){
	this->id = id;
}
int AvionXml::getId(){
	return this->id;
}

void AvionXml::setVelAvion(int velAvion){
	this->velAvion = velAvion;
}
int AvionXml::getVelAvion(){
	return this->velAvion;
}
void AvionXml::setVelBala(int velBala){
	this->velBala = velBala;
}
int AvionXml::getVelBala(){
	return this->velBala;
}
void AvionXml::setIdSpAvion(int idSpAvion){
	this->idSpAvion = idSpAvion;
}
int AvionXml::getIdSpAvion(){
	return this->idSpAvion;
}
void AvionXml::setStrSpAvion(char * strSpAvion, int len_strSpAvion){
	this->strSpAvion = new char[len_strSpAvion + 1];
	memcpy(this->strSpAvion,strSpAvion,len_strSpAvion);
	this->strSpAvion[len_strSpAvion] = '\0';
}
char * AvionXml::getStrSpAvion(){
	return this->strSpAvion;
}
void AvionXml::setIdSpVuelta(int idSpVuelta){
	this->idSpVuelta = idSpVuelta;
}
int AvionXml::getIdSpVuelta(){
	return this->idSpVuelta;
}
void AvionXml::setStrSpVuelta(char * strSpVuelta, int len_strSpVuelta){
	this->strSpVuelta = new char[len_strSpVuelta + 1];
	memcpy(this->strSpVuelta,strSpVuelta,len_strSpVuelta);
	this->strSpVuelta[len_strSpVuelta] = '\0';
}
char * AvionXml::getStrSpVuelta(){
	return this->strSpVuelta;
}
void AvionXml::setIdSpBala(int idSpBala){
	this->idSpBala = idSpBala;
}
int AvionXml::getIdSpBala(){
	return this->idSpBala;
}
void AvionXml::setStrSpBala(char * strSpBala, int len_strSpBala){
	this->strSpBala = new char[len_strSpBala + 1];
	memcpy(this->strSpBala,strSpBala,len_strSpBala);
	this->strSpBala[len_strSpBala] = '\0';
}
char * AvionXml::getStrSpBala(){
	return this->strSpBala;
}
void AvionXml::toString(TCadena1000 cadena){
	sprintf(cadena,"AvionXml:sizeBytes=%d,id=%d,velAvion=%d,velBala=%d,idSpAvion=%d,strSpAvion=%s,idSpVuelta=%d,strSpVuelta=%s,idSpBala=%d,strSpBala=%s",
		sizeBytes,id,velAvion,velBala,idSpAvion,strSpAvion,idSpVuelta,strSpVuelta,idSpBala,strSpBala);
}
