#ifndef _MAINCLIENTE_H_
#define _MAINCLIENTE_H_

#include <winsock2.h> //la cabezera para usar las funciones de winsock
#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <map>
#include <list>
#include <string>
#include <sstream>
#include <cstdlib>
#include <cctype>
#include <SDL2\SDL_thread.h>
#include <SDL2\SDL.h>

#pragma comment(lib,"ws2_32.lib")

#include "../../common/Log.h"
#include "../../common/xml/ParserXml.h"
#include "../../common/xml/ServidorXml.h"
#include "../../common/xml/MensajeXml.h"
#include "../../common/Protocolo.h"
#include "../../common/observer/Observador.h"

// CODIGO DE FINALIZACION DE OPERACIONES
#define COD_OK					0
#define COD_KO					-1

#define OPT_CONECTAR	1
#define OPT_DESCONECTAR 2
#define OPT_SALIR		3
#define OPT_ENVIAR		4

using std::string;
using std::map;
using std::pair;

class MainCliente : public Observador
{
private:
	SOCKET sock;
	
	//este atributo contiene los mensajes a enviar al servidor
	map<int,MensajeXml*> mapMensajes;
	string dirXML;
	string ip,port;
	WSADATA wsa;
	struct hostent *host;
	struct sockaddr_in direc;
	int conex,c,len;
	bool conectado;
	bool serverDesconectado;
	bool cerrarConexion;

	//contiene al parser, lo crea y lo borra
	ParserXml * parserx;
	//se almancena todo el modelo parseado
	ServidorXml * servidorXml;	
public:
	MainCliente();
	virtual ~MainCliente();
	void parsearArchivoXml(int argc, char* argv[]);
	ParserXml * getParserXml();
	int chequearConexion(int len);
	int menu();
	int conectar();
	int desconectar();
	int salir();
	int enviar();
private:
	int inicializarConexion();

	SDL_Thread* receptor;
	static int recibirMensajes(void*);

	virtual void actualizar(int argc, void* argv[]);
};

#endif //_MAINCLIENTE_H_
