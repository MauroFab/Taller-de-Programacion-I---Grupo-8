#ifndef _CLIENTEXML_H_
#define _CLIENTEXML_H_
/* @autor sabris
 */
#include <stdio.h>
#include <iostream>
#include <string.h>
using namespace std;

#include "ConexionXml.h"
#include "MensajeXml.h"

#define MAX_MENSAJES	300

class ClienteXml
{
private:
	ConexionXml conexionXml;
	//BUG-001 cambiar la lista de mensajes
	MensajeXml * lista[MAX_MENSAJES];
	int canMsjs;
public:
	ClienteXml();
	virtual ~ClienteXml();
	//se copia la conexion
	void setConexionXmlCopy(const ConexionXml &conexionXml);
	ConexionXml * getConexionXmlCopy();
	void addMensaje(MensajeXml * mensaje,int pos);
	//listado de punteros
	MensajeXml * * getListaMensajes();
	int getCanMsjs();
};

#endif //_CLIENTEXML_H_
