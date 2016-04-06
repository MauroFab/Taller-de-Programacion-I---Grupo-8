#ifndef _PARSERXML_H_
#define _PARSERXML_H_
#include <stdio.h>
#include "tinyxml2.h"
using namespace tinyxml2;

#include "MensajeXml.h"
#include "ClienteXml.h"

#define MAX_PUERTO 65535
#define MIN_PUERTO 1024


class ParserXml
{
private:
	//contiene el document
	XMLDocument xmlDoc;
public:
	ParserXml();
	virtual ~ParserXml();
	int levantarXMLCliente(char * ruta);
	int readMensaje( XMLElement* elemMensaje);
	int crearXmlCliente();
	int levantarXMLServidor();
	int crearXmlServidor();
	
	//validaciones
	static int isValidIp(char * strIp);
	static int isValidInt(char * strValor);
	static int isValidDouble(char * strValor);
	static int isValidChar(char * strValor);
	static int isValidPuerto(char * strPuerto);
	static int isValidTipo(char * strTipo);
	static int isValidValor(char * strValor,int tipo);
	static int convertTipoToInt(char * strTipo);
	
	//carga de datos
	ClienteXml * createDataClienteXml();
	void createDataConexionXml(ClienteXml * clienteXml,XMLElement* elemConex);
	void createDataListMensajeXml(ClienteXml * clienteXml,XMLElement* listMensajes);
	MensajeXml * createDataMensajeXml(XMLElement* elemMensaje);
	MensajeXml * createMensajeXml(int id, int tipo,char * valor);

	//validacion de xml
	int validarXml();
	int validarClienteXml(XMLElement* elemCliente);
	int validarConexionXml(XMLElement* elemConex);
	int validarListaMensajesXml(XMLElement* listMensajes);
	int validarMensajeXml(XMLElement* elemMensaje);
	
};

#endif //_PARSERXML_H_
