#ifndef _PARSERXML_H_
#define _PARSERXML_H_
/* @autor sabris
 */
#include <stdio.h>
#include <algorithm>
#include <iterator>
#include <set>
#include <map>
#include <string>
using namespace std;
#include "tinyxml2.h"
using namespace tinyxml2;

#include "MensajeXml.h"
#include "ClienteXml.h"
#include "ServidorXml.h"
#include "../Log.h"

#define MAX_PUERTO 65535
#define MIN_PUERTO 1024
#define MAX_RUTA 200
#define XML_DEF_SERVIDOR	"xmlDefaultServidor.xml"
#define XML_DEF_CLIENTE		"xmlDefaultCliente.xml"
#define XML_DEF_SPRITE		"error.bmp"

class ParserXml
{
private:
	//contiene el document
	tinyxml2::XMLDocument xmlDoc;
	
	//mapa con los IDs de los sprites
	map<string,int> mapaSpriteIds;
	
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
	static int isValidString(char * strString);	
	static int isValidPuerto(char * strPuerto);
	static int isValidTipo(char * strTipo);
	static int isValidValor(char * strValor,int tipo);
	static int convertTipoToInt(char * strTipo);
	static int isIgualAPatronMayuscula(char * cadena,char * patronMayus);
	
	//carga de datos
	//CLIENTE
	ClienteXml * createDataClienteXml();
	void createDataConexionXml(ClienteXml * clienteXml,XMLElement* elemConex);
	void createDataListMensajeXml(ClienteXml * clienteXml,XMLElement* listMensajes);
	MensajeXml * createDataMensajeXml(XMLElement* elemMensaje);
	MensajeXml * createMensajeXml(int id, int tipo,char * valor);
	
	//SERVIDOR
	ServidorXml * createDataServidorXml();
	void createDataVentanaXml(ServidorXml *servidorXml,XMLElement* elemVentana);
	
	void createDataListSpriteXml(ServidorXml *servidorXml,XMLElement* listSprites);
	SpriteXml * createDataSpriteXml(XMLElement* elemSprite,int idxSps);
	
	void createDataListEscenariosXml(ServidorXml *servidorXml,XMLElement* listEscenarios);
	EscenarioXml * createDataEscenarioXml(XMLElement* elemEscenario,int idxEs);
	
	void createDataFondoXml(EscenarioXml *escenarioXml,XMLElement* elemFondo);	
	
	void createDataListElementosXml(EscenarioXml *escenarioXml,XMLElement* listElementos);
	ElementoXml * createDataElementoXml(XMLElement* elemE,int idxE);
	
	void createDataListAvionXml(ServidorXml *servidorXml,XMLElement* listAviones);	
	AvionXml * createDataAvionXml(XMLElement* elemAvion,int idxAvs);
	
	void createDataListEnemigoXml(EscenarioXml *escenarioXml,XMLElement* listEnemigo);	
	AvionEnemigoXml * createDataEnemigoXml(XMLElement* elemEnemigo,int idxEne);
	
	void createDataListPowerXml(EscenarioXml *escenarioXml,XMLElement* listPower);	
	PowerUpXml * createDataPowerXml(XMLElement* elemPower,int idxPow);

	int findSpriteIdByName(char * strIdSprite);
	int tipoPowerToInt(char * strTipoPow);
	int tipoEnemigoToInt(char * strTipoEne);
	int modoToint(char * modo);

	//validacion de xml
	//CLIENTE
	int validarXmlArchivoCliente();
	int validarClienteXml(XMLElement* elemCliente);
	int validarConexionXml(XMLElement* elemConex);
	int validarListaMensajesXml(XMLElement* listMensajes);
	int validarMensajeXml(XMLElement* elemMensaje,set<int> &setClaves);
	
	//SERVIDOR
	int validarXmlArchivoServidor();
	int validarServidorXml(XMLElement* elemServidor);
	int validarVentanaXml(XMLElement* elemVentana);
	int validarListaSpriteXml(XMLElement* listSprites);
	int validarSpriteXml(XMLElement* elemSprite,set<string> &setClaves);
	int validarListaEscenarioXml(XMLElement*  listEscenario);
	int validarEscenarioXml(XMLElement*  elemEscenario);
	int validarFondoXml(XMLElement* elemFondo);
	int validarListaElementosXml(XMLElement* listElementos);
	int validarElementoXml(XMLElement* elemE);
	int validarPosicionXml(XMLElement* posicion);
	int validarListaAvionXml(XMLElement* listAviones);
	int validarAvionXml(XMLElement* elemAvion);
	
	int validarListEnemigoXml(XMLElement* listEnemigo);
	int validarEnemigoXml(XMLElement* elemEnemigo);
	int validarListPowerXml(XMLElement* listPower);
	int validarPowerXml(XMLElement* elemPower);
	
	//metodo para vincular y validar entidades del servidor , se puede usar tambien del lado del cliente
	void vincularYValidarEntidades(ServidorXml *servidorXml);
	bool existeFile(char * nomFile);
	
};

#endif //_PARSERXML_H_
