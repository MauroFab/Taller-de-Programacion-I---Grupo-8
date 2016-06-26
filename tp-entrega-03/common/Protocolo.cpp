#include "Protocolo.h"

Protocolo::Protocolo()
{
}

Protocolo::~Protocolo(){
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

int Protocolo::codificar(SpriteXml &spriteXml,char * buffer){
	int sizeBytes = spriteXml.getSizeBytes();
	int id = spriteXml.getId();
	char * strId = spriteXml.getStrId();//ojo que aqui se copian los punteros, no se debe liberar luego (lo hace el destructor)
	char len_strId = strlen(strId);
	char * path = spriteXml.getPath();
	char len_path = strlen(path);
	int cantidad = spriteXml.getCantidad();
	int ancho = spriteXml.getAncho();
	int alto = spriteXml.getAlto();
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
	int idSprite = fondoXml.getIdSprite();
	char * strIdSprite = fondoXml.getStrIdSprite();
	char len_strIdSprite = strlen(strIdSprite);
	int ancho = fondoXml.getAncho();
	int alto = fondoXml.getAlto();

	int offset = 0;
	memcpy(buffer + offset,&sizeBytes,sizeof(int));
	offset += sizeof(int);

	memcpy(buffer + offset,&idSprite,sizeof(int));
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
	int idSprite = -1;
	char strIdSprite[MAX_CADENA] = {0};
	char len_strIdSprite = -1;
	int ancho = -1;
	int alto = -1;
	int offset = 0;
	memcpy(&sizeBytes,buffer + offset,sizeof(int));
	offset += sizeof(int);

	memcpy(&idSprite,buffer + offset,sizeof(int));
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

	fondoXml->setIdSprite(idSprite);
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
	int ancho = ventanaXml.getAncho();
	int alto = ventanaXml.getAlto();
	int velocidadCamara = ventanaXml.getVelocidadCamara();
	int offset = 0;

	memcpy(buffer + offset,&sizeBytes,sizeof(int));
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
	int ancho = -1;
	int alto = -1;
	int velocidadCamara = -1;
	int offset = 0;
	memcpy(&sizeBytes,buffer + offset,sizeof(int));
	offset += sizeof(int);

	memcpy(&ancho,buffer + offset,sizeof(int));
	offset += sizeof(int);

	memcpy(&alto,buffer + offset,sizeof(int));
	offset += sizeof(int);

	memcpy(&velocidadCamara,buffer + offset,sizeof(int));
	offset += sizeof(int);

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
	int cantidadMaximaClientes = servidorXml.getCantidadMaximaClientes();
	int puerto = servidorXml.getPuerto();
	int modo = servidorXml.getModo();
	int canEsc = servidorXml.getCanEsc();
	int canSprs = servidorXml.getCanSprs();
	int canAvs = servidorXml.getCanAvs();
	int canEnes = servidorXml.getCanEnes();
	int canPows = servidorXml.getCanPows();
	int offset = 0;

	memcpy(buffer + offset,&sizeBytes,sizeof(int));
	offset += sizeof(int);

	memcpy(buffer + offset,&cantidadMaximaClientes,sizeof(int));
	offset += sizeof(int);

	memcpy(buffer + offset,&puerto,sizeof(int));
	offset += sizeof(int);
	
	memcpy(buffer + offset,&modo,sizeof(int));
	offset += sizeof(int);
	//-----------
	offset += codificar(*servidorXml.getVentanaXmlCopy(),buffer + offset);
	//-----------
	memcpy(buffer + offset,&canEsc,sizeof(int));
	offset += sizeof(int);
	for (int idx = 0; idx<canEsc;idx++){
		EscenarioXml * escX = servidorXml.getListaEscenario()[idx];
		offset += codificar(*escX,buffer + offset);
	}
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
	memcpy(buffer + offset,&canEnes,sizeof(int));
	offset += sizeof(int);
	for (int idx = 0; idx<canEnes;idx++){
		AvionEnemigoXml * avEneX = servidorXml.getListaEnemigos()[idx];
		offset += codificar(*avEneX,buffer + offset);
	}
	//-----------	
	memcpy(buffer + offset,&canPows,sizeof(int));
	offset += sizeof(int);
	for (int idx = 0; idx<canPows;idx++){
		PowerUpXml * powU = servidorXml.getListaPowerUp()[idx];
		offset += codificar(*powU,buffer + offset);
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
	int cantidadMaximaClientes = -1;
	int puerto = -1;
	int modo = -1;
	int canEsc = -1;
	int canSprs = -1;
	int canAvs = -1;
	int canEnes = -1;
	int canPows = -1;
	int offset = 0;
	memcpy(&sizeBytes,buffer + offset,sizeof(int));
	offset += sizeof(int);

	memcpy(&cantidadMaximaClientes,buffer + offset,sizeof(int));
	offset += sizeof(int);

	memcpy(&puerto,buffer + offset,sizeof(int));
	offset += sizeof(int);
	
	memcpy(&modo,buffer + offset,sizeof(int));
	offset += sizeof(int);
	//-----------
	VentanaXml ventanaXml;
	offset += decodificar(buffer + offset,&ventanaXml);
	servidorXml->setVentanaXml(ventanaXml);
	//-----------
	memcpy(&canEsc,buffer + offset,sizeof(int));
	offset += sizeof(int);
	for (int idx = 0; idx < canEsc;idx++){
		EscenarioXml * escX = new EscenarioXml();
		offset += decodificar(buffer + offset,escX);
		servidorXml->addEscenario(escX,idx);
	}
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
	memcpy(&canEnes,buffer + offset,sizeof(int));
	offset += sizeof(int);
	for (int idx = 0; idx < canEnes;idx++){
		AvionEnemigoXml * avEneX = new AvionEnemigoXml();
		offset += decodificar(buffer + offset,avEneX);
		servidorXml->addEnemigo(avEneX,idx);
	}
	//-----------
	memcpy(&canPows,buffer + offset,sizeof(int));
	offset += sizeof(int);
	for (int idx = 0; idx < canPows;idx++){
		PowerUpXml * powU = new PowerUpXml();
		offset += decodificar(buffer + offset,powU);
		servidorXml->addPowerUp(powU,idx);
	}
	//-----------	
	servidorXml->setCantidadMaximaClientes(cantidadMaximaClientes);
	servidorXml->setPuerto(puerto);
	servidorXml->setModo(modo);
	servidorXml->calculateSizeBytes();
#ifdef FAKE_DEBUG_PROTO
	TCadena1000 cadena;
	servidorXml->toString(cadena);
	printf("%s\n",cadena);
#endif
	return offset;
}

int Protocolo::codificar(AvionEnemigoXml &avionEnemigoXml,char * buffer){
	int sizeBytes = avionEnemigoXml.getSizeBytes();
	int id = avionEnemigoXml.getId();
	int idSprite = avionEnemigoXml.getIdSprite();
	char * strIdSprite = avionEnemigoXml.getStrIdSprite();
	char len_strIdSprite = strlen(strIdSprite);
	int posicion_x = avionEnemigoXml.getPosicion().coorX;
	int posicion_y = avionEnemigoXml.getPosicion().coorY;
	int tipo = avionEnemigoXml.getTipo();

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

	memcpy(buffer + offset,&tipo,sizeof(int));
	offset += sizeof(int);

#ifdef FAKE_DEBUG_PROTO
	TCadena1000 cadena;
	avionEnemigoXml.toString(cadena);
	printf("%s\n",cadena);
#endif
	return offset;
}
int Protocolo::decodificar(char * buffer,AvionEnemigoXml *avionEnemigoXml){
	int sizeBytes = -1;
	int id = -1;
	int idSprite = -1;
	char strIdSprite[MAX_CADENA] = {0};
	char len_strIdSprite = -1;
	TPosicion posicion;
	posicion.coorX = -1;
	posicion.coorY = -1;
	int tipo = -1;
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
	
	memcpy(&tipo,buffer + offset,sizeof(int));
	offset += sizeof(int);

	avionEnemigoXml->setId(id);
	avionEnemigoXml->setIdSprite(idSprite);
	avionEnemigoXml->setStrIdSprite(strIdSprite,len_strIdSprite);
	avionEnemigoXml->setPosicion(posicion);
	avionEnemigoXml->setTipo(tipo);
	avionEnemigoXml->calculateSizeBytes();
#ifdef FAKE_DEBUG_PROTO
	TCadena1000 cadena;
	avionEnemigoXml->toString(cadena);
	printf("%s\n",cadena);
#endif
	return offset;
}

int Protocolo::codificar(PowerUpXml &powerUpXml,char * buffer){
	int sizeBytes = powerUpXml.getSizeBytes();
	int id = powerUpXml.getId();
	int idSprite = powerUpXml.getIdSprite();
	char * strIdSprite = powerUpXml.getStrIdSprite();
	char len_strIdSprite = strlen(strIdSprite);
	int posicion_x = powerUpXml.getPosicion().coorX;
	int posicion_y = powerUpXml.getPosicion().coorY;
	int tipo = powerUpXml.getTipo();

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

	memcpy(buffer + offset,&tipo,sizeof(int));
	offset += sizeof(int);

#ifdef FAKE_DEBUG_PROTO
	TCadena1000 cadena;
	powerUpXml.toString(cadena);
	printf("%s\n",cadena);
#endif
	return offset;
}
int Protocolo::decodificar(char * buffer,PowerUpXml *powerUpXml){
	int sizeBytes = -1;
	int id = -1;
	int idSprite = -1;
	char strIdSprite[MAX_CADENA] = {0};
	char len_strIdSprite = -1;
	TPosicion posicion;
	posicion.coorX = -1;
	posicion.coorY = -1;
	int tipo = -1;
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
	
	memcpy(&tipo,buffer + offset,sizeof(int));
	offset += sizeof(int);

	powerUpXml->setId(id);
	powerUpXml->setIdSprite(idSprite);
	powerUpXml->setStrIdSprite(strIdSprite,len_strIdSprite);
	powerUpXml->setPosicion(posicion);
	powerUpXml->setTipo(tipo);
	powerUpXml->calculateSizeBytes();
#ifdef FAKE_DEBUG_PROTO
	TCadena1000 cadena;
	powerUpXml->toString(cadena);
	printf("%s\n",cadena);
#endif
	return offset;
}

int Protocolo::codificar(EstadoAvion &estadoAvion,char * buffer){

	int sizeBytes = estadoAvion.getSizeBytes();
	int id = estadoAvion.getId();
	int frame = estadoAvion.getFrame();
	int posX = estadoAvion.getPosX();
	int posY = estadoAvion.getPosY();
	int puntosDeVida = estadoAvion.getPuntosDeVida();
	int sizeProyectiles = estadoAvion.getEstadosProyectiles().size();
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

	memcpy(buffer + offset,&puntosDeVida,sizeof(int));
	offset += sizeof(int);

	memcpy(buffer + offset,&sizeProyectiles,sizeof(int));
	offset += sizeof(int);

	std::list<EstadoProyectil*>::iterator it;

	std::list<EstadoProyectil*> lista = estadoAvion.getEstadosProyectiles();

	for (it = lista.begin(); it != lista.end(); it++) {
		EstadoProyectil* estadoProyectil = (*it);
		offset += codificar(*estadoProyectil,buffer + offset);
	}
#ifdef FAKE_DEBUG_PROTO
	TCadena1000 cadena;
	estadoAvion.toString(cadena);
	printf("%s\n",cadena);
#endif
	return offset;

}

int Protocolo::decodificar(char * buffer,EstadoAvion* estadoAvion){

	int sizeBytes = -1;
	int id = -1;
	int frame = -1;
	int posX = -1;
	int posY = -1;
	int sizeProyectiles = -1;
	int puntosDeVida = -1;
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

	memcpy(&puntosDeVida,buffer + offset,sizeof(int));
	offset += sizeof(int);

	estadoAvion->setId(id);
	estadoAvion->setFrame(frame);
	estadoAvion->setPosX(posX);
	estadoAvion->setPosY(posY);
	estadoAvion->setPuntosDeVida(puntosDeVida);

	memcpy(&sizeProyectiles,buffer + offset,sizeof(int));
	offset += sizeof(int);

	for (int i = 0; i < sizeProyectiles;i++){
		EstadoProyectil* estadoProyectil = new EstadoProyectil();
		offset += decodificar(buffer + offset,estadoProyectil);
		estadoAvion->agregarEstadoProyectil(estadoProyectil);
	}

#ifdef FAKE_DEBUG_PROTO
	TCadena1000 cadena;
	estadoAvion->toString(cadena);
	printf("%s\n",cadena);
#endif
	return offset;
}

int Protocolo::decodificar(char* buffer,EstadoProyectil *estadoProyectil){

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

	estadoProyectil->setFrame(frame);
	estadoProyectil->setPosX(posX);
	estadoProyectil->setPosY(posY);

	estadoProyectil->calculateSizeBytes();

#ifdef FAKE_DEBUG_PROTO
	TCadena1000 cadena;
	estadoProyectil->toString(cadena);
	printf("%s\n",cadena);
#endif
	return offset;
}
int Protocolo::codificar(EstadoProyectil &estadoProyectil,char * buffer){

	int sizeBytes = estadoProyectil.getSizeBytes();
	int frame = estadoProyectil.getFrame();
	int posX = estadoProyectil.getPosX();
	int posY = estadoProyectil.getPosY();
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
	estadoProyectil.toString(cadena);
	printf("%s\n",cadena);
#endif
	return offset;
}

int Protocolo::codificar(Posicion &posicion, char* buffer) {

	int sizeBytes = posicion.getSizeBytes();
	int posX = posicion.getPosX();
	int posY = posicion.getPosY();
	int offset = 0;

	memcpy(buffer + offset,&sizeBytes,sizeof(int));
	offset += sizeof(int);

	memcpy(buffer + offset,&posX,sizeof(int));
	offset += sizeof(int);

	memcpy(buffer + offset,&posY,sizeof(int));
	offset += sizeof(int);

#ifdef FAKE_DEBUG_PROTO
	TCadena1000 cadena;
	posicion.toString(cadena);
	printf("%s\n",cadena);
#endif

	return offset;
}

int Protocolo::decodificar(char* buffer, Posicion* posicion) {

	int sizeBytes = -1;
	int posX = -1;
	int posY = -1;
	int offset = 0;

	memcpy(&sizeBytes,buffer + offset,sizeof(int));
	offset += sizeof(int);

	memcpy(&posX,buffer + offset,sizeof(int));
	offset += sizeof(int);

	memcpy(&posY,buffer + offset,sizeof(int));
	offset += sizeof(int);

	posicion->setPosX(posX);
	posicion->setPosY(posY);

	posicion->calculateSizeBytes();

#ifdef FAKE_DEBUG_PROTO
	TCadena1000 cadena;
	posicion->toString(cadena);
	printf("%s\n",cadena);
#endif

	return offset;
}

int Protocolo::codificar(Evento &evento, char* buffer) {

	int sizeBytes = evento.getSizeBytes();
	int offset = 0;
	int numeroDeevento = evento.getNumeroDeEvento();

	memcpy(buffer + offset,&sizeBytes,sizeof(int));
	offset += sizeof(int);

	memcpy(buffer + offset,&numeroDeevento,sizeof(int));
	offset += sizeof(int);
#ifdef FAKE_DEBUG_PROTO
	TCadena1000 cadena;
	evento.toString(cadena);
	printf("%s\n",cadena);
#endif

	return offset;
}

int Protocolo::decodificar(char* buffer, Evento* evento) {
	int sizeBytes = -1;
	int numeroDeEvento = -1;
	int offset = 0;

	memcpy(&sizeBytes,buffer + offset,sizeof(int));
	offset += sizeof(int);

	memcpy(&numeroDeEvento,buffer + offset,sizeof(int));
	offset += sizeof(int);

	evento->setNumeroDeEvento(numeroDeEvento);

#ifdef FAKE_DEBUG_PROTO
	TCadena1000 cadena;
	evento->toString(cadena);
	printf("%s\n",cadena);
#endif

	return offset;
}

int Protocolo::codificar(EstadoJugador &estadoJugador, char* buffer) {
	int sizeBytes = -1;
	int id = -1;
	int puntajeAcumulado;
	int offset = 0;
	sizeBytes = sizeof(int)*2;

	puntajeAcumulado = estadoJugador.getPuntajeAcumulado();
	id = estadoJugador.getid();

	memcpy(buffer + offset,&sizeBytes,sizeof(int));
	offset += sizeof(int);

	memcpy(buffer + offset, &id,sizeof(int));
	offset += sizeof(int);

	memcpy(buffer + offset,&puntajeAcumulado,sizeof(int));
	offset += sizeof(int);
#ifdef FAKE_DEBUG_PROTO
	TCadena1000 cadena;
	estadoJugador.toString(cadena);
	printf("%s\n",cadena);
#endif

	return offset;
}

int Protocolo::decodificar(char* buffer, EstadoJugador &estadoJugador) {
	int sizeBytes = -1;
	int id = -1;
	int puntajeAcumulado;
	int offset = 0;

	memcpy(&sizeBytes,buffer + offset,sizeof(int));
	offset += sizeof(int);

	memcpy(&id,buffer + offset,sizeof(int));
	offset += sizeof(int);

	memcpy(&puntajeAcumulado,buffer + offset,sizeof(int));
	offset += sizeof(int);

	estadoJugador = EstadoJugador(id, puntajeAcumulado);
#ifdef FAKE_DEBUG_PROTO
	TCadena1000 cadena;
	estadoJugador.toString(cadena);
	printf("%s\n",cadena);
#endif
	return offset;
}

int Protocolo::codificar(EstadoPowerUp &estadoPowerUp, char* buffer) {
	int sizeBytes = -1;
	int tipo = -1;
	bool fueUsado;
	int offset = 0;

	sizeBytes = sizeof(int) + sizeof(bool);

	tipo = estadoPowerUp.getTipo();
	fueUsado = estadoPowerUp.fueUsadoElPowerUp();

	memcpy(buffer + offset,&sizeBytes,sizeof(int));
	offset += sizeof(int);

	memcpy(buffer + offset, &tipo,sizeof(int));
	offset += sizeof(int);

	memcpy(buffer + offset,&fueUsado,sizeof(bool));
	offset += sizeof(bool);

	return offset;
}

int Protocolo::decodificar(char* buffer, EstadoPowerUp &estadoPowerUp) {
	int sizeBytes = -1;
	int tipo = -1;
	bool fueUsado;
	int offset = 0;

	memcpy(&sizeBytes,buffer + offset,sizeof(int));
	offset += sizeof(int);

	memcpy(&tipo,buffer + offset,sizeof(int));
	offset += sizeof(int);

	memcpy(&fueUsado,buffer + offset,sizeof(bool));
	offset += sizeof(bool);

	estadoPowerUp = EstadoPowerUp(tipo, fueUsado);

	return offset;
}

int Protocolo::codificar(EstadoJuego &estadoJuego, char* buffer){
	//Por ahora el juego no es mas que un conjunto de un evento, estadoAviones y un estadoMapa
	int offset = 0;	
	std::list<EstadoAvion*> estadoAviones;
	estadoAviones = estadoJuego.getEstadoDeLosAviones();
	int cantidadDeAviones = -1;
	int cantidadDeJugadores = -1;
	if(estadoAviones.empty()){
		cantidadDeAviones = 0;
	}else{
		cantidadDeAviones = estadoAviones.size();
	}

	std::list<EstadoAvion*>::iterator it;
	std::list<EstadoAvion*> lista = estadoAviones;

	//Primero guardamos el evento especial
	offset += codificar(*estadoJuego.obtenerEvento(),buffer + offset);

	//Segundo guardamos la cantidad de aviones
	memcpy(buffer + offset,&cantidadDeAviones,sizeof(int));
	offset += sizeof(int);

	//Luego todos los aviones
	for (it = lista.begin(); it != lista.end(); it++) {
		EstadoAvion* estadoAvion = (*it);
		offset += codificar(*estadoAvion,buffer + offset);
	}

	//Guardo la cantidad de jugadores
	std::list<EstadoJugador> estadoJugadores;

	//Luego sus estados
	estadoJugadores = estadoJuego.getEstadoDeLosJugadores();
	cantidadDeJugadores = estadoJugadores.size();

	memcpy(buffer + offset,&cantidadDeJugadores,sizeof(int));
	offset += sizeof(int);

	std::list<EstadoJugador>::iterator itJ;
	
	for (itJ = estadoJugadores.begin(); itJ != estadoJugadores.end(); itJ++) {
		EstadoJugador estadoJugador = (*itJ);
		offset += codificar(estadoJugador,buffer + offset);
	}

	//Paso a los power ups
	std::list<EstadoPowerUp> estadoPowerUps;
	int cantidadDePowerUps;
	
	estadoPowerUps = estadoJuego.getEstadoPowerUps();
	//Guardo la cantidad de powerUps
	cantidadDePowerUps = estadoPowerUps.size();
	memcpy(buffer + offset,&cantidadDePowerUps,sizeof(int));
	offset += sizeof(int);

	//Guardo los power ups
	std::list<EstadoPowerUp>::iterator itP;
	
	for (itP = estadoPowerUps.begin(); itP != estadoPowerUps.end(); itP++) {
		EstadoPowerUp estadoPowerUp = (*itP);
		offset += codificar(estadoPowerUp,buffer + offset);
	}


	//Luego se codifica el estado del Mapa
	offset += codificar(*estadoJuego.getEstadoDelMapa(), buffer + offset);
#ifdef FAKE_DEBUG_PROTO
	TCadena1000 cadena;
	estadoJuego.toString(cadena);
	printf("%s\n",cadena);
#endif	
	return offset;
}
//ERROR-000
/*Aca hay un new para cada evento eso lo hace mas costoso.
*/
int Protocolo::decodificar(char* buffer, EstadoJuego*& estadoJuego){
	int cantidadDeAviones = -1;
	int cantidadDeJugadores = -1;
	int offset = 0;
	std::list<EstadoAvion*> estadoAviones;
	std::list<EstadoJugador> estadoJugadores;

	Evento* evento = new Evento(0);
	//Decodifico el evento
	offset += decodificar(buffer + offset,evento);

	//Cargo la cantidad de aviones
	memcpy(&cantidadDeAviones,buffer + offset,sizeof(int));
	offset += sizeof(int);

	//Decodifico los datos de los aviones
	for (int i = 0; i < cantidadDeAviones; i++){
		EstadoAvion* estadoAvion = new EstadoAvion();
		offset += decodificar(buffer + offset,estadoAvion);
		estadoAviones.push_back(estadoAvion);
	}

	//Cargo la cantidad de jugadores
	memcpy(&cantidadDeJugadores,buffer + offset,sizeof(int));
	offset += sizeof(int);

	//Decodifico los estado de los jugadores
	for (int i = 0; i < cantidadDeJugadores; i++){
		EstadoJugador estadoJugador;
		offset += decodificar(buffer + offset,estadoJugador);
		estadoJugadores.push_back(estadoJugador);
	}

	int cantidadDePowerUps;
	std::list<EstadoPowerUp> estadoPowerUps;

	//Cargo la cantidad de power ups
	memcpy(&cantidadDePowerUps,buffer + offset,sizeof(int));
	offset += sizeof(int);

	//Decodifico los estados de los power ups
	for (int i = 0; i < cantidadDePowerUps; i++){
		EstadoPowerUp estadoPowerUp;
		offset += decodificar(buffer + offset,estadoPowerUp);
		estadoPowerUps.push_back(estadoPowerUp);
	}

	//Decodifico el estado del Mapa
	EstadoMapa* estadoMapa = new EstadoMapa();
	offset += decodificar(buffer + offset, estadoMapa);

	estadoJuego = new EstadoJuego(estadoAviones, estadoJugadores, estadoPowerUps,
									estadoMapa, *evento);
	delete evento;
#ifdef FAKE_DEBUG_PROTO
	TCadena1000 cadena;
	estadoJuego->toString(cadena);
	printf("%s\n",cadena);
#endif	
	return offset;
}

int Protocolo::codificar(EstadoMapa &estadoMapa, char* buffer) {

	int sizeBytes = estadoMapa.getSizeBytes();
	int offset = 0;

	int cantidadDePixelesQuePasaron = estadoMapa.getCantidadDePixeles();
	int codigoDeReinicio = estadoMapa.getCodigoReinicio();
	int idEtapa = estadoMapa.getIdEtapa();

	memcpy(buffer + offset,&sizeBytes,sizeof(int));
	offset += sizeof(int);

	memcpy(buffer + offset,&cantidadDePixelesQuePasaron,sizeof(int));
	offset += sizeof(int);

	memcpy(buffer + offset,&codigoDeReinicio,sizeof(int));
	offset += sizeof(int);

	memcpy(buffer + offset,&idEtapa,sizeof(int));
	offset += sizeof(int);
#ifdef FAKE_DEBUG_PROTO
	TCadena1000 cadena;
	estadoMapa.toString(cadena);
	printf("%s\n",cadena);
#endif	
	return offset;
}

int Protocolo::decodificar(char* buffer, EstadoMapa* estadoMapa) {

	int sizeBytes = -1;
	int cantidadDePixelesQuePasaron = -1;
	int codigoDeReinicio = -1;
	int idEtapa = -1;
	int offset = 0;

	memcpy(&sizeBytes,buffer + offset,sizeof(int));
	offset += sizeof(int);

	memcpy(&cantidadDePixelesQuePasaron,buffer + offset,sizeof(int));
	offset += sizeof(int);

	memcpy(&codigoDeReinicio,buffer + offset,sizeof(int));
	offset += sizeof(int);

	memcpy(&idEtapa,buffer + offset,sizeof(int));
	offset += sizeof(int);

	estadoMapa->setCantidaDePixeles(cantidadDePixelesQuePasaron);
	estadoMapa->setCodigoReinicio(codigoDeReinicio);
	estadoMapa->setIdEtapa(idEtapa);
#ifdef FAKE_DEBUG_PROTO
	TCadena1000 cadena;
	estadoMapa->toString(cadena);
	printf("%s\n",cadena);
#endif
	return offset;
}