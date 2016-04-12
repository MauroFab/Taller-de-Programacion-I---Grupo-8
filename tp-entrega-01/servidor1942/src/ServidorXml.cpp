#include "ServidorXml.h"

ServidorXml::ServidorXml()
{
}

ServidorXml::~ServidorXml()
{
}

void ServidorXml::setCantidadMaximaClientes(int cantidadMaximaClientes){
	this->cantidadMaximaClientes = cantidadMaximaClientes;
}
int ServidorXml::getCantidadMaximaClientes(){
	return this->cantidadMaximaClientes;
}
void ServidorXml::setPuerto(int puerto){
	this->puerto = puerto;
}
int ServidorXml::getPuerto(){
	return this->puerto;
}