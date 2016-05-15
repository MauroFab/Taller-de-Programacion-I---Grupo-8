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

#include "../../juego/Juego.h"
#include "../../juego/EstadoAvion.h"
#include "../../juego/EstadoProyectil.h"

// CODIGO DE FINALIZACION DE OPERACIONES
#define COD_OK					0
#define COD_KO					-1

#define OPT_CONECTAR	1
#define OPT_DESCONECTAR 2
#define OPT_SALIR		3
#define OPT_ENVIAR		4

//FAKE es de falso, bueno este flag esta para trabajar sin cargar los datos
//pues servidor y puerto los levanta del XML
//y que se harcodee nombre cuando esta todo hardcodeado no pasa nada
//nota:antes de que un integrante puntual salte le aviso, dejar No hardcodeado lo unico que se ingresa, es complicarla ahora
//y antes del lo de siempre, y diga <<NO<<, esa no es la forma correcta hagamos lo contrario.--> eso es perder tiempo
#define FAKE_DEBUG_CLIENTE		1

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
	string nombreDeUsuario;
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
	//realiza la conexion y copia todo el modelo desde el cliente
	int conectar();
	int desconectar();
	int salir();
	int enviar();
private:

	SDL_Thread* receptor;
	int inicializarConexion();
	static void grabarEnElLogLaDesconexion(int len);
	static int recibirMensajes(void*);
	void cargarNombreDeUsuario();
	void cargarIpYPuerto();
	void cargarIP();
	void cargarPuerto();

	virtual void actualizar(int argc, void* argv[]);
};

#endif //_MAINCLIENTE_H_
