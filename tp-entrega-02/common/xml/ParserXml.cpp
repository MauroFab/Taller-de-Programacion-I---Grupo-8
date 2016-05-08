#include "ParserXml.h"
/* @autor sabris
 */
ParserXml::ParserXml()
{
}

ParserXml::~ParserXml()
{
}

//-------------CLIENTE
int ParserXml::levantarXMLCliente(char * ruta)
{
//-----------------------------------------------------------------------------
// Lee un archivo xml del cliente
//-----------------------------------------------------------------------------

	xmlDoc.LoadFile(ruta);

	int codErr = xmlDoc.ErrorID();
	
	if(codErr != 0)
		printf("\n%s %d\n","codigo", xmlDoc.ErrorID());

	return codErr;
}

int ParserXml::crearXmlCliente()
{

//-----------------------------------------------------------------------------
// Crea un archivo xml por defecto para el cliente
//-----------------------------------------------------------------------------
//	XMLDocument xmlDoc;

	XMLNode * pRaiz = xmlDoc.NewElement("cliente");
	xmlDoc.InsertFirstChild(pRaiz);

	//luego del raiz cliente, sobre este se insertan nuevos elementos
	XMLElement * pConexion = xmlDoc.NewElement("conexion");
	//pConexion->SetText("abc123");
	pRaiz->InsertEndChild(pConexion);

	XMLElement * pIP = xmlDoc.NewElement("ip");
	pConexion->InsertEndChild(pIP);
	XMLText * textoIP = xmlDoc.NewText("127.0.0.1");
//para que funcione en la entreta del miercoles
//	XMLText * textoIP = xmlDoc.NewText("169.254.241.212");
	pIP->InsertEndChild(textoIP);

	XMLElement * pPuerto = xmlDoc.NewElement("puerto");
	pConexion->InsertEndChild(pPuerto);
	XMLText * textoPuerto = xmlDoc.NewText("15636");
	pPuerto->InsertEndChild(textoPuerto);


	XMLElement * pMensajes = xmlDoc.NewElement("mensajes");
	pRaiz->InsertEndChild(pMensajes);

	//mensaje 1 por defecto--es un int
	XMLElement * pMsj1 = xmlDoc.NewElement("mensaje");
	pMensajes->InsertEndChild(pMsj1);

	XMLElement * pID1 = xmlDoc.NewElement("id");
	pMsj1->InsertEndChild(pID1);
	XMLText * textoID1 = xmlDoc.NewText("101");
	pID1->InsertEndChild(textoID1);

	XMLElement * pTipo1 = xmlDoc.NewElement("tipo");
	pMsj1->InsertEndChild(pTipo1);
	XMLText * textoTipo1 = xmlDoc.NewText("INT");
	pTipo1->InsertEndChild(textoTipo1);

	XMLElement * pValor1 = xmlDoc.NewElement("valor");
	pMsj1->InsertEndChild(pValor1);
	XMLText * textoValor1 = xmlDoc.NewText("i1");
	pValor1->InsertEndChild(textoValor1);

	//mensaje 2 por defecto--es un string
	XMLElement * pMsj2 = xmlDoc.NewElement("mensaje");
	pMensajes->InsertEndChild(pMsj2);

	XMLElement * pID2 = xmlDoc.NewElement("id");
	pMsj2->InsertEndChild(pID2);
	XMLText * textoID2 = xmlDoc.NewText("102");
	pID2->InsertEndChild(textoID2);

	XMLElement * pTipo2 = xmlDoc.NewElement("tipo");
	pMsj2->InsertEndChild(pTipo2);
	XMLText * textoTipo2 = xmlDoc.NewText("STRING");
	pTipo2->InsertEndChild(textoTipo2);

	XMLElement * pValor2 = xmlDoc.NewElement("valor");
	pMsj2->InsertEndChild(pValor2);
	XMLText * textoValor2 = xmlDoc.NewText("hola mundo");
	pValor2->InsertEndChild(textoValor2);

 	//mensaje 3 por defecto--es un double
	XMLElement * pMsj3 = xmlDoc.NewElement("mensaje");
	pMensajes->InsertEndChild(pMsj3);

	XMLElement * pID3 = xmlDoc.NewElement("id");
	pMsj3->InsertEndChild(pID3);
	XMLText * textoID3 = xmlDoc.NewText("103");
	pID3->InsertEndChild(textoID3);

	XMLElement * pTipo3 = xmlDoc.NewElement("tipo");
	pMsj3->InsertEndChild(pTipo3);
	XMLText * textoTipo3 = xmlDoc.NewText("DOUBLE");
	pTipo3->InsertEndChild(textoTipo3);

	XMLElement * pValor3 = xmlDoc.NewElement("valor");
	pMsj3->InsertEndChild(pValor3);
	XMLText * textoValor3 = xmlDoc.NewText("21.00");
	pValor3->InsertEndChild(textoValor3);

    //mensaje 4 por defecto--es un char
	XMLElement * pMsj4 = xmlDoc.NewElement("mensaje");
	pMensajes->InsertEndChild(pMsj4);

	XMLElement * pID4 = xmlDoc.NewElement("id");
	pMsj4->InsertEndChild(pID4);
	XMLText * textoID4 = xmlDoc.NewText("104");
	pID4->InsertEndChild(textoID4);

	XMLElement * pTipo4 = xmlDoc.NewElement("tipo");
	pMsj4->InsertEndChild(pTipo4);
	XMLText * textoTipo4 = xmlDoc.NewText("CHAR");
	pTipo4->InsertEndChild(textoTipo4);

	XMLElement * pValor4 = xmlDoc.NewElement("valor");
	pMsj4->InsertEndChild(pValor4);
	XMLText * textoValor4 = xmlDoc.NewText("a");
	pValor4->InsertEndChild(textoValor4);


	//luego guardar el documento a un archivo XML
	//FILE * archivo = fopen("miarchi.xml","w");
	//XMLError eResult = xmlDoc.SaveFile(archivo);

	XMLError eResult = xmlDoc.SaveFile(XML_DEF_CLIENTE);

	printf("\ncod ERR= %d\n",eResult);

//   system("pause");

   return 0;
}

void ParserXml::cargarXmlCliente(int argc, char* argv[]){
//	levantarXMLCliente();
//	levantarXMLServidor();
//    crearXmlServidor();
	int cantargs=argc;
	char ruta[MAX_RUTA];

	int codErr = XML_ERROR_FILE_NOT_FOUND;
	//solo si es 2 intenta levantar sino asumo error
	if (cantargs == 2){
		strcpy(ruta, argv[1]);
		printf("\n%s %s\n", "argumento", ruta);
		codErr = this->levantarXMLCliente(ruta);
	}
	else{
		Log::getInstance()->error("La cantidad de argumentos es incorrecta, se usa archivo por default");
/*		printf("error, no ruta valida, ingrese ruta\n");
		scanf("%s",ruta);
*/
	}
	//si hubo error al leer, llama al xml por defecto
	if (codErr != XML_SUCCESS){
		//printf("\n ERROR:el xml cliente NO fue encontrado o hubo error al intentar abrir");
		Log::getInstance()->error("el xml cliente NO fue encontrado o hubo error al intentar abrir");
		if (codErr == XML_ERROR_MISMATCHED_ELEMENT)
			Log::getInstance()->error("Error de sintaxis en xml, elemento no encontrado XML_ERROR_MISMATCHED_ELEMENT");

		this->crearXmlCliente();
		printf("\n%s\n","INFO:ese cargo xml por defecto del cliente.");
		char * rutaDefecto = XML_DEF_CLIENTE;
		codErr = this->levantarXMLCliente(rutaDefecto);
	}
	else{
		printf("\n%s\n","INFO:xml cliente procesado con exito.");
	}
}
//------------SERVIDOR
int ParserXml::levantarXMLServidor(char * ruta){
	xmlDoc.LoadFile(ruta);

	int codErr = xmlDoc.ErrorID();
	
	if(codErr != 0)
		printf("\n%s %d\n","codigo",xmlDoc.ErrorID());
	
	return codErr;
}

int ParserXml::crearXmlServidor(){
//-----------------------------------------------------------------------------
// Crea un archivo xml por defecto para el servidor
//-----------------------------------------------------------------------------

	XMLDocument xmlDoc;
	XMLNode * pRaiz = xmlDoc.NewElement("servidor");
	xmlDoc.InsertFirstChild(pRaiz);

	XMLElement * pMaxCli = xmlDoc.NewElement("cantidadMaximaClientes");
	pRaiz->InsertEndChild(pMaxCli);
	XMLText * textoMaxCli = xmlDoc.NewText("7");
	pMaxCli->InsertEndChild(textoMaxCli);


	XMLElement * pPuerto = xmlDoc.NewElement("puerto");
	pRaiz->InsertEndChild(pPuerto);
	XMLText * textoPuerto = xmlDoc.NewText("15636");
	pPuerto->InsertEndChild(textoPuerto);


	XMLError eResult = xmlDoc.SaveFile(XML_DEF_SERVIDOR);
	printf("\ncod ERR= %d\n",eResult);

//	system("pause");
	return 0;
}

void ParserXml::cargarXmlServidor(int argc, char* argv[]){
	int cantargs=argc;
	char ruta[MAX_RUTA];

	int codErr = XML_ERROR_FILE_NOT_FOUND;
	if (cantargs == 2){
		strcpy(ruta, argv[1]);
		printf("\n%s %s\n", "argumento", ruta);
		codErr = this->levantarXMLServidor(ruta);
	}
	else{
		Log::getInstance()->error("La cantidad de argumentos es incorrecta, se usa archivo por default");
/*		printf("error, no ruta valida, ingrese ruta\n");
		scanf("%s",ruta);
*/
	}

	//si hubo error al leer, llama al xml por defecto
	if (codErr != XML_SUCCESS){
		printf("\n%s\n","ERROR:el xml servidor NO fue encontrado o hubo error al intentar abrir.");
		if (codErr == XML_ERROR_MISMATCHED_ELEMENT)
			printf("\n%s\n","ERROR: Error de sintaxis en xml, xml invalido.");

		this->crearXmlServidor();
		printf("\n%s\n","INFO:ese cargo xml por defecto del servidor.");
		char * rutaDefecto = XML_DEF_SERVIDOR;
		codErr = this->levantarXMLServidor(rutaDefecto);
	}
	else{
		printf("\n%s\n","INFO:xml servidor procesado con exito.");
	}
}

/*
int ParserXml::levantarXMLServidor()
{
//-----------------------------------------------------------------------------
// Lee un archivo xml del Servidor
//-----------------------------------------------------------------------------

//	XMLDocument doc;
	xmlDoc.LoadFile( "servidor.xml" );
	printf("\ncodigo %d\n",xmlDoc.ErrorID());
	XMLNode * primero = xmlDoc.FirstChild();
	//<servidor> y sobre este se obtiene el primer elemento
	//<cantidadMaximaClientes>
	XMLNode * dataMaxCli = primero->FirstChild();

	char * textoMaxCli;
	textoMaxCli= (char*) ((XMLElement*)dataMaxCli)->GetText();
	printf("\nla CantMaxCli es= <%s>\n",textoMaxCli);

	XMLNode * dataPuerto= primero->LastChild();
    char * textoPuerto;
	textoPuerto= (char*) ((XMLElement*)dataPuerto)->GetText();
	printf("\n el puerto servidor es= <%s>\n",textoPuerto);
//	system("pause");

   return 0;
}
*/


/**
 * @param strIp cadena que contiene la ip a validar
 * @return retorna 0 si es valida, o un valor <> de 0
 * si no es valida la ip
 */
int ParserXml::isValidIp(char * strIp){
	//se controla la longitud maxima
	int len = strlen(strIp);
	//no puede exceder esto
	//255.255.255.255
	// 4 + 4 + 4 + 3 = 15
	if (len > 15)
		return -1;
	//se cuentan los puntos "." exactamente 3
	int idx = 0;
	int canPoints = 0;
	int canDig = 0;
	while (idx < len){
		if (strIp[idx] == '.'){
			canDig = 0;
			canPoints++;
		}
		else
			if (isdigit(strIp[idx])){
				canDig++;
			}
			else{	//si no es un digito ni un punto, es ip invalida
				return -1;
			}
		//si excede el maximo de puntos, es ip invalida
		if (canPoints > 3)
			return -1;
		//si excede el largo de digitos, es ip invalida
		if (canDig > 3)
			return -1;
		idx++;
	}
	//si no hay 3 puntos es ip invalida
	if (canPoints != 3)
		return -1;

	//cadenas para testear los numeros
	char cadenaNum[4];
	//4 enteros
	char listNum[4] = {0,0,0,0};

	char cadena[20];
	strcpy(cadena,strIp);
	char * pFind = strtok(cadena,".");
	idx = 0;
	int canNum = 0;
	while (pFind != NULL){
		//printf ("%s\n",pFind);
		strcpy(cadenaNum,pFind);
		listNum[idx++] = atoi(cadenaNum);
		canNum++;
		pFind = strtok (NULL, ".");
	}
	if (canNum != 4)
		return -1;
	for (int i = 0; i < 4; i++) {
		if (listNum[i] > 255)
			return -1;
	}
	return 0;
}
/**
 * @param strValor valor a validar
 * @return retorna 0 si es valida, o un valor <> de 0
 * si no es valido el argumento
 */
int ParserXml::isValidInt(char * strValor){
	int len = strlen(strValor);
	int idx = 0;
	if (strValor[idx] == '-' || strValor[idx] == '+')
		idx++;
	while (idx < len){
		if (!isdigit(strValor[idx]))
			return -1;
		idx++;
	}
	return 0;
}
/**
 * @param strValor valor a validar
 * @return retorna 0 si es valida, o un valor <> de 0
 * si no es valido el argumento
 */
int ParserXml::isValidDouble(char * strValor){
	int len = strlen(strValor);
	int idx = 0;
	int canPoints = 0;
	int canDig = 0;
	int canNums = 0;
	if (strValor[idx] == '-' || strValor[idx] == '+')
		idx++;
	while (idx < len){
		if (isdigit(strValor[idx])){
			canDig++;
		}
		else{
			if (strValor[idx] == '.'){
				//si no tiene numeros antes del punto, es double invalido
				if (canDig == 0)
					return -1;
				else{	//sino se cuenta la cantidad de numeros
					canNums++;
					canDig = 0;	//se inicializa el contador de digitos
				}
				canPoints++;
			}
			else //si no es un digito ni un punto, es un caracter no admitido
				return -1;
		}
		idx++;
	}
	if (canDig > 0)		//lo ultimo que cargo son digitos
		canNums++;
	if (canNums > 2)	//si tiene mas de 2 numeros es invalido
		return -1;
	if (canPoints > 1)	//si tiene mas de un punto es invalido
		return -1;
	return 0;
}
/**
 * @param strValor valor a validar
 * @return retorna 0 si es valida, o un valor <> de 0
 * si no es valido el argumento
 */
int ParserXml::isValidChar(char * strValor){
	if (strValor == NULL)
		return -1;
	//si NO tiene un caracter, es invalido
	if (strlen(strValor) != 1)
		return -1;
	return 0;
}
/**
 * @param strString valor a validar
 * @return retorna 0 si es valida, o un valor <> de 0
 * si no es valido el argumento
 */
int ParserXml::isValidString(char * strString){
	if (strString == NULL)
		return -1;
	//si NO tiene un caracter, es invalido
	if (strlen(strString) == 0)
		return -1;
	return 0;
}
/**
 * @param strPuerto valor a validar
 * @return retorna 0 si es valida, o un valor <> de 0
 * si no es valido el argumento
 */
int ParserXml::isValidPuerto(char * strPuerto){
	int res = isValidInt(strPuerto);
	if (res != 0)
		return -1;
	int puerto = atoi(strPuerto);
	if (puerto > MAX_PUERTO || puerto < MIN_PUERTO)
		return -1;
	return 0;
}

/**
 * @param strTipo valor a validar
 * @return retorna 0 si es valida, o un valor <> de 0
 * si no es valido el argumento
 */
int ParserXml::isValidTipo(char * strTipo){
	if (isIgualAPatronMayuscula(strTipo,STR_TIPO_INT) == 0
		|| isIgualAPatronMayuscula(strTipo,STR_TIPO_DOUBLE) == 0
		|| isIgualAPatronMayuscula(strTipo,STR_TIPO_STRING) == 0
		|| isIgualAPatronMayuscula(strTipo,STR_TIPO_CHAR) == 0)
		return 0;
	return -1;
}
int ParserXml::isValidValor(char * valor,int tipo){
	switch (tipo)
	{
		case TIPO_CHAR:{
			/*if (isValidChar(valor) < 0)
				return -1;*/
			return isValidChar(valor);
		}
		break;
		case TIPO_DOUBLE:{
			/*if (isValidDouble(valor) < 0)
				return -1;*/
			return isValidDouble(valor);
		}
		break;
		case TIPO_INT:{
			/*if (isValidInt(valor) < 0)
				return -1;*/
			return isValidInt(valor);
		}
		break;
		case TIPO_STRING:{
			//TODOS los string son validos
				return 0;
		}
		break;
		default:
			return -1;
		break;
	}
	return 0;
}
/**
 * @param strTipo tipo de dato a convertir en int
 * @return retorna el tipo[int] segun la cadena recibida por parametro [char]
 */
int ParserXml::convertTipoToInt(char * strTipo){
	if (isIgualAPatronMayuscula(strTipo,STR_TIPO_INT) == 0)
		return TIPO_INT;
	else if (isIgualAPatronMayuscula(strTipo,STR_TIPO_DOUBLE) == 0)
		return TIPO_DOUBLE;
	else if (isIgualAPatronMayuscula(strTipo,STR_TIPO_STRING) == 0)
		return TIPO_STRING;
	else if (isIgualAPatronMayuscula(strTipo,STR_TIPO_CHAR) == 0)
		return TIPO_CHAR;
	return -1;
}
/**
 * @param patronMayus cadena en MAYUSCULA a comprar
 * @param cadena tira de caracteres
 */
int ParserXml::isIgualAPatronMayuscula(char * cadena,char * patronMayus){
	int res = -1;
	//convertir el 1er caracter A...Z, a..z, 0..9..cualquer ascii
	int largo = strlen(cadena);
	char * temporal = new char[largo + 1];
	for (int i = 0; i < largo ; i++){
		char carMay = 0;
		int car = cadena[i];
		//si es minuscula
		if (car >= 'a' && car <= 'z'){
			carMay = car - 32;
		}
		else
			carMay = car;
		temporal[i] = carMay;
	}
	temporal[largo] = '\0';

	//si luego de pasar a mayuscula son iguales, entonces son iguales
	if (strcmp(patronMayus,temporal) != 0)
		res = -1;
	else
		res = 0;
	delete [] temporal;

	return res;
}

/**
 * @return retorna un objeto cliente q contiene los datos desde el xml
 */
ClienteXml * ParserXml::createDataClienteXml(){
	ClienteXml * clienteXml = new ClienteXml();

	XMLNode * raiz = (XMLNode*)&xmlDoc;
	XMLElement* elemCliente = (XMLElement*)raiz->FirstChild();
	XMLElement* elemConex = (XMLElement*)elemCliente->FirstChild();
	createDataConexionXml(clienteXml,elemConex);
	XMLElement* listMensajes = (XMLElement*)elemCliente->LastChild();
	createDataListMensajeXml(clienteXml,listMensajes);

	return clienteXml;
}
/**
 * @param clienteXml cliente a modificar
 * @param elemConex objeto q contiene los datos a cargar
 * carga un objeto conexion q contiene los datos desde el xml
 */
void ParserXml::createDataConexionXml(ClienteXml * clienteXml,XMLElement* elemConex){
	XMLElement* elemIp = (XMLElement*)elemConex->FirstChild();
	char *ip = (char*)elemIp->GetText();
	XMLElement* elemPuerto = (XMLElement*)elemConex->LastChild();
	char *puerto = (char*)elemPuerto->GetText();
	ConexionXml * pConexionXml = clienteXml->getConexionXmlCopy();
	pConexionXml->setIp(ip);
	pConexionXml->setPuerto(atoi(puerto));
}
/**
 * @param clienteXml cliente a modificar
 * @param elemConex objeto q contiene los datos a cargar
 * carga un objeto listaMensajes q contiene los datos desde el xml
 */
void ParserXml::createDataListMensajeXml(ClienteXml * clienteXml,XMLElement* listMensajes){
	XMLNode * elemMensaje = NULL;
	int idxMjes = 0;
//	char * texto;
	if (!listMensajes->NoChildren()){	//si tiene al menos un hijo
		//se obtiene el 1er mensaje <mensaje>
		XMLNode * data1ErMensaje = listMensajes->FirstChild();
		//se copia el ptr del 1er mensaje a un puntero a nodo para leer luego los sgtes mjs
		elemMensaje = data1ErMensaje;
		while (elemMensaje != listMensajes->LastChild()){
			//se procesa el mensaje
//			texto = (char*) ((XMLElement*)elemMensaje)->Name();
			MensajeXml * mensa = createDataMensajeXml((XMLElement*)elemMensaje);
			clienteXml->addMensaje(mensa,idxMjes);
			//leo siguiente mensaje
			elemMensaje = elemMensaje->NextSibling();
			idxMjes++; // contador de mensajes del cliente
		}
		//leo el ultimo mensaje dado que elemMensaje es el lastchild
		MensajeXml * mensa = createDataMensajeXml((XMLElement*)elemMensaje);
		clienteXml->addMensaje(mensa,idxMjes);
	}
}
/**
 * @param elemMensaje objeto q contiene los datos a cargar
 * @return crea y retorna un objeto mensaje cargado segun el tipo que recibe
 */
MensajeXml * ParserXml::createDataMensajeXml(XMLElement* elemMensaje){
	//obtiene el ID
	XMLElement* elemID = (XMLElement*)elemMensaje->FirstChild();
	int id = atoi(elemID->GetText());
	//obtiene el TIPO
	XMLElement* elemTIPO = (XMLElement*)elemID->NextSibling();
	char * strTipo = (char *)elemTIPO->GetText();
	int tipo = convertTipoToInt(strTipo);
	//obtiene el TIPO
	XMLElement* elemVALOR = (XMLElement*)elemTIPO->NextSibling();
	char * valor = (char *)elemVALOR->GetText();
	return createMensajeXml(id,tipo,valor);
}

/**
 * @param id del mensaje
 * @param tipo del mensaje
 * @param valor a cargar
 * @return crea y retorna un objeto mensaje cargado segun el tipo que recibe
 */
MensajeXml * ParserXml::createMensajeXml(int id, int tipo,char * valor){
	MensajeXml * men = new MensajeXml(id,tipo,valor);
	/*
	switch (tipo)
	{
		case TIPO_CHAR:{
			char car = valor[0];
			men = new MensajeXml(id,tipo,valor);
		}
		break;
		case TIPO_DOUBLE:{
			double numD = atof(valor);
			men = new MensajeXml(id,tipo,valor);
		}
		break;
		case TIPO_INT:{
			int numI = atoi(valor);
			men = new MensajeXml(id,tipo,valor);
		}
		break;
		case TIPO_STRING:{
			char * cadena = valor;
			men = new MensajeXml(id,tipo,valor);
		}
		break;
		default:
			men = NULL;
		break;
	}*/
	return men;
}

ServidorXml * ParserXml::createDataServidorXml(){
	ServidorXml * servidorXml = new ServidorXml();
	XMLNode * raiz = (XMLNode*)&xmlDoc;
	XMLElement* elemServidor = (XMLElement*)raiz->FirstChild();
	XMLElement* elemCantidad = (XMLElement*)elemServidor->FirstChild();
	char *cantidad = (char*)elemCantidad->GetText();
	servidorXml->setCantidadMaximaClientes(atoi(cantidad));
	XMLElement* elemPuerto = (XMLElement*)elemCantidad->NextSibling();
	char *puerto = (char*)elemPuerto->GetText();
	servidorXml->setPuerto(atoi(puerto));
	//aqui se cargan los datos nuevos
	XMLElement* elemVentana = (XMLElement*)elemPuerto->NextSibling();
	createDataVentanaXml(servidorXml,elemVentana);
	XMLElement* listSprites = (XMLElement*)elemVentana->NextSibling();
	createDataListSpriteXml(servidorXml,listSprites);
	XMLElement* elemEscenario = (XMLElement*)listSprites->NextSibling();
	createDataEscenarioXml(servidorXml,elemEscenario);
	XMLElement* listAviones = (XMLElement*)elemEscenario->NextSibling();
	createDataListAvionXml(servidorXml,listAviones);

	return servidorXml;
}
void ParserXml::createDataVentanaXml(ServidorXml *servidorXml,XMLElement* elemVentana){
	//obtiene ANCHO
	XMLElement* elemANCHO = (XMLElement*)elemVentana->FirstChild();
	int ancho = atoi(elemANCHO->GetText());
	//obtiene el ALTO
	XMLElement* elemALTO = (XMLElement*)elemANCHO->NextSibling();
	int alto = atoi(elemALTO->GetText());
	//obtiene el VELOCIDAD
	XMLElement* elemVELOCIDAD = (XMLElement*)elemALTO->NextSibling();
	int velocidad = atoi(elemVELOCIDAD->GetText());
	VentanaXml ventanaXml(ancho,alto,velocidad);
	servidorXml->setVentanaXml(ventanaXml);
}
void ParserXml::createDataListSpriteXml(ServidorXml *servidorXml,XMLElement* listSprites){
	XMLNode * elemSprite = NULL;
	int idxSps = 0;
//	char * texto;
	if (!listSprites->NoChildren()){	//si tiene al menos un hijo
		//se obtiene el 1er mensaje <mensaje>
		XMLNode * data1ErSprite = listSprites->FirstChild();
		//se copia el ptr del 1er mensaje a un puntero a nodo para leer luego los sgtes mjs
		elemSprite = data1ErSprite;
		while (elemSprite != listSprites->LastChild()){
			//se procesa el mensaje
			SpriteXml * spriteX = createDataSpriteXml((XMLElement*)elemSprite,idxSps);
			servidorXml->addSprite(spriteX,idxSps);
			//leo siguiente mensaje
			elemSprite = elemSprite->NextSibling();
			idxSps++; // contador de mensajes del cliente
		}
		//leo el ultimo mensaje dado que elemSprite es el lastchild
		SpriteXml * spriteX = createDataSpriteXml((XMLElement*)elemSprite,idxSps);
		servidorXml->addSprite(spriteX,idxSps);
	}
}

SpriteXml * ParserXml::createDataSpriteXml(XMLElement* elemSprite,int idxSps){
	//obtiene el ID
	XMLElement* elemID = (XMLElement*)elemSprite->FirstChild();
	char * strId = (char *)elemID->GetText();
	//obtiene el PATH
	XMLElement* elemPATH = (XMLElement*)elemID->NextSibling();
	char * path = (char *)elemPATH->GetText();
	//obtiene la CANTIDAD
	XMLElement* elemCANTIDAD = (XMLElement*)elemPATH->NextSibling();
	int cantidad = atoi(elemCANTIDAD->GetText());
	//obtiene el ANCHO
	XMLElement* elemANCHO = (XMLElement*)elemCANTIDAD->NextSibling();
	int ancho = atoi(elemANCHO->GetText());
	//obtiene el ALTO
	XMLElement* elemALTO = (XMLElement*)elemANCHO->NextSibling();
	int alto = atoi(elemALTO->GetText());
	return new SpriteXml(idxSps,strId,path,cantidad,ancho,alto);
}

void ParserXml::createDataEscenarioXml(ServidorXml *servidorXml,XMLElement* elemEscenario){
	//obtiene el ANCHO
	XMLElement* elemANCHO = (XMLElement*)elemEscenario->FirstChild();
	int ancho = atoi(elemANCHO->GetText());
	//obtiene el ALTO
	XMLElement* elemALTO = (XMLElement*)elemANCHO->NextSibling();
	int alto = atoi(elemALTO->GetText());
	servidorXml->getEscenarioXmlCopy()->setAncho(ancho);
	servidorXml->getEscenarioXmlCopy()->setAlto(alto);
	//obtiene el FONDO
	XMLElement* elemFONDO = (XMLElement*)elemALTO->NextSibling();
	createDataFondoXml(servidorXml->getEscenarioXmlCopy(),elemFONDO);
	//obtiene la listaELEMENTOS
	XMLElement* listElementos = (XMLElement*)elemFONDO->NextSibling();
	createDataListElementosXml(servidorXml->getEscenarioXmlCopy(),listElementos);
}
void ParserXml::createDataFondoXml(EscenarioXml *escenarioXml,XMLElement* elemFondo){
	//obtiene ANCHO
	int idSprite = -1;
	XMLElement* elemStrSpId = (XMLElement*)elemFondo->FirstChild();
	char * strIdSprite = (char*)elemStrSpId->GetText();
	//obtiene ANCHO
	XMLElement* elemANCHO = (XMLElement*)elemStrSpId->NextSibling();
	int ancho = atoi(elemANCHO->GetText());
	//obtiene el ALTO
	XMLElement* elemALTO = (XMLElement*)elemANCHO->NextSibling();
	int alto = atoi(elemALTO->GetText());
	FondoXml fondoXml(idSprite,strIdSprite,ancho,alto);
	escenarioXml->setFondoXml(fondoXml);
}

void ParserXml::createDataListElementosXml(EscenarioXml *escenarioXml,XMLElement* listElementos){
	XMLNode * elemE = NULL;
	int idxE = 0;
//	char * texto;
	if (!listElementos->NoChildren()){	//si tiene al menos un hijo
		//se obtiene el 1er elemento <elemento>
		XMLNode * data1ErElem = listElementos->FirstChild();
		//se copia el ptr del 1er elemento a un puntero a nodo para leer luego los sgtes mjs
		elemE = data1ErElem;
		while (elemE != listElementos->LastChild()){
			//se procesa el elemento
			ElementoXml * elemX = createDataElementoXml((XMLElement*)elemE,idxE);
			escenarioXml->addElemento(elemX,idxE);
			//leo siguiente elemento
			elemE = elemE->NextSibling();
			idxE++; // contador de elementos del escenario
		}
		//leo el ultimo elemento dado que elemE es el lastchild
		ElementoXml * elemX = createDataElementoXml((XMLElement*)elemE,idxE);
		escenarioXml->addElemento(elemX,idxE);
	}
}

ElementoXml * ParserXml::createDataElementoXml(XMLElement* elemE,int idxE){
/*
			<elemento>
				<spriteId>isla</spriteId>
				<posicion>
					<x>10</x>
					<y>15</y>
				</posicion>
			</elemento>
 */
	//obtiene spriteId
	int idSprite = idxE;
	XMLElement* elemStrSpId = (XMLElement*)elemE->FirstChild();
	char * strIdSprite = (char*)elemStrSpId->GetText();
	//obtiene la posicion y luego los dos hijos
	XMLElement* elemPosicion = (XMLElement*)elemStrSpId->NextSibling();
	//obtiene la posicionX
	XMLElement* elemCoorX = (XMLElement*)elemPosicion->FirstChild();
	int coorX = atoi(elemCoorX->GetText());
	//obtiene la posicionY
	XMLElement* elemCoorY = (XMLElement*)elemCoorX->NextSibling();
	int coorY = atoi(elemCoorY->GetText());
	return new ElementoXml(idSprite,strIdSprite,coorX,coorY);

}
void ParserXml::createDataListAvionXml(ServidorXml *servidorXml,XMLElement* listAviones){
	XMLNode * elemAvion = NULL;
	int idxAvs = 0;
//	char * texto;
	if (!listAviones->NoChildren()){	//si tiene al menos un hijo
		//se obtiene el 1er mensaje <mensaje>
		XMLNode * data1ErAvion = listAviones->FirstChild();
		//se copia el ptr del 1er mensaje a un puntero a nodo para leer luego los sgtes mjs
		elemAvion = data1ErAvion;
		while (elemAvion != listAviones->LastChild()){
			//se procesa el mensaje
			AvionXml * avionX = createDataAvionXml((XMLElement*)elemAvion,idxAvs);
			servidorXml->addAvion(avionX,idxAvs);
			//leo siguiente mensaje
			elemAvion = elemAvion->NextSibling();
			idxAvs++; // contador de mensajes del cliente
		}
		//leo el ultimo mensaje dado que elemSprite es el lastchild
		AvionXml * avionX = createDataAvionXml((XMLElement*)elemAvion,idxAvs);
		servidorXml->addAvion(avionX,idxAvs);
	}
}
AvionXml * ParserXml::createDataAvionXml(XMLElement* elemAvion,int idxAvs){
/*
	<avion>
		<velocidadDesplazamiento> 10	</velocidadDesplazamiento>
		<velocidadDisparos>6</velocidadDisparos>
		<avionSpriteId>avion</avionSpriteId>
		<vueltaSpriteId>disparo</vueltaSpriteId>
		<disparosSpriteId>vuelta</disparosSpriteId>
	</avion>
 */
	//obtiene la velAvion
	XMLElement* elemVelAvion = (XMLElement*)elemAvion->FirstChild();
	int velAvion = atoi(elemVelAvion->GetText());
	//obtiene la velBala
	XMLElement* elemVelBala = (XMLElement*)elemVelAvion->NextSibling();
	int velBala = atoi(elemVelBala->GetText());
	//obtiene la strSpAvion
	int idSpAvion = idxAvs;
	XMLElement* elemStrSpAvion = (XMLElement*)elemVelBala->NextSibling();
	char * strSpAvion = (char*)elemStrSpAvion->GetText();
	//obtiene la VUELTA
	int idSpVuelta = idxAvs*100;
	XMLElement* elemVuelta = (XMLElement*)elemStrSpAvion->NextSibling();
	char * strSpVuelta = (char *)elemVuelta->GetText();
	//obtiene la BALA
	XMLElement* elemBALA = (XMLElement*)elemVuelta->NextSibling();
	int idSpBala = idxAvs*1000;
	char * strSpBala = (char *)elemBALA->GetText();
	return new AvionXml(velAvion,velBala,idSpAvion,strSpAvion,idSpVuelta,strSpVuelta,idSpBala,strSpBala);
}

int ParserXml::validarXmlArchivoCliente(){
	XMLNode * raiz = (XMLNode*)&xmlDoc;
	if (raiz->NoChildren()){
	//no existe tags
		Log::getInstance()->error("no existe tag raiz");
		return -1;
	}

	XMLElement* elemCliente = (XMLElement*)raiz->FirstChild();
	if (validarClienteXml(elemCliente) < 0)
		return -1;
	if (elemCliente->NoChildren()){
		//cliente sin hijos
		Log::getInstance()->error("existe un cliente pero no tiene tags hijos");
		return -1;
	}

	XMLElement* elemConex = (XMLElement*)elemCliente->FirstChild();
	if (validarConexionXml(elemConex) < 0)
		return -1;
	XMLElement* listMensajes = (XMLElement*)elemConex->NextSibling();
	if (validarListaMensajesXml(listMensajes) < 0)
		return -1;
	if (listMensajes != elemCliente->LastChild())
		return -1;
	if (raiz->FirstChild() != raiz->LastChild())
		return -1;
	return 0;
}
int ParserXml::validarClienteXml(XMLElement* elemCliente){
	if (elemCliente == NULL)
		return -1;
	//error en tag de cliente
	if (strcmp(elemCliente->Name(),"cliente") != 0)
		return -1;
	if (elemCliente->NoChildren())
		return -1;
	return 0;
}

int ParserXml::validarConexionXml(XMLElement* elemConex){
	if (elemConex == NULL)
		return -1;
	//error en tag de conexion
	if (strcmp(elemConex->Name(),"conexion") != 0)
		return -1;
	if (elemConex->NoChildren())
		return -1;
	XMLElement* elemIp = (XMLElement*)elemConex->FirstChild();
	//error en tag de ip
	if (strcmp(elemIp->Name(),"ip") != 0)
		return -1;
	char *ip = (char*)elemIp->GetText();
	if (isValidIp(ip) < 0)
		return -1;
	XMLElement* elemPuerto = (XMLElement*)elemIp->NextSibling();
	//error en tag de puerto
	if (strcmp(elemPuerto->Name(),"puerto") != 0)
		return -1;
	char *puerto = (char*)elemPuerto->GetText();
	if (isValidPuerto(puerto) < 0)
		return -1;
	if (elemConex->LastChild() != elemPuerto)
		return -1;
	return 0;
}
int ParserXml::validarListaMensajesXml(XMLElement* listMensajes){
	if (listMensajes == NULL)
		return -1;
	//error en tag de listMensajes
	if (strcmp(listMensajes->Name(),"mensajes") != 0)
		return -1;
	if (listMensajes->NoChildren())
		return -1;

	//set de claves para controlar unicidad
	set<int> setClaves;
	XMLNode * elemMensaje = NULL;
	//se obtiene el 1er mensaje <mensaje>
	XMLNode * data1ErMensaje = listMensajes->FirstChild();
	//se copia el ptr del 1er mensaje a un puntero a nodo para leer luego los sgtes mjs
	elemMensaje = data1ErMensaje;
	while (elemMensaje != listMensajes->LastChild()){
		//se valida el mensaje
		if ( validarMensajeXml((XMLElement*)elemMensaje,setClaves) < 0)
			return -1;
		//leo siguiente mensaje
		elemMensaje = elemMensaje->NextSibling();
	}
	//leo el ultimo mensaje dado que elemMensaje es el lastchild
	//se valida el mensaje
	if ( validarMensajeXml((XMLElement*)elemMensaje,setClaves) < 0)
		return -1;
	return 0;
}
int ParserXml::validarMensajeXml(XMLElement* elemMensaje,set<int> &setClaves){
	if (elemMensaje == NULL)
		return -1;
	//error en tag de elemMensaje
	if (strcmp(elemMensaje->Name(),"mensaje") != 0)
		return -1;
	if (elemMensaje->NoChildren())
		return -1;
	//obtiene el ID
	XMLElement* elemID = (XMLElement*)elemMensaje->FirstChild();
	if (strcmp(elemID->Name(),"id") != 0)
		return -1;
	char * id = (char*)elemID->GetText();
	if (isValidInt(id) < 0)
		return -1;
	//como es un int valido, ahora se controla si ya existe
	int idNum = atoi(elemID->GetText());
	set<int>::iterator it;
	it = setClaves.find(idNum);
	if (it == setClaves.end()){
		//no lo encontro por lo tanto se puede agregar
		setClaves.insert(idNum);
	}
	else{
		//ya existe por tanto no se agrega y tira error
		Log::getInstance()->error("el mensaje tiene un id duplicado");
		return -1;
	}
	XMLElement* elemTIPO = (XMLElement*)elemID->NextSibling();
	if (strcmp(elemTIPO->Name(),"tipo") != 0)
		return -1;
	char * tipo = (char*)elemTIPO->GetText();
	if (isValidTipo(tipo) < 0)
		return -1;
	//obtiene el TIPO
	XMLElement* elemVALOR = (XMLElement*)elemTIPO->NextSibling();
	if (strcmp(elemVALOR->Name(),"valor") != 0)
		return -1;
	if (elemMensaje->LastChild() != elemVALOR)
		return -1;
	char * valor = (char*)elemVALOR->GetText();
	int nTipo = convertTipoToInt(tipo);
	//no se valida el valor
	/*
	if (isValidValor(valor,nTipo) < 0)
		return -1;
	*/
	return 0;
}

int ParserXml::validarXmlArchivoServidor(){
	XMLNode * raiz = (XMLNode*)&xmlDoc;
	if (raiz->NoChildren())
		return -1;
	XMLElement* elemServidor = (XMLElement*)raiz->FirstChild();
	if (elemServidor->NoChildren())
		return -1;
	if (validarServidorXml(elemServidor) < 0)
		return -1;
	XMLElement* elemCantidad = (XMLElement*)elemServidor->FirstChild();
	//error en tag de cantidad
	if (strcmp(elemCantidad->Name(),"cantidadMaximaClientes") != 0)
		return -1;
	char *cantidad = (char*)elemCantidad->GetText();
	if (isValidInt(cantidad) < 0)
		return -1;
	XMLElement* elemPuerto = (XMLElement*)elemCantidad->NextSibling();
	//error en tag de puerto
	if (strcmp(elemPuerto->Name(),"puerto") != 0)
		return -1;
	char *puerto = (char*)elemPuerto->GetText();
	if (isValidPuerto(puerto) < 0)
		return -1;
	XMLElement* elemVentana =  (XMLElement*)elemPuerto->NextSibling();
	if (validarVentanaXml(elemVentana) < 0)
		return -1;
	XMLElement* listSprites =  (XMLElement*)elemVentana->NextSibling();
	if (validarListaSpriteXml(listSprites) < 0)
		return -1;
	XMLElement* escenario =  (XMLElement*)listSprites->NextSibling();
	if (validarEscenarioXml(escenario) < 0)
		return -1;
	XMLElement* listAviones =  (XMLElement*)escenario->NextSibling();
	if (validarListaAvionXml(listAviones) < 0)
		return -1;
/*
	//error en tag de ventana
	if (strcmp(elemVentana->Name(),"ventana") != 0)
		return -1;
*/
	//repetidos
	if (listAviones != elemServidor->LastChild())
		return -1;
	return 0;
}


int ParserXml::validarServidorXml(XMLElement* elemServidor){
	if (elemServidor == NULL)
		return -1;
	//error en tag de cliente
	if (strcmp(elemServidor->Name(),"servidor") != 0)
		return -1;
	if (elemServidor->NoChildren())
		return -1;
	return 0;
}

int ParserXml::validarVentanaXml(XMLElement* elemVentana){
	if (elemVentana == NULL)
		return -1;
	//error en tag de ventana
	if (strcmp(elemVentana->Name(),"ventana") != 0)
		return -1;
	if (elemVentana->NoChildren())
		return -1;
	XMLElement* elemAncho = (XMLElement*)elemVentana->FirstChild();
	//error en tag de ancho
	if (strcmp(elemAncho->Name(),"ancho") != 0)
		return -1;
	char *ancho = (char*)elemAncho->GetText();
	if (isValidInt(ancho) < 0)
		return -1;
	XMLElement* elemAlto = (XMLElement*)elemAncho->NextSibling();
	//error en tag de alto
	if (strcmp(elemAlto->Name(),"alto") != 0)
		return -1;
	char * alto = (char*)elemAlto->GetText();
	if (isValidInt(alto) < 0)
		return -1;
	XMLElement* elemVelocidad = (XMLElement*)elemAlto->NextSibling();
	//error en tag de velocidad
	if (strcmp(elemVelocidad->Name(),"velocidadCamara") != 0)
		return -1;
	char * velocidad = (char*)elemVelocidad->GetText();
	if (isValidInt(velocidad) < 0)
		return -1;
	if (elemVentana->LastChild() != elemVelocidad)
		return -1;
	return 0;
}
int ParserXml::validarListaSpriteXml(XMLElement* listSprites){
	if (listSprites == NULL)
		return -1;
	//error en tag de listSprites
	if (strcmp(listSprites->Name(),"sprites") != 0)
		return -1;
	if (listSprites->NoChildren())
		return -1;

	//set de claves para controlar unicidad
	set<string> setClaves;
	XMLNode * elemSprite = NULL;
	//se obtiene el 1er sprite <sprite>
	XMLNode * data1ErSprite = listSprites->FirstChild();
	//se copia el ptr del 1er sprite a un puntero a nodo para leer luego los sgtes mjs
	elemSprite = data1ErSprite;
	while (elemSprite != listSprites->LastChild()){
		//se valida el sprite
		if ( validarSpriteXml((XMLElement*)elemSprite,setClaves) < 0)
			return -1;
		//leo siguiente sprite
		elemSprite = elemSprite->NextSibling();
	}
	//leo el ultimo sprite dado que elemSprite es el lastchild
	//se valida el sprite
	if ( validarSpriteXml((XMLElement*)elemSprite,setClaves) < 0)
		return -1;
	return 0;
}
int ParserXml::validarSpriteXml(XMLElement* elemSprite,set<string> &setClaves){
	if (elemSprite == NULL)
		return -1;
	//error en tag de elemSprite
	if (strcmp(elemSprite->Name(),"sprite") != 0)
		return -1;
	if (elemSprite->NoChildren())
		return -1;
	//obtiene el ID
	//-------------------------------------------------
	XMLElement* elemID = (XMLElement*)elemSprite->FirstChild();
	if (strcmp(elemID->Name(),"id") != 0)
		return -1;
	char * idStr = (char*)elemID->GetText();
	if (isValidString(idStr) < 0)
		return -1;
	//como es un int valido, ahora se controla si ya existe
	set<string>::iterator it;
	it = setClaves.find(idStr);
	if (it == setClaves.end()){
		//no lo encontro por lo tanto se puede agregar
		setClaves.insert(idStr);
	}
	else{
		//ya existe por tanto no se agrega y tira error
		Log::getInstance()->error("el mensaje tiene un id duplicado");
		return -1;
	}
	//-------------------------------------------------
	//obtiene el PATH
	//-------------------------------------------------
	XMLElement* elemPATH = (XMLElement*)elemID->NextSibling();
	if (strcmp(elemPATH->Name(),"path") != 0)
		return -1;
	char * path = (char*)elemPATH->GetText();
	if (isValidString(path) < 0)
		return -1;
	//-------------------------------------------------
	//obtiene la CANTIDAD
	//-------------------------------------------------
	XMLElement* elemCANTIDAD = (XMLElement*)elemPATH->NextSibling();
	if (strcmp(elemCANTIDAD->Name(),"cantidad") != 0)
		return -1;
	char * cantidad = (char*)elemCANTIDAD->GetText();
	if (isValidInt(cantidad) < 0)
		return -1;
	//-------------------------------------------------
	//obtiene el ANCHO
	//-------------------------------------------------
	XMLElement* elemANCHO = (XMLElement*)elemCANTIDAD->NextSibling();
	if (strcmp(elemANCHO->Name(),"ancho") != 0)
		return -1;
	char * ancho = (char*)elemANCHO->GetText();
	if (isValidInt(ancho) < 0)
		return -1;
	//-------------------------------------------------
	//obtiene el ALTO
	//-------------------------------------------------
	XMLElement* elemALTO = (XMLElement*)elemANCHO->NextSibling();
	if (strcmp(elemALTO->Name(),"alto") != 0)
		return -1;
	char * alto = (char*)elemALTO->GetText();
	if (isValidInt(alto) < 0)
		return -1;
	//-------------------------------------------------
	if (elemSprite->LastChild() != elemALTO)
		return -1;
	return 0;
}
int ParserXml::validarEscenarioXml(XMLElement* elemEscenario){
	if (elemEscenario == NULL)
		return -1;
	//error en tag de escenario
	if (strcmp(elemEscenario->Name(),"escenario") != 0)
		return -1;
	if (elemEscenario->NoChildren())
		return -1;
	XMLElement* elemAncho = (XMLElement*)elemEscenario->FirstChild();
	//error en tag de ancho
	if (strcmp(elemAncho->Name(),"ancho") != 0)
		return -1;
	char *ancho = (char*)elemAncho->GetText();
	if (isValidInt(ancho) < 0)
		return -1;
	XMLElement* elemAlto = (XMLElement*)elemAncho->NextSibling();
	//error en tag de ancho
	if (strcmp(elemAlto->Name(),"alto") != 0)
		return -1;
	char * alto = (char*)elemAlto->GetText();
	if (isValidInt(alto) < 0)
		return -1;
	XMLElement* elemFondo = (XMLElement*)elemAlto->NextSibling();
	if (validarFondoXml(elemFondo) < 0)
		return -1;
	XMLElement* listElementos = (XMLElement*)elemFondo->NextSibling();
	if (validarListaElementosXml(listElementos) < 0)
		return -1;
	if (elemEscenario->LastChild() != listElementos)
		return -1;
	return 0;
}
int ParserXml::validarFondoXml(XMLElement* elemFondo){
	if (elemFondo == NULL)
		return -1;
	//error en tag de fondo
	if (strcmp(elemFondo->Name(),"fondo") != 0)
		return -1;
	if (elemFondo->NoChildren())
		return -1;
	//--------------------------------------------
	XMLElement* elemIdSprite = (XMLElement*)elemFondo->FirstChild();
	//error en tag de spriteId
	if (strcmp(elemIdSprite->Name(),"spriteId") != 0)
		return -1;
	char *sprite = (char*)elemIdSprite->GetText();
	if (isValidString(sprite) < 0)
		return -1;
	//--------------------------------------------
	XMLElement* elemAncho = (XMLElement*)elemIdSprite->NextSibling();
	//error en tag de ancho
	if (strcmp(elemAncho->Name(),"ancho") != 0)
		return -1;
	char *ancho = (char*)elemAncho->GetText();
	if (isValidInt(ancho) < 0)
		return -1;
	//--------------------------------------------
	XMLElement* elemAlto = (XMLElement*)elemAncho->NextSibling();
	//error en tag de alto
	if (strcmp(elemAlto->Name(),"alto") != 0)
		return -1;
	char * alto = (char*)elemAlto->GetText();
	if (isValidInt(alto) < 0)
		return -1;
	if (elemFondo->LastChild() != elemAlto)
		return -1;
	return 0;
}
int ParserXml::validarListaElementosXml(XMLElement* listElementos){
	if (listElementos == NULL)
		return -1;
	//error en tag de listElementos
	if (strcmp(listElementos->Name(),"elementos") != 0)
		return -1;
	if (listElementos->NoChildren())
		return -1;

	XMLNode * elemE = NULL;
	//se obtiene el 1er mensaje <mensaje>
	XMLNode * data1ErElem = listElementos->FirstChild();
	//se copia el ptr del 1er mensaje a un puntero a nodo para leer luego los sgtes mjs
	elemE = data1ErElem;
	while (elemE != listElementos->LastChild()){
		//se valida el mensaje
		if ( validarElementoXml((XMLElement*)elemE) < 0)
			return -1;
		//leo siguiente mensaje
		elemE = elemE->NextSibling();
	}
	//leo el ultimo mensaje dado que elemE es el lastchild
	//se valida el mensaje
	if ( validarElementoXml((XMLElement*)elemE) < 0)
		return -1;
	return 0;
}
int ParserXml::validarElementoXml(XMLElement* elemE){
	if (elemE == NULL)
		return -1;
	//error en tag de ventana
	if (strcmp(elemE->Name(),"elemento") != 0)
		return -1;
	if (elemE->NoChildren())
		return -1;
	//--------------------------------------------
	XMLElement* elemIdSprite = (XMLElement*)elemE->FirstChild();
	//error en tag de spriteId
	if (strcmp(elemIdSprite->Name(),"spriteId") != 0)
		return -1;
	char *sprite = (char*)elemIdSprite->GetText();
	if (isValidString(sprite) < 0)
		return -1;
	//--------------------------------------------
	XMLElement* elemPosicion = (XMLElement*)elemIdSprite->NextSibling();
	if ( validarPosicionXml((XMLElement*)elemPosicion) < 0)
		return -1;
	if (elemE->LastChild() != elemPosicion)
		return -1;
	return 0;
}
int ParserXml::validarPosicionXml(XMLElement* elemPosicion){
	if (elemPosicion == NULL)
		return -1;
	//error en tag de posicion
	if (strcmp(elemPosicion->Name(),"posicion") != 0)
		return -1;
	if (elemPosicion->NoChildren())
		return -1;
	//obtiene el X
	//-------------------------------------------------
	XMLElement* elemX = (XMLElement*)elemPosicion->FirstChild();
	if (strcmp(elemX->Name(),"x") != 0)
		return -1;
	char * x = (char*)elemX->GetText();
	if (isValidInt(x) < 0)
		return -1;
	//-------------------------------------------------
	XMLElement* elemY = (XMLElement*)elemX->NextSibling();
	if (strcmp(elemY->Name(),"y") != 0)
		return -1;
	char * y = (char*)elemY->GetText();
	if (isValidInt(y) < 0)
		return -1;

	if (elemPosicion->LastChild() != elemY)
		return -1;
	return 0;
}
int ParserXml::validarListaAvionXml(XMLElement* listAviones){
	if (listAviones == NULL)
		return -1;
	//error en tag de listAviones
	if (strcmp(listAviones->Name(),"aviones") != 0)
		return -1;
	if (listAviones->NoChildren())
		return -1;
	XMLNode * elemAvion = NULL;
	//se obtiene el 1er avion <avion>
	XMLNode * data1ErAvion = listAviones->FirstChild();
	//se copia el ptr del 1er avion a un puntero a nodo para leer luego los sgtes mjs
	elemAvion = data1ErAvion;
	while (elemAvion != listAviones->LastChild()){
		//se valida el avion
		if ( validarAvionXml((XMLElement*)elemAvion) < 0)
			return -1;
		//leo siguiente avion
		elemAvion = elemAvion->NextSibling();
	}
	//leo el ultimo avion dado que elemAvion es el lastchild
	//se valida el avion
	if ( validarAvionXml((XMLElement*)elemAvion) < 0)
		return -1;
	return 0;
}
int ParserXml::validarAvionXml(XMLElement* elemAvion){
	if (elemAvion == NULL)
		return -1;
	//error en tag de avion
	if (strcmp(elemAvion->Name(),"avion") != 0)
		return -1;
	if (elemAvion->NoChildren())
		return -1;
	//-------------------------
	XMLElement* elemVelAvion = (XMLElement*)elemAvion->FirstChild();
	//error en tag de velocidadDesplazamiento
	if (strcmp(elemVelAvion->Name(),"velocidadDesplazamiento") != 0)
		return -1;
	char *velAvion = (char*)elemVelAvion->GetText();
	if (isValidInt(velAvion) < 0)
		return -1;
	//-------------------------
	XMLElement* elemVelBala = (XMLElement*)elemVelAvion->NextSibling();
	//error en tag de velocidadDisparos
	if (strcmp(elemVelBala->Name(),"velocidadDisparos") != 0)
		return -1;
	char * velBala = (char*)elemVelBala->GetText();
	if (isValidInt(velBala) < 0)
		return -1;
	//-------------------------
	XMLElement* elemIdSprite = (XMLElement*)elemVelBala->NextSibling();
	//error en tag de spriteId
	if (strcmp(elemIdSprite->Name(),"avionSpriteId") != 0)
		return -1;
	char *sprite = (char*)elemIdSprite->GetText();
	if (isValidString(sprite) < 0)
		return -1;
	//--------------------------------------------
	XMLElement* elemVuelta = (XMLElement*)elemIdSprite->NextSibling();
	//error en tag de vueltaSpriteId
	if (strcmp(elemVuelta->Name(),"vueltaSpriteId") != 0)
		return -1;
	char *vuelta = (char*)elemVuelta->GetText();
	if (isValidString(vuelta) < 0)
		return -1;
	//--------------------------------------------
	XMLElement* elemDisparos = (XMLElement*)elemVuelta->NextSibling();
	//error en tag de vueltaSpriteId
	if (strcmp(elemDisparos->Name(),"disparosSpriteId") != 0)
		return -1;
	char *disparos = (char*)elemDisparos->GetText();
	if (isValidString(disparos) < 0)
		return -1;
	//--------------------------------------------
	if (elemAvion->LastChild() != elemDisparos)
		return -1;
	return 0;
}