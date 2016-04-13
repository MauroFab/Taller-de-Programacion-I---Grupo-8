#include "Protocolo.h"

Protocolo::Protocolo()
{
}

Protocolo::~Protocolo()
{
}

int Protocolo::codificar(MensajeXml &mensajeXml,char * buffer){
	int sizeBytes = mensajeXml.getSizeBytes();
	int id = mensajeXml.getId();
	int tipo = mensajeXml.getTipo();
	//ojo que aqui se copian los punteros, no se debe liberar luego (o hace el destructor)
	char * valor = mensajeXml.getValor();
	int lenValor = sizeBytes - (3*sizeof(int));
//	//aloca espacio suficiente para ESTE mensajeXML puntual, pues el size es variable
//	char *pBuf = (*buffer) = new char[sizeBytes];
	int offset = 0;
	memcpy(buffer + offset,&sizeBytes,sizeof(int));
	offset += sizeof(int);
	
	memcpy(buffer + offset,&id,sizeof(int));
	offset += sizeof(int);
	
	memcpy(buffer + offset,&tipo,sizeof(int));
	offset += sizeof(int);
	
	memcpy(buffer + offset,valor,lenValor);
	offset += lenValor;
	
	return sizeBytes;
}

int Protocolo::decodificar(char * buffer,MensajeXml *mensajeXml){
	int sizeBytes = -1;
	int id = -1;
	int tipo = -1;
	char * valor = NULL;
	int offset = 0;
	memcpy(&sizeBytes,buffer + offset,sizeof(int));
	offset += sizeof(int);
	
	memcpy(&id,buffer + offset,sizeof(int));
	offset += sizeof(int);
	
	memcpy(&tipo,buffer + offset,sizeof(int));
	offset += sizeof(int);
	
	int lenValor = sizeBytes - (3*sizeof(int));
	valor = new char[lenValor];
	memcpy(valor,buffer + offset,lenValor);
	
	mensajeXml->setId(id);
	mensajeXml->setTipo(tipo);
	mensajeXml->setValor(valor,lenValor);
	mensajeXml->calculateSizeBytes();
	
	//luego de usar el valor debe liberarlo pues no se usa mas
	delete [] valor;
	return sizeBytes;
}

int Protocolo::validarMensaje(MensajeXml& mensaje) {
	
	char* valor = mensaje.getValor();
	int tipoDato = mensaje.getTipo();

	int codigoError = ParserXml::isValidValor(valor, tipoDato);
	
	if (codigoError < 0) {

		if (tipoDato == TIPO_INT) {
			
			if (ParserXml::isValidDouble(valor) == 0) return -1;
			if (ParserXml::isValidChar(valor) == 0) return -2;
			return -3;

		} else if (tipoDato == TIPO_CHAR) {

			if (ParserXml::isValidDouble(valor) == 0) return -4;
			return -5;

		} else if (tipoDato == TIPO_DOUBLE) {

			if (ParserXml::isValidChar(valor) == 0) return -6;
			return -7;
		}
	}

	return codigoError;
}
/*
OJO no puede retornar un puntero a algo cuyo ambito finalizo, si se usa puede tirar error
char* Protocolo::informacionSobreError(int codigoError) {
	
	if (codigoError == 1) return "Error: se esperaba un (int) y se recibió un (double)";
	if (codigoError == 2) return "Error: se esperaba un (int) y se recibió un (char)";
	if (codigoError == 3) return "Error: se esperaba un (int) y se recibió un (string)";

	if (codigoError == 4) return "Error: se esperaba un (char) y se recibió un (double)";
	if (codigoError == 5) return "Error: se esperaba un (char) y se recibió un (string)";

	if (codigoError == 6) return "Error: se esperaba un (double) y se recibió un (char)";
	if (codigoError == 7) return "Error: se esperaba un (double) y se recibió un (string)";

	return "Ok: valor y tipo de dato correctos";
}

*/