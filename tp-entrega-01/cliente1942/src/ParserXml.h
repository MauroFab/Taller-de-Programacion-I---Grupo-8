#ifndef _PARSERXML_H_
#define _PARSERXML_H_
#include <stdio.h>
#include "tinyxml2.h"
using namespace tinyxml2;

#include "MensajeXml.h"
#include "ClienteXml.h"
#include "ServidorXml.h"
#include "../../common/Log.h"

#define MAX_PUERTO 65535
#define MIN_PUERTO 1024
#define MAX_RUTA 200
#define XML_DEF_SERVIDOR	"xmlDefaultServidor.xml"
#define XML_DEF_CLIENTE		"xmlDefaultCliente.xml"

class ParserXml
{
private:
	//contiene el document
	tinyxml2::XMLDocument xmlDoc;
public:
	ParserXml();
	virtual ~ParserXml();
	//CLIENTE
	int levantarXMLCliente(char * ruta);
	int crearXmlCliente();
	//esta funcion realiza la carga del xml del cliente
	void cargarXmlCliente(int argc, char* argv[]);
	//SERVIDOR
	int levantarXMLServidor(char * ruta);
	int crearXmlServidor();
	//esta funcion realiza la carga del xml del SERVIDOR
	void cargarXmlServidor(int argc, char* argv[]);
	
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
	//CLIENTE
	ClienteXml * createDataClienteXml();
	void createDataConexionXml(ClienteXml * clienteXml,XMLElement* elemConex);
	void createDataListMensajeXml(ClienteXml * clienteXml,XMLElement* listMensajes);
	MensajeXml * createDataMensajeXml(XMLElement* elemMensaje);
	MensajeXml * createMensajeXml(int id, int tipo,char * valor);
	
	//SERVIDOR
	ServidorXml * createDataServidorXml();

	//validacion de xml
	//CLIENTE
	int validarXmlArchivoCliente();
	int validarClienteXml(XMLElement* elemCliente);
	int validarConexionXml(XMLElement* elemConex);
	int validarListaMensajesXml(XMLElement* listMensajes);
	int validarMensajeXml(XMLElement* elemMensaje);
	
	//SERVIDOR
	int validarXmlArchivoServidor();
	int validarServidorXml(XMLElement* elemServidor);
	
};

#endif //_PARSERXML_H_
