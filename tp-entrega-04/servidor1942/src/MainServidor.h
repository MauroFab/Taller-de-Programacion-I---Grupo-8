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
#include "../../common/xml/ParserXml.h"
#include "../../common/xml/MensajeXml.h"
#include "../../juego/EstadoAvion.h"
#include "../../common/Protocolo.h"
#include "../../common/MensajeSeguro.h"
#include "../../juego/Avion.h"
#include "../../common/view/AvionView.h"
#include "../../common/view/BalaView.h"
#include "../../common/model/AvionModel.h"
#include "../../common/model/BalaModel.h"
#include "ModeloDelJuego.h"
#include "asignadorDeUsuarios.h"
#include "ConfiguracionInicialJuego.h"

#define MODO_EQUIPO "Equipo"

//funciondes de hilos de SDL
void freeSocketsSDL (SOCKET* s);
void waitThreadSDL (SDL_Thread* h);

class MainServidor
{
private:
	/*Parametros del servidor*/

	/*Nota: esta configuracion fue puesta para que ande correctamente en mi pc de escritorio con 4 jugadores. 
	Los parametros podrían variar un poco de pc a pc.
	Todos los tiempos estan en ms, y son una cota minima. Subirlos implica una mejora en el rendimiento
	para el servidor, a costa de lo que este comentado*/

	//Subir este tiempo implica unicamente que se tarde un poco mas en detectar una conexion entrante
	static const int tiempoEntreRevisarNuevasConexiones = 1000;

	//Subir este tiempo implica que el cliente sentira cierta "demora" entre lo que apreta y lo que le pasa
	//A su avion. Con 60ms es casi imperceptible
	static const int tiempoEntreRevisarNuevosEventosUsuario = 60;

	/*Los siguientes dos van a la par, y son los mas sensibles. 
	
	Las zonas a las que afectan estan sujetas a cambios para mejorar el funcionamiento.
	
	
	Este es el tiempo entre el cual miro de nuevo si hay estadoJuegos para enviar a los clientes,
	Subirlo provoca que al cliente no le lleguen suficientes estados para tener una grafica fluida
	pero le da mas tiempo al thread principal para poner los nuevos estados en la cola de los jugadores.
	haciendo que vaya mas fluido
	*/
	static const int tiempoEntreVolverARevisarSiLaColaEstaVacia = 10;

	/*Este es el tiempo entre el cual avanzo el juego, subirlo hace que los estadoJuego vayan mas lento al cliente,
	  y retrasa la velocidad a la que va el juego
	 */

	static const int tiempoEntreAvancesDelJuego = 10;


	/*Atributos*/

	int argc;
	char* *argv;

	struct MensajeConId {
	    int id;
		char* mensaje;
		EstadoAvion* estadoAvion;
	};

	struct MensajeConIdRecibido {
	    int id;
		Evento* evento;
	};

    static MainServidor *single;
	AsignadorDeUsuarios *usuarios;

	ModeloDelJuego* modeloJuego;

	int clienteQueSolitaElEstado;
	int posicionDelMapa;
	//No se deberia usar para nada cuando todo el modelo pase al servidor,
	//a menos que dejemos el avance del mapa del lado del cliente
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

	static void liberar();
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
	void actualizarLaUltimaPosicionDelUsuario(int id, EstadoAvion* estadoAvion);
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
	void sendEstadoAvionJuegoIniciado(SOCKET* socket);
	void enviarMensajeDeConexionRechazadaPorqueYaEstaLlenoElServidorAl(SOCKET* socket);
	void enviarMensajeDeConexionRechazadaPorqueYaEstaConectadoEseUsuarioAl(SOCKET* socket);

	void esperarAQueTodosLosUsuariosEstenConectadosParaContinuar();
	void avisarATodosLosUsuariosQueComenzoLaPartida();

	void comunicarEventosRecibidosAlJuego();
	//Por ahora comunica estadoAvionesXml. Deberia comunicar el estado juego

	void comunicarElNuevoEstadoDelJuegoALosClientes();
	//Crea los aviones basandose en el servidorXml
	//Y los pone en aviones, el atributo del mainServidor
	//En futuros cambios quedaran encapsulados adentro del juego
	//Nota: No define la posicion inicial de los aviones.
	int mainPrincipal();
};

#endif //_MAINSERVIDOR_H_