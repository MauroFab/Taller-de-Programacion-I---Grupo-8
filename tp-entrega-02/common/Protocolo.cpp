#include "Protocolo.h"

Protocolo::Protocolo()
{
}

Protocolo::~Protocolo()
{
}

int Protocolo::codificar(MensajeXml &mensajeXml,char * buffer){
	int sizeBytes = mensajeXml.getSizeBytes();
	int id = mensajeXml.getId();
	int tipo = mensajeXml.getTipo();
	//ojo que aqui se copian los punteros, no se debe liberar luego (o hace el destructor)
	char * valor = mensajeXml.getValor();
	char lenValor = strlen(mensajeXml.getValor());
	int offset = 0;
	memcpy(buffer + offset,&sizeBytes,sizeof(int));
	offset += sizeof(int);
	
	memcpy(buffer + offset,&id,sizeof(int));
	offset += sizeof(int);
	
	memcpy(buffer + offset,&tipo,sizeof(int));
	offset += sizeof(int);
	
	memcpy(buffer + offset,&lenValor,sizeof(char));
	offset += sizeof(char);
	
	memcpy(buffer + offset,valor,lenValor);
	offset += lenValor;
#ifdef FAKE_DEBUG_PROTO
	TCadena1000 cadena;
	mensajeXml.toString(cadena);
	printf("%s\n",cadena);		
#endif	
	return offset;
}

int Protocolo::decodificar(char * buffer,MensajeXml *mensajeXml){
	int sizeBytes = -1;
	int id = -1;
	int tipo = -1;
	char * valor = NULL;
	char lenValor = -1;
	int offset = 0;
	memcpy(&sizeBytes,buffer + offset,sizeof(int));
	offset += sizeof(int);
	
	memcpy(&id,buffer + offset,sizeof(int));
	offset += sizeof(int);
	
	memcpy(&tipo,buffer + offset,sizeof(int));
	offset += sizeof(int);
	
	memcpy(&lenValor,buffer + offset,sizeof(char));
	offset += sizeof(char);
	
	valor = new char[lenValor +1];
	memcpy(valor,buffer + offset,lenValor);
	offset += lenValor;
	//solo para string
//	if (tipo == TIPO_STRING)
	valor[lenValor] = '\0';
	
	mensajeXml->setId(id);
	mensajeXml->setTipo(tipo);
	mensajeXml->setValor(valor,lenValor);
	mensajeXml->calculateSizeBytes();
#ifdef FAKE_DEBUG_PROTO
	TCadena1000 cadena;
	mensajeXml->toString(cadena);
	printf("%s\n",cadena);	
#endif
	delete [] valor;
	return offset;
}

int Protocolo::validarMensaje(MensajeXml& mensaje) {
	
	char* valor = mensaje.getValor();
	int tipoDato = mensaje.getTipo();

	int codigoError = ParserXml::isValidValor(valor, tipoDato);
	
	if (codigoError < 0) {

		if (tipoDato == TIPO_INT) {
			
			if (ParserXml::isValidDouble(valor) == 0) return -1;
			if (ParserXml::isValidChar(valor) == 0) return -2;
			return -3;

		} else if (tipoDato == TIPO_CHAR) {

			if (ParserXml::isValidDouble(valor) == 0) return -4;
			return -5;

		} else if (tipoDato == TIPO_DOUBLE) {

			if (ParserXml::isValidChar(valor) == 0) return -6;
			return -7;
		}
	}

	return codigoError;
}
/*
OJO no puede retornar un puntero a algo cuyo ambito finalizo, si se usa puede tirar error
char* Protocolo::informacionSobreError(int codigoError) {
	
	if (codigoError == 1) return "Error: se esperaba un (int) y se recibió un (double)";
	if (codigoError == 2) return "Error: se esperaba un (int) y se recibió un (char)";
	if (codigoError == 3) return "Error: se esperaba un (int) y se recibió un (string)";

	if (codigoError == 4) return "Error: se esperaba un (char) y se recibió un (double)";
	if (codigoError == 5) return "Error: se esperaba un (char) y se recibió un (string)";

	if (codigoError == 6) return "Error: se esperaba un (double) y se recibió un (char)";
	if (codigoError == 7) return "Error: se esperaba un (double) y se recibió un (string)";

	return "Ok: valor y tipo de dato correctos";
}

*/
int Protocolo::codificar(SpriteXml &spriteXml,char * buffer){
	int sizeBytes = spriteXml.getSizeBytes();
	int id = spriteXml.getId();
	char * strId = spriteXml.getStrId();//ojo que aqui se copian los punteros, no se debe liberar luego (lo hace el destructor)
	char len_strId = strlen(strId);
	char * path = spriteXml.getPath();
	char len_path = strlen(path);
	int cantidad = spriteXml.getCantidad();
	int ancho = spriteXml.getAncho();
	int alto = spriteXml.getAncho();
	//aloca espacio suficiente para ESTE SpriteXml puntual, pues el size es variable
	int offset = 0;
	memcpy(buffer + offset,&sizeBytes,sizeof(int));
	offset += sizeof(int);
	
	memcpy(buffer + offset,&id,sizeof(int));
	offset += sizeof(int);
	
	memcpy(buffer + offset,&len_strId,sizeof(char));
	offset += sizeof(char);
	
	memcpy(buffer + offset,strId,len_strId);
	offset += len_strId;
	
	memcpy(buffer + offset,&len_path,sizeof(char));
	offset += sizeof(char);
	
	memcpy(buffer + offset,path,len_path);
	offset += len_path;	

	memcpy(buffer + offset,&cantidad,sizeof(int));
	offset += sizeof(int);

	memcpy(buffer + offset,&ancho,sizeof(int));
	offset += sizeof(int);
		
	memcpy(buffer + offset,&alto,sizeof(int));
	offset += sizeof(int);

#ifdef FAKE_DEBUG_PROTO
	TCadena1000 cadena;
	spriteXml.toString(cadena);
	printf("%s\n",cadena);
#endif
	return offset;
}
int Protocolo::decodificar(char * buffer,SpriteXml *spriteXml){
	int sizeBytes = -1;
	int id = -1;
	char strId[MAX_CADENA] = {0};
	char len_strId = -1;
	char path[MAX_CADENA] = {0};
	char len_path = -1;
	int cantidad = -1;
	int ancho = -1;
	int alto = -1;
	int offset = 0;
	memcpy(&sizeBytes,buffer + offset,sizeof(int));
	offset += sizeof(int);
	
	memcpy(&id,buffer + offset,sizeof(int));
	offset += sizeof(int);
	
	memcpy(&len_strId,buffer + offset,sizeof(char));
	offset += sizeof(char);
	
	memcpy(strId,buffer + offset,len_strId);
	offset += len_strId;
	strId[len_strId] = '\0';
	
	memcpy(&len_path,buffer + offset,sizeof(char));
	offset += sizeof(char);
	
	memcpy(path,buffer + offset,len_path);
	offset += len_path;
	path[len_path] = '\0';	
	
	memcpy(&cantidad,buffer + offset,sizeof(int));
	offset += sizeof(int);
	
	memcpy(&ancho,buffer + offset,sizeof(int));
	offset += sizeof(int);
	
	memcpy(&alto,buffer + offset,sizeof(int));
	offset += sizeof(int);
	
	spriteXml->setId(id);
	spriteXml->setStrId(strId,len_strId);
	spriteXml->setPath(path,len_path);
	spriteXml->setCantidad(cantidad);
	spriteXml->setAncho(ancho);
	spriteXml->setAlto(alto);
	spriteXml->calculateSizeBytes();
#ifdef FAKE_DEBUG_PROTO
	TCadena1000 cadena;
	spriteXml->toString(cadena);
	printf("%s\n",cadena);	
#endif
	return offset;
}
int Protocolo::codificar(AvionXml &avionXml,char * buffer){
	int sizeBytes = avionXml.getSizeBytes();
	int id = avionXml.getId();
	int velAvion = avionXml.getVelAvion();
	int velBala = avionXml.getVelBala();
	int idSpAvion = avionXml.getIdSpAvion();
	char * strSpAvion = avionXml.getStrSpAvion();
	char len_strSpAvion = strlen(strSpAvion);
	int idSpVuelta = avionXml.getIdSpVuelta();
	char * strSpVuelta = avionXml.getStrSpVuelta();
	char len_strSpVuelta = strlen(strSpVuelta);
	int idSpBala = avionXml.getIdSpBala();
	char * strSpBala = avionXml.getStrSpBala();
	char len_strSpBala = strlen(strSpBala);
	
	//aloca espacio suficiente para ESTE AvionXml puntual, pues el size es variable
	int offset = 0;
	memcpy(buffer + offset,&sizeBytes,sizeof(int));
	offset += sizeof(int);
	
	memcpy(buffer + offset,&id,sizeof(int));
	offset += sizeof(int);
	
	memcpy(buffer + offset,&velAvion,sizeof(int));
	offset += sizeof(int);
	
	memcpy(buffer + offset,&velBala,sizeof(int));
	offset += sizeof(int);
	
	memcpy(buffer + offset,&idSpAvion,sizeof(int));
	offset += sizeof(int);
	
	memcpy(buffer + offset,&len_strSpAvion,sizeof(char));
	offset += sizeof(char);
	
	memcpy(buffer + offset,strSpAvion,len_strSpAvion);
	offset += len_strSpAvion;
	
	memcpy(buffer + offset,&idSpVuelta,sizeof(int));
	offset += sizeof(int);
	
	memcpy(buffer + offset,&len_strSpVuelta,sizeof(char));
	offset += sizeof(char);
	
	memcpy(buffer + offset,strSpVuelta,len_strSpVuelta);
	offset += len_strSpVuelta;
	
	memcpy(buffer + offset,&idSpBala,sizeof(int));
	offset += sizeof(int);
	
	memcpy(buffer + offset,&len_strSpBala,sizeof(char));
	offset += sizeof(char);
	
	memcpy(buffer + offset,strSpBala,len_strSpBala);
	offset += len_strSpBala;

#ifdef FAKE_DEBUG_PROTO
	TCadena1000 cadena;
	avionXml.toString(cadena);
	printf("%s\n",cadena);
#endif
	return offset;
}
int Protocolo::decodificar(char * buffer,AvionXml *avionXml){
	int sizeBytes = -1;
	int id = -1;
	int velAvion = -1;
	int velBala = -1;
	int idSpAvion = -1;
	char strSpAvion[MAX_CADENA] = {0};
	char len_strSpAvion = -1;
	int idSpVuelta = -1;
	char strSpVuelta[MAX_CADENA] = {0};
	char len_strSpVuelta = -1;
	int idSpBala = -1;
	char strSpBala[MAX_CADENA] = {0};
	char len_strSpBala = -1;
	int offset = 0;
	memcpy(&sizeBytes,buffer + offset,sizeof(int));
	offset += sizeof(int);
	
	memcpy(&id,buffer + offset,sizeof(int));
	offset += sizeof(int);
	
	memcpy(&velAvion,buffer + offset,sizeof(int));
	offset += sizeof(int);

	memcpy(&velBala,buffer + offset,sizeof(int));
	offset += sizeof(int);
	
	memcpy(&idSpAvion,buffer + offset,sizeof(int));
	offset += sizeof(int);
	
	memcpy(&len_strSpAvion,buffer + offset,sizeof(char));
	offset += sizeof(char);
	
	memcpy(strSpAvion,buffer + offset,len_strSpAvion);
	offset += len_strSpAvion;
	strSpAvion[len_strSpAvion] = '\0';

	memcpy(&idSpVuelta,buffer + offset,sizeof(int));
	offset += sizeof(int);
	
	memcpy(&len_strSpVuelta,buffer + offset,sizeof(char));
	offset += sizeof(char);
	
	memcpy(strSpVuelta,buffer + offset,len_strSpVuelta);
	offset += len_strSpVuelta;
	strSpVuelta[len_strSpVuelta] = '\0';
	
	memcpy(&idSpBala,buffer + offset,sizeof(int));
	offset += sizeof(int);
	
	memcpy(&len_strSpBala,buffer + offset,sizeof(char));
	offset += sizeof(char);
	
	memcpy(strSpBala,buffer + offset,len_strSpBala);
	offset += len_strSpBala;
	strSpBala[len_strSpBala] = '\0';
	
	avionXml->setId(id);
	avionXml->setVelAvion(velAvion);
	avionXml->setVelBala(velBala);
	avionXml->setIdSpAvion(idSpAvion);
	avionXml->setStrSpAvion(strSpAvion,len_strSpAvion);
	avionXml->setIdSpVuelta(idSpVuelta);
	avionXml->setStrSpVuelta(strSpVuelta,len_strSpVuelta);
	avionXml->setIdSpBala(idSpBala);
	avionXml->setStrSpBala(strSpBala,len_strSpBala);
	avionXml->calculateSizeBytes();

#ifdef FAKE_DEBUG_PROTO
	TCadena1000 cadena;
	avionXml->toString(cadena);
	printf("%s\n",cadena);		
#endif
	return offset;
}

int Protocolo::codificar(ElementoXml &elementoXml,char * buffer){
	int sizeBytes = elementoXml.getSizeBytes();
	int id = elementoXml.getId();
	int idSprite = elementoXml.getIdSprite();
	char * strIdSprite = elementoXml.getStrIdSprite();
	char len_strIdSprite = strlen(strIdSprite);
	int posicion_x = elementoXml.getPosicion().coorX;
	int posicion_y = elementoXml.getPosicion().coorY;
	
	//aloca espacio suficiente para ESTE AvionXml puntual, pues el size es variable
	int offset = 0;
	memcpy(buffer + offset,&sizeBytes,sizeof(int));
	offset += sizeof(int);
	
	memcpy(buffer + offset,&id,sizeof(int));
	offset += sizeof(int);
	
	memcpy(buffer + offset,&idSprite,sizeof(int));
	offset += sizeof(int);
	
	memcpy(buffer + offset,&len_strIdSprite,sizeof(char));
	offset += sizeof(char);
	
	memcpy(buffer + offset,strIdSprite,len_strIdSprite);
	offset += len_strIdSprite;
	
	memcpy(buffer + offset,&posicion_x,sizeof(int));
	offset += sizeof(int);
	
	memcpy(buffer + offset,&posicion_y,sizeof(int));
	offset += sizeof(int);

#ifdef FAKE_DEBUG_PROTO
	TCadena1000 cadena;
	elementoXml.toString(cadena);
	printf("%s\n",cadena);		
#endif
	return offset;
}
int Protocolo::decodificar(char * buffer,ElementoXml *elementoXml){
	int sizeBytes = -1;
	int id = -1;
	int idSprite = -1;
	char strIdSprite[MAX_CADENA] = {0};
	char len_strIdSprite = -1;
	TPosicion posicion;
	posicion.coorX = -1;
	posicion.coorY = -1;
	int offset = 0;
	memcpy(&sizeBytes,buffer + offset,sizeof(int));
	offset += sizeof(int);
	
	memcpy(&id,buffer + offset,sizeof(int));
	offset += sizeof(int);
	
	memcpy(&idSprite,buffer + offset,sizeof(int));
	offset += sizeof(int);
	
	memcpy(&len_strIdSprite,buffer + offset,sizeof(char));
	offset += sizeof(char);
	
	memcpy(strIdSprite,buffer + offset,len_strIdSprite);
	offset += len_strIdSprite;
	strIdSprite[len_strIdSprite] = '\0';
	
	memcpy(&(posicion.coorX),buffer + offset,sizeof(int));
	offset += sizeof(int);	
	
	memcpy(&(posicion.coorY),buffer + offset,sizeof(int));
	offset += sizeof(int);	
	
	elementoXml->setId(id);
	elementoXml->setIdSprite(idSprite);
	elementoXml->setStrIdSprite(strIdSprite,len_strIdSprite);
	elementoXml->setPosicion(posicion);
	elementoXml->calculateSizeBytes();
#ifdef FAKE_DEBUG_PROTO
	TCadena1000 cadena;
	elementoXml->toString(cadena);
	printf("%s\n",cadena);	
#endif
	return offset;
}

int Protocolo::codificar(FondoXml &fondoXml,char * buffer){
	int sizeBytes = fondoXml.getSizeBytes();
	int id = fondoXml.getId();
	char * strIdSprite = fondoXml.getStrIdSprite();
	char len_strIdSprite = strlen(strIdSprite);
	int ancho = fondoXml.getAncho();
	int alto = fondoXml.getAlto();
	
	int offset = 0;
	memcpy(buffer + offset,&sizeBytes,sizeof(int));
	offset += sizeof(int);
	
	memcpy(buffer + offset,&id,sizeof(int));
	offset += sizeof(int);
	
	memcpy(buffer + offset,&len_strIdSprite,sizeof(char));
	offset += sizeof(char);
	
	memcpy(buffer + offset,strIdSprite,len_strIdSprite);
	offset += len_strIdSprite;
	
	memcpy(buffer + offset,&ancho,sizeof(int));
	offset += sizeof(int);
	
	memcpy(buffer + offset,&alto,sizeof(int));
	offset += sizeof(int);

#ifdef FAKE_DEBUG_PROTO
	TCadena1000 cadena;
	fondoXml.toString(cadena);
	printf("%s\n",cadena);	
#endif
	return offset;	
}
int Protocolo::decodificar(char * buffer,FondoXml *fondoXml){
	int sizeBytes = -1;
	int id = -1;
	char strIdSprite[MAX_CADENA] = {0};
	char len_strIdSprite = -1;
	int ancho = -1;
	int alto = -1;
	int offset = 0;
	memcpy(&sizeBytes,buffer + offset,sizeof(int));
	offset += sizeof(int);
	
	memcpy(&id,buffer + offset,sizeof(int));
	offset += sizeof(int);
	
	memcpy(&len_strIdSprite,buffer + offset,sizeof(char));
	offset += sizeof(char);
	
	memcpy(strIdSprite,buffer + offset,len_strIdSprite);
	offset += len_strIdSprite;
	strIdSprite[len_strIdSprite] = '\0';
	
	memcpy(&ancho,buffer + offset,sizeof(int));
	offset += sizeof(int);	
	
	memcpy(&alto,buffer + offset,sizeof(int));
	offset += sizeof(int);	
	
	fondoXml->setId(id);
	fondoXml->setStrIdSprite(strIdSprite,len_strIdSprite);
	fondoXml->setAncho(ancho);
	fondoXml->setAlto(alto);
	fondoXml->calculateSizeBytes();

#ifdef FAKE_DEBUG_PROTO
	TCadena1000 cadena;
	fondoXml->toString(cadena);
	printf("%s\n",cadena);		
#endif
	return offset;
}

int Protocolo::codificar(VentanaXml &ventanaXml,char * buffer){
	int sizeBytes = ventanaXml.getSizeBytes();
	int id = ventanaXml.getId();
	int ancho = ventanaXml.getAncho(); 
	int alto = ventanaXml.getAlto(); 
	int velocidadCamara = ventanaXml.getVelocidadCamara();
	int offset = 0;

	memcpy(buffer + offset,&sizeBytes,sizeof(int));
	offset += sizeof(int);
	
	memcpy(buffer + offset,&id,sizeof(int));
	offset += sizeof(int);
	
	memcpy(buffer + offset,&ancho,sizeof(int));
	offset += sizeof(int);
	
	memcpy(buffer + offset,&alto,sizeof(int));
	offset += sizeof(int);
	
	memcpy(buffer + offset,&velocidadCamara,sizeof(int));
	offset += sizeof(int);
#ifdef FAKE_DEBUG_PROTO
	TCadena1000 cadena;
	ventanaXml.toString(cadena);
	printf("%s\n",cadena);
#endif
	return offset;
}

int Protocolo::decodificar(char * buffer,VentanaXml *ventanaXml){
	int sizeBytes = -1;
	int id = -1;
	int ancho = -1;
	int alto = -1;
	int velocidadCamara = -1;
	int offset = 0;
	memcpy(&sizeBytes,buffer + offset,sizeof(int));
	offset += sizeof(int);
	
	memcpy(&id,buffer + offset,sizeof(int));
	offset += sizeof(int);
	
	memcpy(&ancho,buffer + offset,sizeof(int));
	offset += sizeof(int);
	
	memcpy(&alto,buffer + offset,sizeof(int));
	offset += sizeof(int);
	
	memcpy(&velocidadCamara,buffer + offset,sizeof(int));
	offset += sizeof(int);
	
	ventanaXml->setId(id);
	ventanaXml->setAncho(ancho);
	ventanaXml->setAlto(alto);
	ventanaXml->setVelocidadCamara(velocidadCamara);
	ventanaXml->calculateSizeBytes();

#ifdef FAKE_DEBUG_PROTO
	TCadena1000 cadena;
	ventanaXml->toString(cadena);
	printf("%s\n",cadena);		
#endif
	return offset;
}

int Protocolo::codificar(EscenarioXml &escenarioXml,char * buffer){
	int sizeBytes = escenarioXml.getSizeBytes();
	int id = escenarioXml.getId();
	int ancho = escenarioXml.getAncho(); 
	int alto = escenarioXml.getAlto(); 
	int canElems = escenarioXml.getCanElems();
	int offset = 0;

	memcpy(buffer + offset,&sizeBytes,sizeof(int));
	offset += sizeof(int);
	
	memcpy(buffer + offset,&id,sizeof(int));
	offset += sizeof(int);
	
	memcpy(buffer + offset,&ancho,sizeof(int));
	offset += sizeof(int);
	
	memcpy(buffer + offset,&alto,sizeof(int));
	offset += sizeof(int);
	//-----------
	offset += codificar(*escenarioXml.getFondoXmlCopy(),buffer + offset);
	//-----------	
	memcpy(buffer + offset,&canElems,sizeof(int));
	offset += sizeof(int);
	for (int idx = 0; idx<canElems;idx++){
		ElementoXml * elem = escenarioXml.getListaElementos()[idx];
		offset += codificar(*elem,buffer + offset);
	}
#ifdef FAKE_DEBUG_PROTO
	TCadena1000 cadena;
	escenarioXml.toString(cadena);
	printf("%s\n",cadena);		
#endif
	return offset;

}
int Protocolo::decodificar(char * buffer,EscenarioXml *escenarioXml){
	int sizeBytes = -1;
	int id = -1;
	int ancho = -1;
	int alto = -1;
	int canElems = -1;
	int offset = 0;
	memcpy(&sizeBytes,buffer + offset,sizeof(int));
	offset += sizeof(int);
	
	memcpy(&id,buffer + offset,sizeof(int));
	offset += sizeof(int);
	
	memcpy(&ancho,buffer + offset,sizeof(int));
	offset += sizeof(int);
	
	memcpy(&alto,buffer + offset,sizeof(int));
	offset += sizeof(int);
		
	escenarioXml->setId(id);
	escenarioXml->setAncho(ancho);
	escenarioXml->setAlto(alto);

	//-----------
	FondoXml fondoXml;
	offset += decodificar(buffer + offset,&fondoXml);
	escenarioXml->setFondoXml(fondoXml);
	//-----------	
	
	// Muevo el canElems
	memcpy(&canElems,buffer + offset,sizeof(int));
	offset += sizeof(int);

	for (int idx = 0; idx < canElems;idx++){
		ElementoXml * elem = new ElementoXml();
		offset += decodificar(buffer + offset,elem);
		escenarioXml->addElemento(elem,idx);
	}
	//-----------	
	escenarioXml->calculateSizeBytes();

#ifdef FAKE_DEBUG_PROTO
	TCadena1000 cadena;
	escenarioXml->toString(cadena);
	printf("%s\n",cadena);	
#endif
	return offset;
}

int Protocolo::codificar(ServidorXml &servidorXml,char * buffer){
	int sizeBytes = servidorXml.getSizeBytes();
	int id = servidorXml.getId();
	int cantidadMaximaClientes = servidorXml.getCantidadMaximaClientes();
	int puerto = servidorXml.getPuerto();
	int canSprs = servidorXml.getCanSprs(); 
	int canAvs = servidorXml.getCanAvs(); 
	int offset = 0;

	memcpy(buffer + offset,&sizeBytes,sizeof(int));
	offset += sizeof(int);
	
	memcpy(buffer + offset,&id,sizeof(int));
	offset += sizeof(int);
	
	memcpy(buffer + offset,&cantidadMaximaClientes,sizeof(int));
	offset += sizeof(int);
	
	memcpy(buffer + offset,&puerto,sizeof(int));
	offset += sizeof(int);
	//-----------
	offset += codificar(*servidorXml.getVentanaXmlCopy(),buffer + offset);
	//-----------
	offset += codificar(*servidorXml.getEscenarioXmlCopy(),buffer + offset);
	//-----------
	memcpy(buffer + offset,&canSprs,sizeof(int));
	offset += sizeof(int);
	for (int idx = 0; idx<canSprs;idx++){
		SpriteXml * sprX = servidorXml.getListaSprites()[idx];
		offset += codificar(*sprX,buffer + offset);
	}
	//-----------
	memcpy(buffer + offset,&canAvs,sizeof(int));
	offset += sizeof(int);
	for (int idx = 0; idx<canAvs;idx++){
		AvionXml * avX = servidorXml.getListaAviones()[idx];
		offset += codificar(*avX,buffer + offset);
	}
	//-----------

#ifdef FAKE_DEBUG_PROTO
	TCadena1000 cadena;
	servidorXml.toString(cadena);
	printf("%s\n",cadena);	
#endif
	return offset;
}
int Protocolo::decodificar(char * buffer,ServidorXml *servidorXml){
	int sizeBytes = -1;
	int id = -1;
	int cantidadMaximaClientes = -1;
	int puerto = -1;
	int canSprs = -1;
	int canAvs = -1;
	int offset = 0;
	memcpy(&sizeBytes,buffer + offset,sizeof(int));
	offset += sizeof(int);
	
	memcpy(&id,buffer + offset,sizeof(int));
	offset += sizeof(int);
	
	memcpy(&cantidadMaximaClientes,buffer + offset,sizeof(int));
	offset += sizeof(int);
	
	memcpy(&puerto,buffer + offset,sizeof(int));
	offset += sizeof(int);
	//-----------
	VentanaXml ventanaXml;
	offset += decodificar(buffer + offset,&ventanaXml);
	servidorXml->setVentanaXml(ventanaXml);
	//-----------
	EscenarioXml escenarioXml;
	offset += decodificar(buffer + offset,&escenarioXml);
	servidorXml->setEscenarioXml(escenarioXml);
	//-----------
	memcpy(&canSprs,buffer + offset,sizeof(int));
	offset += sizeof(int);
	for (int idx = 0; idx < canSprs;idx++){
		SpriteXml * sprX = new SpriteXml();
		offset += decodificar(buffer + offset,sprX);
		servidorXml->addSprite(sprX,idx);
	}
	//-----------	
	memcpy(&canAvs,buffer + offset,sizeof(int));
	offset += sizeof(int);
	for (int idx = 0; idx < canAvs;idx++){
		AvionXml * avX = new AvionXml();
		offset += decodificar(buffer + offset,avX);
		servidorXml->addAvion(avX,idx);
	}
	//-----------	
	servidorXml->setId(id);
	servidorXml->setCantidadMaximaClientes(cantidadMaximaClientes);
	servidorXml->setPuerto(puerto);
	servidorXml->calculateSizeBytes();
#ifdef FAKE_DEBUG_PROTO
	TCadena1000 cadena;
	servidorXml->toString(cadena);
	printf("%s\n",cadena);
#endif
	return offset;
}
	
int Protocolo::codificar(EstadoAvionXml &estadoAvionXml,char * buffer){

	int sizeBytes = estadoAvionXml.getSizeBytes();
	int id = estadoAvionXml.getId();
	int frame = estadoAvionXml.getFrame(); 
	int posX = estadoAvionXml.getPosX(); 
	int posY = estadoAvionXml.getPosY();
	int sizeProyectiles = estadoAvionXml.getEstadosProyectiles().size();
	int offset = 0;

	memcpy(buffer + offset,&sizeBytes,sizeof(int));
	offset += sizeof(int);
	
	memcpy(buffer + offset,&id,sizeof(int));
	offset += sizeof(int);
	
	memcpy(buffer + offset,&frame,sizeof(int));
	offset += sizeof(int);

	memcpy(buffer + offset,&posX,sizeof(int));
	offset += sizeof(int);

	memcpy(buffer + offset,&posY,sizeof(int));
	offset += sizeof(int);

	memcpy(buffer + offset,&sizeProyectiles,sizeof(int));
	offset += sizeof(int);

	std::list<EstadoProyectilXml*>::iterator it;

	std::list<EstadoProyectilXml*> lista = estadoAvionXml.getEstadosProyectiles();

	for (it = lista.begin(); it != lista.end(); it++) {
		EstadoProyectilXml* estadoProyectilXml = (*it);
		offset += codificar(*estadoProyectilXml,buffer + offset);
	}
#ifdef FAKE_DEBUG_PROTO
	TCadena1000 cadena;
	estadoAvionXml.toString(cadena);
	printf("%s\n",cadena);		
#endif
	return offset;

}

int Protocolo::decodificar(char * buffer,EstadoAvionXml *estadoAvionXml){

	int sizeBytes = -1;
	int id = -1;
	int frame = -1;
	int posX = -1;
	int posY = -1;
	int sizeProyectiles = -1;
	int offset = 0;
	
	memcpy(&sizeBytes,buffer + offset,sizeof(int));
	offset += sizeof(int);
	
	memcpy(&id,buffer + offset,sizeof(int));
	offset += sizeof(int);
	
	memcpy(&frame,buffer + offset,sizeof(int));
	offset += sizeof(int);
	
	memcpy(&posX,buffer + offset,sizeof(int));
	offset += sizeof(int);

	memcpy(&posY,buffer + offset,sizeof(int));
	offset += sizeof(int);
		
	estadoAvionXml->setId(id);
	estadoAvionXml->setFrame(frame);
	estadoAvionXml->setPosX(posX);
	estadoAvionXml->setPosY(posY);
	
	memcpy(&sizeProyectiles,buffer + offset,sizeof(int));
	offset += sizeof(int);

	for (int i = 0; i < sizeProyectiles;i++){
		EstadoProyectilXml* estadoProyectil = new EstadoProyectilXml();
		offset += decodificar(buffer + offset,estadoProyectil);
		estadoAvionXml->agregarEstadoProyectil(estadoProyectil);
	}

	estadoAvionXml->calculateSizeBytes();
#ifdef FAKE_DEBUG_PROTO
	TCadena1000 cadena;
	estadoAvionXml->toString(cadena);
	printf("%s\n",cadena);	
#endif
	return offset;
}

int Protocolo::codificar(EstadoProyectilXml &estadoProyectilXml,char * buffer){

	int sizeBytes = estadoProyectilXml.getSizeBytes();
	int frame = estadoProyectilXml.getFrame(); 
	int posX = estadoProyectilXml.getPosX(); 
	int posY = estadoProyectilXml.getPosY();
	int offset = 0;

	memcpy(buffer + offset,&sizeBytes,sizeof(int));
	offset += sizeof(int);
	
	memcpy(buffer + offset,&frame,sizeof(int));
	offset += sizeof(int);

	memcpy(buffer + offset,&posX,sizeof(int));
	offset += sizeof(int);

	memcpy(buffer + offset,&posY,sizeof(int));
	offset += sizeof(int);

#ifdef FAKE_DEBUG_PROTO
	TCadena1000 cadena;
	estadoProyectilXml.toString(cadena);
	printf("%s\n",cadena);		
#endif
	return offset;
}

int Protocolo::decodificar(char * buffer,EstadoProyectilXml *estadoProyectilXml){

	int sizeBytes = -1;
	int frame = -1;
	int posX = -1;
	int posY = -1;
	int offset = 0;
	
	memcpy(&sizeBytes,buffer + offset,sizeof(int));
	offset += sizeof(int);
	
	memcpy(&frame,buffer + offset,sizeof(int));
	offset += sizeof(int);
	
	memcpy(&posX,buffer + offset,sizeof(int));
	offset += sizeof(int);

	memcpy(&posY,buffer + offset,sizeof(int));
	offset += sizeof(int);
		
	estadoProyectilXml->setFrame(frame);
	estadoProyectilXml->setPosX(posX);
	estadoProyectilXml->setPosY(posY);
	
	estadoProyectilXml->calculateSizeBytes();

#ifdef FAKE_DEBUG_PROTO
	TCadena1000 cadena;
	estadoProyectilXml->toString(cadena);
	printf("%s\n",cadena);	
#endif
	return offset;
}
