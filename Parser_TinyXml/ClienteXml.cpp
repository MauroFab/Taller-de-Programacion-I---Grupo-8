#include "ClienteXml.h"

ClienteXml::ClienteXml()
{
}

ClienteXml::~ClienteXml()
{
}
void ClienteXml::setConexionXmlCopy(const ConexionXml &conexionXml){
	this->conexionXml = conexionXml;
}
ConexionXml * ClienteXml::getConexionXmlCopy(){
	return &this->conexionXml;
}

void ClienteXml::addMensaje(MensajeXml * mensaje,int pos){
	this->lista[pos] = mensaje;
}

