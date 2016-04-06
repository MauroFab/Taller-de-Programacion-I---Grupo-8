#include <stdio.h>
#include "tinyxml2.h"
#include "ParserXml.h"
using namespace tinyxml2;

//esta funcion realiza la carga del xml del cliente
void cargarXmlCliente(ParserXml &parserx,int argc, char* argv[]);
//CLIENTE
int main(int argc, char* argv[])
{
	printf("\nCLIENTE");
	ParserXml parserx;
//	crearXmlCliente();
	cargarXmlCliente(parserx,argc,argv);
	int res = parserx.validarXml();
	if (res < 0)
		return 0;
	//luego de la carga crea los datos a partir del XML
	ClienteXml * clienteXml = parserx.createDataClienteXml();
	system("pause");
	return 0;
}

void cargarXmlCliente(ParserXml &parserx,int argc, char* argv[]){
//	levantarXMLCliente();
//	levantarXMLServidor();
//    crearXmlServidor();
	int cantargs=argc;
	char ruta[200];
	
	if (cantargs == 2){
		strcpy(ruta, argv[1]);
	}
	else{
		printf("error, no ruta valida, ingrese ruta\n");
		scanf("%s",ruta);
	}
	printf("\n argumento %s\n", ruta);
	
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