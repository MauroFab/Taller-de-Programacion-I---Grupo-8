#include "ClienteXml.h"

ClienteXml::ClienteXml()
{
	for (int i = 0; i < MAX_MENSAJES; i++){
		this->lista[i] = NULL;
	}
	this->canMsjs = 0;
}

ClienteXml::~ClienteXml()
{
	for (int i = 0; i < MAX_MENSAJES; i++){
		if (this->lista[i] != NULL)
			delete this->lista[i];
	}

}
void ClienteXml::setConexionXmlCopy(const ConexionXml &conexionXml){
	this->conexionXml = conexionXml;
}
ConexionXml * ClienteXml::getConexionXmlCopy(){
	return &this->conexionXml;
}

void ClienteXml::addMensaje(MensajeXml * mensaje,int pos){
	this->canMsjs++;
	this->lista[pos] = mensaje;
}

MensajeXml * * ClienteXml::getListaMensajes(){
	return this->lista;
}
int ClienteXml::getCanMsjs(){
	return this->canMsjs;
}