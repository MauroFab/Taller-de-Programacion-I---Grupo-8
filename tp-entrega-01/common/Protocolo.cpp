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
