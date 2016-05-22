#ifndef _MAINSERVIDOR_H_
#define _MAINSERVIDOR_H_

#include <iostream>
#include <string>
#include <queue>     
#include <vector>
#include <algorithm>
#include <sstream>
#include <fstream>
#include <stdio.h>
#include <WinSock2.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_thread.h>

#pragma comment(lib,"ws2_32.lib")
using std::string;
using std::cout;
using std::cin;
using std::clog;
using std::cerr;
using std::ofstream;


#include "../../common/Log.h"
#include "asignadorDeUsuarios.h"
#include "../../common/xml/ParserXml.h"
#include "../../common/xml/MensajeXml.h"
#include "../../common/xml/EstadoAvionXml.h"
#include "../../common/Protocolo.h"
#include "../../common/MensajeSeguro.h"
class MainServidor
{
private:
	struct MensajeConId {
	     int id;
		 char* mensaje;
		 EstadoAvionXml mensajeXml;
	};
	void notificarPorConsolaLaDesconexionInesperada();
    static bool instanceFlag;
    static MainServidor *single;
	AsignadorDeUsuarios *usuarios;
	int puerto;
    MainServidor();
	//pMsj mensaje desde el cual se realiza la copia de datos
	void guardarElMensajeEnLaColaPrincipal(char* buffer, int id,EstadoAvionXml* pMsj);
	//se almancena todo el modelo parseado
	ServidorXml * servidorXml;
	void MainServidor::grabarEnElLogLaDesconexion(int len);
	bool seguimosConectados(int len);
	void enviarMensajeDeConexionAceptadaAl(SOCKET* socket);
public:
	bool seDebeCerrarElServidor;
	std::queue<MensajeConId*> colaDeMensaje;
	std::vector<SDL_Thread*> vectorHilos;
	std::vector<SOCKET*> vectorSockets;
	std::map<string, bool> usuariosConectados;
	SOCKET socketDeEscucha;
	SDL_mutex *mut; // el mutex para proteger la cola de mensajes

public:

	virtual ~MainServidor();
	static MainServidor* getInstance();
	void parsearArchivoXml(int argc, char* argv[]);
public:
	SOCKET obtenerSocketInicializado(sockaddr_in &local);
	void ponerAEscuchar(SOCKET sock);
	static int fun_atenderCliente(void* punteroAlSocketRecibido);
	static int fun_recibirConexiones(void*);
	static int fun_consolaDelServidor(void*);
	static int fun_avisarATodos(void*);
	static int fun_revisarSiHayMensajesParaElClienteYEnviarlos(void* idYPunteroAlSocketRecibido);

	int revisarSiHayMensajesParaElClienteYEnviarlos(void* idYPunteroAlSocketRecibido);
	int atenderCliente(void* punteroAlSocketRecibido);
	int recibirConexiones(void*);
	int consolaDelServidor(void*);
	int avisarATodos(void*);
	int mainPrincipal();
};

#endif //_MAINSERVIDOR_H_