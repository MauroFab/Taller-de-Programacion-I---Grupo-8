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
#include "../../juego/Avion.h"
#include "../../common/view/AvionView.h"
#include "../../common/view/BalaView.h"
#include "../../common/model/AvionModel.h"
#include "../../common/model/BalaModel.h"

//funciondes de hilos de SDL
void freeSocketsSDL (SOCKET* s);
void waitThreadSDL (SDL_Thread* h);

class MainServidor
{
private:

	/*Atributos*/

	int argc; 
	char* *argv;

	struct MensajeConId {
	    int id;
		char* mensaje;
		EstadoAvionXml estadoAvionXml;
	};

	struct MensajeConIdRecibido {
	    int id;
		Evento* evento;
	};

	static bool instanceFlag;
    static MainServidor *single;
	AsignadorDeUsuarios *usuarios;

	//Temporalmente voy a tener los aviones de los jugadores directamente en el servidor, 
	//Luego deberan ir incluidos dentro del juego en algun otro lugar
	Avion** avion;


	int clienteQueSolitaElEstado;
	int posicionDelMapa;
	bool seActualizoLaUltimaPosicionDelMapa;

	
	int puerto;
	MainServidor();

	ServidorXml * servidorXml; //se almancena todo el modelo parseado
	bool seDebeCerrarElServidor;
	std::queue<MensajeConIdRecibido*> colaDeMensaje;
	std::vector<SDL_Thread*> vectorHilos;
	std::vector<SOCKET*> vectorSockets;
	SOCKET socketDeEscucha;
	SDL_mutex *mutColaPrincipal; // el mutex para proteger la cola de mensajes
	SDL_mutex **mutColaDeUsuario;
	SDL_mutex *mutLogger;

	/**
	 * recarga el archivo XML y lo vuelve a parsear
	 * borra el anterior ServidorXml
	 * y crea otra instancia de ServidorXml
	 */
	void recargarServidorXml();
	/**
	 * crea la instancia de  ServidorXml
	 * @return retorna la cantidadDeClientesMaxima
	 */
	int parsearXML(int argc, char* argv[]);

public:

	/*Funciones*/

	static MainServidor* getInstance();
	virtual ~MainServidor();
	void parsearArchivoXml(int argc, char* argv[]);

	/*Funciones estaticas ultilizadas como puntero a funcion*/

	static int fun_atenderCliente(void* punteroAlSocketRecibido);
	static int fun_recibirConexiones(void*);
	static int fun_consola(void*);
	static int fun_revisarSiHayMensajesParaElClienteYEnviarlos(void* idYPunteroAlSocketRecibido);

	SOCKET obtenerSocketInicializado(sockaddr_in &local);

	void escucharSocket(SOCKET sock);
	void grabarEnElLogLaDesconexion(int len);

	/**
	 * @param sizeBytesIn cantidad de bytes de la conexion
	 * @return true si es positivo
	 * false en otro caso
	 */
	bool isHayBytes(int sizeBytesIn);
	bool esUnMensajeDeUnEstadoAvion(MensajeConId* mensajeConId);
	bool esUnMensajeIndicandoQueNecesitoUnEstadoMapa(MensajeConId* mensajeConId);
	bool esUnEstadoMapa(EstadoAvionXml* estadoAvionXml);
	bool esUnEstadoAvion(EstadoAvionXml* estadoAvionXml);
	bool esUnMensajeIndicandoQueSeDebeReiniciarElMapa(MensajeConId* estadoAvionXml);
	bool indicaUnReinicioDelMapa(EstadoAvionXml* estadoAvionXml);
	int atenderCliente(void* punteroAlSocketRecibido);
	int recibirConexiones(void*);
	/**
	 * este metodo se encarga esperar a capturar las teclas de la consola
	 * cuando recibe el mensaje de cierre, cierra el socket global
	 * 
	 * @param 
	 */
	int waitTeclasConsola(void*);
	int revisarSiHayMensajesParaElClienteYEnviarlos(void* idYPunteroAlSocketRecibido);
	/**
	 * este metodo envia todo el modelo xml al socket del cliente
	 * @param idCliente id del cliente
	 * @param socket socket_escucha del cliente asociado al id idCliente
	 */
	void enviarModeloXmlxConexionAceptadaAl(int idCliente, SOCKET* socket);
	void actualizarLaUltimaPosicionDelUsuario(int id, EstadoAvionXml* estadoAvion);
	/**
	 * crea un MensajeXml temporalmente que luego enviar por un socket
	 * @param  socket socket del cliente al que se enviara el mensajeXML
	 * @param mensajeStr cadena de texto que contiene el mensaje a enviar
	 */
	void sendMensajeXml(SOCKET* socket,char * mensajeStr);
	/**
	 * recibe un MensajeXml creado fuera del metodo y luego lo carga con datos
	 * obtenidos desde el socket
	 * @param socket socket del cliente sobre el que se recibe el mensajeXML
	 * @param mensajeRecib MensajeXml que contiene la salida cargada desde el socket
	 */
	void receiveMensajeXml(SOCKET* socket,MensajeXml * mensajeRecib);
	/**
	 * este metodo envia el estado INICIAL del juego/de la partida
	 * @param socket socket del cliente usado para enviar el estado del avion
	 */
	void enviarEstadoAvionXmlxQueYaEmpezoElJuego(SOCKET* socket);
	void enviarMensajeDeConexionRechazadaPorqueYaEstaLlenoElServidorAl(SOCKET* socket);
	void enviarMensajeDeConexionRechazadaPorqueYaEstaConectadoEseUsuarioAl(SOCKET* socket);
	void informarATodosLosClientesDelEstadoDelAvion(MensajeConId* mensajeConId);
	void informarATodosLosClientesDelReinicioDelEscenario(MensajeConId* mensajeConId);
	void informarAUnClienteQueSeRequiereSaberLaPosicionDelMapa();

	//Crea los aviones basandose en el servidorXml
	//Y los pone en aviones, el atributo del mainServidor
	//En futuros cambios quedaran encapsulados adentro del juego
	//Nota: No define la posicion inicial de los aviones.
	void crearAviones();
	int mainPrincipal();
};

#endif //_MAINSERVIDOR_H_