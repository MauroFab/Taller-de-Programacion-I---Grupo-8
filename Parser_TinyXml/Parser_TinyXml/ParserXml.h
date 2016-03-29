#ifndef _PARSERXML_H_
#define _PARSERXML_H_
#include <stdio.h>
#include "tinyxml2.h"
using namespace tinyxml2;

class ParserXml
{
public:
	ParserXml();
	virtual ~ParserXml();
	int levantarXMLCliente(char * ruta);
	int readMensaje( XMLElement* elemMensaje);
	int crearXmlCliente();
	int levantarXMLServidor();
	int crearXmlServidor();
	
};

#endif //_PARSERXML_H_
