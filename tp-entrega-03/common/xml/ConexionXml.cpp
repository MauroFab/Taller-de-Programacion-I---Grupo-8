#include "ConexionXml.h"
/* @autor sabris
 */
ConexionXml::ConexionXml()
{
	strcpy(this->ip,"");
	this->puerto = -1;
}

ConexionXml::~ConexionXml()
{
}
void ConexionXml::setIp(char* ip){
	strcpy(this->ip,ip);
}
char* ConexionXml::getIp(){
	return this->ip;
}
void ConexionXml::setPuerto(int puerto){
	this->puerto = puerto;
}
int ConexionXml::getPuerto(){
	return this->puerto;
}

ConexionXml & ConexionXml::operator = (const ConexionXml & source){
	strcpy(ip ,source.ip);
	puerto = source.puerto;
    return *this;
};
