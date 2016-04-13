#include "ParserXml.h"

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
	printf("\ncodigo %d\n",xmlDoc.ErrorID());

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
		printf("\n argumento %s\n", ruta);
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
		printf("\n INFO:ese cargo xml por defecto del cliente");
		char * rutaDefecto = XML_DEF_CLIENTE;
		codErr = this->levantarXMLCliente(rutaDefecto);
	}
	else{
		printf("\n INFO:xml cliente procesado con exito");
	}
}
//------------SERVIDOR
int ParserXml::levantarXMLServidor(char * ruta){
	xmlDoc.LoadFile(ruta);

	int codErr = xmlDoc.ErrorID();
	printf("\ncodigo %d\n",xmlDoc.ErrorID());
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
		printf("\n argumento %s\n", ruta);
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
		printf("\n ERROR:el xml servidor NO fue encontrado o hubo error al intentar abrir");
		if (codErr == XML_ERROR_MISMATCHED_ELEMENT)
			printf("\nERROR: Error de sintaxis en xml, xml invalido");

		this->crearXmlServidor();
		printf("\n INFO:ese cargo xml por defecto del servidor");
		char * rutaDefecto = XML_DEF_SERVIDOR;
		codErr = this->levantarXMLServidor(rutaDefecto);
	}
	else{
		printf("\n INFO:xml servidor procesado con exito");
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
	//si NO tiene un caracter, es invalido
	if (strlen(strValor) != 1)
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
	if (strcmp(strTipo,STR_TIPO_INT) == 0
		|| strcmp(strTipo,STR_TIPO_DOUBLE) == 0
		|| strcmp(strTipo,STR_TIPO_STRING) == 0
		|| strcmp(strTipo,STR_TIPO_CHAR) == 0)
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
	if (strcmp(strTipo,STR_TIPO_INT) == 0)
		return TIPO_INT;
	else if (strcmp(strTipo,STR_TIPO_DOUBLE) == 0)
		return TIPO_DOUBLE;
	else if (strcmp(strTipo,STR_TIPO_STRING) == 0)
		return TIPO_STRING;
	else if (strcmp(strTipo,STR_TIPO_CHAR) == 0)
		return TIPO_CHAR;
	return -1;
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
			//printf("\nMENSAJE= <%s>\n",texto);
			MensajeXml * mensa = createDataMensajeXml((XMLElement*)elemMensaje);
			clienteXml->addMensaje(mensa,idxMjes);
			//leo siguiente mensaje
			elemMensaje = elemMensaje->NextSibling();
			idxMjes++; // contador de mensajes del cliente
		}
		//leo el ultimo mensaje dado que elemMensaje es el lastchild
//		texto = (char*) ((XMLElement*)elemMensaje)->Name();
		//printf("\nMENSAJE= <%s>",texto);
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
//	printf("\ntag <%s>",elemID->Name());
//	printf("\nvalue [%s]",elemID->GetText());
	int id = atoi(elemID->GetText());
	//obtiene el TIPO
	XMLElement* elemTIPO = (XMLElement*)elemID->NextSibling();
//	printf("\ntag <%s>",elemTIPO->Name());
//	printf("\nvalue [%s]",elemTIPO->GetText());
	char * strTipo = (char *)elemTIPO->GetText();
	int tipo = convertTipoToInt(strTipo);
	//obtiene el TIPO
	XMLElement* elemVALOR = (XMLElement*)elemTIPO->NextSibling();
//	printf("\ntag <%s>",elemVALOR->Name());
//	printf("\nvalue [%s]",elemVALOR->GetText());
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

	return servidorXml;
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

	//repetidos
	if (elemPuerto != elemServidor->LastChild())
		return -1;
	//
	if (raiz->FirstChild() != raiz->LastChild())
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