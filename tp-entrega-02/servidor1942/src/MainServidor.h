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
#include "../../common/StringUtil.h"
#include "asignadorDeUsuarios.h"
#include "../../common/xml/ParserXml.h"
#include "../../common/xml/MensajeXml.h"
#include "../../common/xml/EstadoAvionXml.h"
#include "../../common/Protocolo.h"
#include "../../common/MensajeSeguro.h"

class MainServidor
{
private:

	/*Atributos*/

	struct MensajeConId {
	    int id;
		char* mensaje;
		EstadoAvionXml estadoAvionXml;
	};

	static bool instanceFlag;
    static MainServidor *single;
	AsignadorDeUsuarios *usuarios;

	int clienteQueSolitaElEstado;
	int posicionDelMapa;
	bool seActualizoLaUltimaPosicionDelMapa;
	void solicitarLaUltimaPosicionDelMapaAUnCliente();

	int puerto;
	MainServidor();

	ServidorXml * servidorXml; //se almancena todo el modelo parseado
	bool seDebeCerrarElServidor;
	std::queue<MensajeConId*> colaDeMensaje;
	std::vector<SDL_Thread*> vectorHilos;
	std::vector<SOCKET*> vectorSockets;
	SOCKET socketDeEscucha;
	SDL_mutex *mutColaPrincipal; // el mutex para proteger la cola de mensajes
	SDL_mutex **mutColaDeUsuario;
	SDL_mutex *mutLogger;

public:

	/*Funciones*/

	static MainServidor* getInstance();
	virtual ~MainServidor();
	void parsearArchivoXml(int argc, char* argv[]);

	/*Funciones estatáticas ultilizadas como puntero a función*/

	static int fun_atenderCliente(void* punteroAlSocketRecibido);
	static int fun_recibirConexiones(void*);
	static int fun_consola(void*);
	static int fun_revisarSiHayMensajesParaElClienteYEnviarlos(void* idYPunteroAlSocketRecibido);

	SOCKET obtenerSocketInicializado(sockaddr_in &local);

	void ponerAEscuchar(SOCKET sock);
	void guardarElMensajeEnLaColaPrincipal(char* buffer, int id,EstadoAvionXml* pMsj);
	void grabarEnElLogLaDesconexion(int len);

	bool seguimosConectados(int len);
	bool esUnMensajeDeUnEstadoAvion(MensajeConId* mensajeConId);
	bool esUnMensajeIndicandoQueNecesitoUnEstadoMapa(MensajeConId* mensajeConId);
	bool esUnEstadoMapa(EstadoAvionXml* estadoAvionXml);
	bool esUnEstadoAvion(EstadoAvionXml* estadoAvionXml);
	bool esUnMensajeIndicandoQueSeDebeReiniciarElMapa(MensajeConId* estadoAvionXml);
	bool indicaUnReinicioDelMapa(EstadoAvionXml* estadoAvionXml);
	int atenderCliente(void* punteroAlSocketRecibido);
	int recibirConexiones(void*);
	int consola(void*);
	int revisarSiHayMensajesParaElClienteYEnviarlos(void* idYPunteroAlSocketRecibido);
	void enviarMensajeDeConexionAceptadaAl(int idUsuario, SOCKET* socket);
	void actualizarLaUltimaPosicionDelUsuario(int id, EstadoAvionXml* estadoAvion);
	/**
	 * crea un MensajeXml temporalmente que luego enviar por un socket
	 * @param  socket socket del cliente al que se enviara el mensajeXML
	 * @param mensajeStr cadena de texto que contiene el mensaje a enviar
	 */
	void sendMensajeXml(SOCKET* socket,char * mensajeStr);
	void enviarUnMensajeAvisandoleQueYaEmpezoElJuegoAl(SOCKET* socket);
	void enviarMensajeDeConexionRechazadaPorqueYaEstaLlenoElServidorAl(SOCKET* socket);
	void enviarMensajeDeConexionRechazadaPorqueYaEstaConectadoEseUsuarioAl(SOCKET* socket);
	void informarATodosLosClientesDelEstadoDelAvion(MensajeConId* mensajeConId);
	void informarAUnClienteQueSeRequiereSaberLaPosicionDelMapa();
	int mainPrincipal();
};

#endif //_MAINSERVIDOR_H_