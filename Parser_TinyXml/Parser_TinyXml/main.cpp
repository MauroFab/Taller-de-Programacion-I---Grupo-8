#include <stdio.h>
#include "tinyxml2.h"
#include "ParserXml.h"
using namespace tinyxml2;

//esta funcion realiza la carga del xml del cliente
void cargarXmlCliente(int argc, char* argv[]);
//CLIENTE
int main(int argc, char* argv[])
{
//	crearXmlCliente();
	cargarXmlCliente(argc,argv);
	system("pause");
	return 0;
}

void cargarXmlCliente(int argc, char* argv[]){
//	levantarXMLCliente();
//	levantarXMLServidor();
//    crearXmlServidor();
	int cantargs=argc;
//	char * ruta = new char[200]; 
	char ruta[200];
	
	if (cantargs == 2){
		strcpy(ruta, argv[1]);
	}
	else{
		printf("error, no ruta valida, ingrese ruta\n");
		scanf("%s",ruta);
	}
	printf("\n argumento %s\n", ruta);
	ParserXml parserx;
	int codErr = parserx.levantarXMLCliente(ruta);
	//si hubo error al leer, llama al xml por defecto
	if (codErr != XML_SUCCESS){
		printf("\n ERROR:el xml cliente NO fue encontrado o hubo error al intentar abrir");
		parserx.crearXmlCliente();
		printf("\n INFO:ese cargo xml por defecto del cliente");
		char * rutaDefecto = "xmlDefaultCliente.xml";
		codErr = parserx.levantarXMLCliente(rutaDefecto);
	}
	else{
		printf("\n INFO:xml cliente procesado con exito");
	}
	
}