#ifndef _CLIENTEXML_H_
#define _CLIENTEXML_H_

#include "ConexionXml.h"
#include "MensajeXml.h"

#define MAX_MENSAJES	100

class ClienteXml
{
private:
	ConexionXml conexionXml;
	//BUG-001 cambiar la lista de mensajes
	MensajeXml * lista[MAX_MENSAJES];
public:
	ClienteXml();
	virtual ~ClienteXml();
	//se copia la conexion
	void setConexionXmlCopy(const ConexionXml &conexionXml);
	ConexionXml * getConexionXmlCopy();
	void addMensaje(MensajeXml * mensaje,int pos);
};

#endif //_CLIENTEXML_H_
