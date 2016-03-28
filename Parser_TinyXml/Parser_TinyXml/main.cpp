#include <stdio.h>
#include "tinyxml2.h"
using namespace tinyxml2;
int crearXmlCliente();
int levantarXMLCliente();
int readMensaje( XMLElement* elemMensaje);
int levantarXMLServidor();
int crearXmlServidor();


int levantarXMLCliente()
{
//-----------------------------------------------------------------------------
// Lee un archivo xml del cliente	
//-----------------------------------------------------------------------------

	XMLDocument doc;
	doc.LoadFile( "cliente.xml" );
	printf("\ncodigo %d\n",doc.ErrorID());
	//luego de la carga del documento
	//se obtiene el primer elemento
	XMLNode * primero = doc.FirstChild();
	//<cliente> y sobre este se obtiene el primer elemento
	//<conexion>
	XMLNode * dataConexion = primero->FirstChild();
	
	char * textoIP;
	XMLNode * dataIP= dataConexion->FirstChild();
	textoIP = (char*) ((XMLElement*)dataIP)->GetText();
	printf("\nla ip es= <%s>\n",textoIP);

	char * textoPuerto;
	XMLNode * dataPuerto = dataConexion->LastChild();
	textoPuerto =(char*) ((XMLElement*)dataPuerto)->GetText();
	printf("\nel puerto es= <%s>\n",textoPuerto);

	int canMjes=0;
	char * texto;
	XMLNode * elemMensaje = NULL;
	//el listado de mensajes <mensajes>
	XMLNode * listMensajes = dataConexion->NextSibling();

	//se obtiene el 1er mensaje <mensaje>
	XMLNode * data1ErMensaje = listMensajes->FirstChild();
	//se copia el ptr del 1er mensaje a un puntero a nodo para leer luego los sgtes mjs
	elemMensaje = data1ErMensaje;
	while (elemMensaje != listMensajes->LastChild()){
		//se procesa el mensaje
		canMjes++; // contador de mensajes del cliente 
		texto = (char*) ((XMLElement*)elemMensaje)->Name();
		printf("\nMENSAJE= <%s>\n",texto);
		readMensaje(((XMLElement*)elemMensaje));
		//leo siguiente mensaje
		elemMensaje = elemMensaje->NextSibling();
	}
	//leo el ultimo mensaje dado que elemMensaje es el lastchild
	canMjes++;
	texto = (char*) ((XMLElement*)elemMensaje)->Name();
	printf("\nMENSAJE= <%s>",texto);
	printf("\nMENSAJE2= <%s>",((XMLElement*)elemMensaje)->GetText());
	readMensaje(((XMLElement*)elemMensaje));
	printf("\n#msjes leidos del cliente %d\n",canMjes);
	
	//return doc.ErrorID();
	system("pause");
	return 0;
} 


int readMensaje( XMLElement* elemMensaje){
	//obtiene el ID
	XMLElement* elemID = (XMLElement*)elemMensaje->FirstChild();
	printf("\ntag <%s>",elemID->Name());
	printf("\nvalue [%s]",elemID->GetText());
	//obtiene el TIPO
	XMLElement* elemTIPO = (XMLElement*)elemID->NextSibling();
	printf("\ntag <%s>",elemTIPO->Name());
	printf("\nvalue [%s]",elemTIPO->GetText());
	//obtiene el TIPO
	XMLElement* elemVALOR = (XMLElement*)elemTIPO->NextSibling();
	printf("\ntag <%s>",elemVALOR->Name());
	printf("\nvalue [%s]",elemVALOR->GetText());
	return 0;
}



int crearXmlCliente()
{

//-----------------------------------------------------------------------------
// Crea un archivo xml por defecto para el cliente
//-----------------------------------------------------------------------------

	XMLDocument xmlDoc;
	XMLNode * pRaiz = xmlDoc.NewElement("cliente");
	xmlDoc.InsertFirstChild(pRaiz);

	//luego del raiz cliente, sobre este se insertan nuevos elementos
	XMLElement * pConexion = xmlDoc.NewElement("conexion");
	//pConexion->SetText("abc123");
	pRaiz->InsertEndChild(pConexion);
	
	XMLElement * pIP = xmlDoc.NewElement("ip");
	pConexion->InsertEndChild(pIP);
	XMLText * textoIP = xmlDoc.NewText("192.168.0.1");
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
	XMLText * textoID1 = xmlDoc.NewText("mensaje1");
	pID1->InsertEndChild(textoID1);

	XMLElement * pTipo1 = xmlDoc.NewElement("tipo");
	pMsj1->InsertEndChild(pTipo1);
	XMLText * textoTipo1 = xmlDoc.NewText("int");
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
	XMLText * textoID2 = xmlDoc.NewText("mensaje2");
	pID2->InsertEndChild(textoID2);

	XMLElement * pTipo2 = xmlDoc.NewElement("tipo");
	pMsj2->InsertEndChild(pTipo2);
	XMLText * textoTipo2 = xmlDoc.NewText("string");
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
	XMLText * textoID3 = xmlDoc.NewText("mensaje3");
	pID3->InsertEndChild(textoID3);

	XMLElement * pTipo3 = xmlDoc.NewElement("tipo");
	pMsj3->InsertEndChild(pTipo3);
	XMLText * textoTipo3 = xmlDoc.NewText("double");
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
	XMLText * textoID4 = xmlDoc.NewText("mensaje4");
	pID4->InsertEndChild(textoID4);

	XMLElement * pTipo4 = xmlDoc.NewElement("tipo");
	pMsj4->InsertEndChild(pTipo4);
	XMLText * textoTipo4 = xmlDoc.NewText("char");
	pTipo4->InsertEndChild(textoTipo4);

	XMLElement * pValor4 = xmlDoc.NewElement("valor");
	pMsj4->InsertEndChild(pValor4);
	XMLText * textoValor4 = xmlDoc.NewText("a");
	pValor4->InsertEndChild(textoValor4);

		
	//luego guardar el documento a un archivo XML
	//FILE * archivo = fopen("miarchi.xml","w");
	//XMLError eResult = xmlDoc.SaveFile(archivo);

		
	XMLError eResult = xmlDoc.SaveFile("xmlDefaultCliente.xml");

	printf("\ncod ERR= %d\n",eResult);
 	  
   system("pause");
   
   return 0;
}


int levantarXMLServidor()
{
//-----------------------------------------------------------------------------
// Lee un archivo xml del Servidor	
//-----------------------------------------------------------------------------

	XMLDocument doc;
	doc.LoadFile( "servidor.xml" );
	printf("\ncodigo %d\n",doc.ErrorID());
	XMLNode * primero = doc.FirstChild();
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
	system("pause");
   
   return 0;
}

int crearXmlServidor(){
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


	XMLError eResult = xmlDoc.SaveFile("xmlDefaultServidor.xml");
	printf("\ncod ERR= %d\n",eResult);


system("pause");
return 0;
}

int main(int argc, char* argv[])
{
//	crearXmlCliente();
//	levantarXMLCliente();
//	levantarXMLServidor();
    crearXmlServidor();

	return 0;
}