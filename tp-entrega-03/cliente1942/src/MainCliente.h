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
#include "../../common/MensajeSeguro.h"
#include "../../common/Posicion.h"

#include "../../juego/VistaInicio.h"
#include "../../juego/VistaJuego.h"
#include "../../juego/EstadoAvion.h"
#include "../../juego/EstadoProyectil.h"

// CODIGO DE FINALIZACION DE OPERACIONES
#define COD_OK					0
#define COD_KO					-1

#define OPT_CONECTAR	1
#define OPT_DESCONECTAR 2
#define OPT_SALIR		3
#define OPT_ENVIAR		4

//este flag esta para trabajar sin cargar los datos
//pues servidor y puerto los levanta del XML
//#define FAKE_DEBUG_CLIENTE		1

using std::string;
using std::map;
using std::pair;

class MainCliente : public Observador
{
private:

    static MainCliente *single;

	SOCKET sock;

	//este atributo contiene los mensajes a enviar al servidor
	map<int,MensajeXml*> mapMensajes;
	string ip;
	string port;
	WSADATA wsa;
	struct hostent *host;
	struct sockaddr_in direc;
	bool conectado;
	static bool serverDesconectado;
	static bool cerrarConexion;
	int opt;

	//contiene al parser, lo crea y lo borra
	ParserXml * parserx;
	//se almancena todo el modelo parseado
	ServidorXml * servidorXml;
public:
	static MainCliente* getInstance();
	virtual ~MainCliente();
	void parsearArchivoXml(int argc, char* argv[]);
	ParserXml * getParserXml();
	int chequearConexion(int len);
	int menu();
	//realiza la conexion y copia todo el modelo desde el cliente
	int conectar();
	int inicio();
	int desconectar();
	int salir();
	int terminarElCliente();
	/**
	 * se encarga de liberar la memoria del servidorXML
	 * y volver a alocar memoria para el nuevo servidorXML
	 */
	void recreateServidorXml();

private:
	MainCliente();
	SDL_Thread* receptor;
	int inicializarConexion();
	static void grabarEnElLogLaDesconexion(int len);
	static int fun_recibirMensajes(void*);
	int recibirMensajes(void*);
	virtual int actualizar(Evento* eventoRecibido);
};

#endif //_MAINCLIENTE_H_
