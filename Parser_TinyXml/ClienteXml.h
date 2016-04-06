#ifndef _CLIENTEXML_H_
#define _CLIENTEXML_H_

#include "ConexionXml.h"
#include "MensajeXml.h"

class ClienteXml
{
private:
	ConexionXml conexionXml;
	MensajeXml * lista[10];
public:
	ClienteXml();
	virtual ~ClienteXml();
	//se copia la conexion
	void setConexionXmlCopy(const ConexionXml &conexionXml);
	ConexionXml * getConexionXmlCopy();
	void addMensaje(MensajeXml * mensaje,int pos);
};

#endif //_CLIENTEXML_H_
