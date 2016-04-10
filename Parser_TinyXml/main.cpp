#include <stdio.h>
#include "tinyxml2.h"
#include "ParserXml.h"
using namespace tinyxml2;

//esta funcion realiza la carga del xml del cliente
void cargarXmlCliente(ParserXml &parserx,int argc, char* argv[]);

/**
 * @param mensajeXml mensaje que contiene los datos a convertir en tira de bytes
 * @param buffer que contiene la tira de bytes generada
 * @return retorna la cantidad de bytes usados para el buffer
 * luego se debera hacer delete [] del buffer
 */
int ejemplo_MensajeXml_TO_Buffer(MensajeXml &mensajeXml,char * buffer);
/**
 * @param buffer buffer con los bytes que contienen la representacion de cada
 * campo de un mensajeXml
 * @param mensajeXml mensaje a cargar con los campos obtenidos desde mensajeXml
 * @return retorna el size del mensaje obtenido desde el buffer
 * Por las dudas que sea requerido para el metodo que lo llama para sumar al puntero
 * y moverse al size del siguiente mensaje
 */
int ejemplo_Buffer_TO_MensajeXml(char * buffer,MensajeXml *mensajeXml);

void ejemplo_varios_mensajes();

//CLIENTE
int main(int argc, char* argv[])
{
	printf("\nCLIENTE");
	ParserXml parserx;
//	crearXmlCliente();
	cargarXmlCliente(parserx,argc,argv);
	int res = parserx.validarXml();
	if (res < 0){
		printf("\nERROR\n");
	}
	else{
		printf("\nOK\n");
	}

	//luego de la carga crea los datos a partir del XML
	ClienteXml * clienteXml = parserx.createDataClienteXml();
	
	//---------------------------------
	//PATRICIO fijate ACA
	//---------------------------------
	ejemplo_varios_mensajes();
	//---------------------------------
	//PATRICIO fijate ACA
	//---------------------------------

	
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

int ejemplo_MensajeXml_TO_Buffer(MensajeXml &mensajeXml,char * buffer){
	int sizeBytes = mensajeXml.getSizeBytes();
	int id = mensajeXml.getId();
	int tipo = mensajeXml.getTipo();
	//ojo que aqui se copian los punteros, no se debe liberar luego (o hace el destructor)
	char * valor = mensajeXml.getValor();
	int lenValor = sizeBytes - (3*sizeof(int));
//	//aloca espacio suficiente para ESTE mensajeXML puntual, pues el size es variable
//	char *pBuf = (*buffer) = new char[sizeBytes];
	int offset = 0;
	memcpy(buffer + offset,&sizeBytes,sizeof(int));
	offset += sizeof(int);
	
	memcpy(buffer + offset,&id,sizeof(int));
	offset += sizeof(int);
	
	memcpy(buffer + offset,&tipo,sizeof(int));
	offset += sizeof(int);
	
	memcpy(buffer + offset,valor,lenValor);
	offset += lenValor;
	
	return sizeBytes;
}

int ejemplo_Buffer_TO_MensajeXml(char * buffer,MensajeXml *mensajeXml){
	int sizeBytes = -1;
	int id = -1;
	int tipo = -1;
	char * valor = NULL;
	int offset = 0;
	memcpy(&sizeBytes,buffer + offset,sizeof(int));
	offset += sizeof(int);
	
	memcpy(&id,buffer + offset,sizeof(int));
	offset += sizeof(int);
	
	memcpy(&tipo,buffer + offset,sizeof(int));
	offset += sizeof(int);
	
	int lenValor = sizeBytes - (3*sizeof(int));
	valor = new char[lenValor];
	memcpy(valor,buffer + offset,lenValor);
	
	mensajeXml->setId(id);
	mensajeXml->setTipo(tipo);
	mensajeXml->setValor(valor,lenValor);
	mensajeXml->calculateSizeBytes();
	
	//luego de usar el valor debe liberarlo pues no se usa mas
	delete [] valor;
	return sizeBytes;
}

void ejemplo_varios_mensajes(){
	
	printf("\n \n \n \n \n \n \n \n \n \n \n \n \n ejemplo_varios_mensajes\n");
	//-------------------------------------
	//se crea un mensaje DUMMY solo para mostrar como el protocolo pensamos
	//que deberia tomar un mensaje y enviarlo
	//-------------------------------------
	//en el CLIENTE- BEGIN
	char* buffEnvio = NULL;
//	//aloca espacio suficiente para ESTE mensajeXML puntual, pues el size es variable
	//se crea una lista dummy solo de dos mensajes
	MensajeXml lista_de_dos[2];
	//mensaje 1
	lista_de_dos[0].setId(102);
	lista_de_dos[0].setTipo(TIPO_DOUBLE);
	lista_de_dos[0].setValor("99.55",strlen("99.55") + 1);
	//como ya cargo todos los datos y valor es un STRING (siempre)
	//se puede calcular sizeBytes
	lista_de_dos[0].calculateSizeBytes();
	
	//mensaje 2
	lista_de_dos[1].setId(305);
	lista_de_dos[1].setTipo(TIPO_INT);
	lista_de_dos[1].setValor("8X",strlen("8X") + 1);
	//como ya cargo todos los datos y valor es un STRING (siempre)
	//se puede calcular sizeBytes
	lista_de_dos[1].calculateSizeBytes();
	
	//el size total del buffer "a ser enviador  al servidor" es la suma de los 
	//size individuales de los mensajes
	int sizeBytesTotalLista = lista_de_dos[0].getSizeBytes() + lista_de_dos[1].getSizeBytes();
	
	buffEnvio = new char[sizeBytesTotalLista];	
	int offBuffer = 0;
	for (int i = 0; i<2;i++){
		///toma un mensaje y lo pasa al buffer
		int canBytesEnviarX_MENSAJE_XML = ejemplo_MensajeXml_TO_Buffer(lista_de_dos[i],buffEnvio + offBuffer);
		offBuffer += canBytesEnviarX_MENSAJE_XML;
		//cargo un mensaje en el buffer
	}
	//-------------------------------------
	//en el CLIENTE- END
	//-------------------------------------
	//ENVIO por socket
	//esto repre
	//-------------------------------------
	//en el SERVIDOR- BEGIN
	//recepcion de 2 mensajes
	MensajeXml lista_a_recibir[2];
	int offBufferRec = 0;
	int canRecxMsj = 0;
	for(int j = 0; j < 2; j++){
		canRecxMsj = ejemplo_Buffer_TO_MensajeXml(buffEnvio + offBufferRec,&lista_a_recibir[j]);
		printf("\n MSJ = %d",j);
		printf("\nsizeBytes = %d",lista_a_recibir[j].getSizeBytes());
		printf("\nid = %d",lista_a_recibir[j].getId());
		printf("\ntipo = %d",lista_a_recibir[j].getTipo());
		printf("\nvalor = %s",lista_a_recibir[j].getValor());
		MensajeXml mensaRecibido;
		offBufferRec += canRecxMsj;
	}
	//en el SERVIDOR- END
}