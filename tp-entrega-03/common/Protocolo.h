#ifndef _PROTOCOLO_H_
#define _PROTOCOLO_H_
/* @autor cbenez
 */

#include <stdio.h>
#include "./xml/ParserXml.h"
#include "./xml/MensajeXml.h"
#include "./xml/SpriteXml.h"
#include "./xml/AvionXml.h"
#include "./xml/ElementoXml.h"
#include "./xml/FondoXml.h"
#include "./xml/VentanaXml.h"
#include "Posicion.h"
#include "Evento.h"
#include "../juego/EstadoAvion.h"
#include "../juego/EstadoProyectil.h"
#include "../juego/EstadoJuego.h"
#include "../juego/EstadoMapa.h"

#define MAX_CADENA	300
//buffer suficientemente grande para todo el escenario (2Kb de datos)
#define MAX_BUFFER	5120

#define MSJ_CONEX_ACEPT "Conexion aceptada."
#define MSJ_SUPERO_MAX	"Conexion rechazada. Cantidad maxima de clientes superada."
#define MSJ_USR_YA_CONECT "Nombre de usuario existente y conectado en este momento."
#define MSJ_COMENZAR_JUEGO "Comenzar Juego"
//si este flag existe, entonces se muestran todos los mensajes de debug del protocolo
//se comenta o descomenta esta linea
//#define FAKE_DEBUG_PROTO 1

class Protocolo
{
public:
	Protocolo();
	virtual ~Protocolo();
	/**
	 * @param mensajeXml mensaje que contiene los datos a convertir en tira de bytes
	 * @param buffer que contiene la tira de bytes generada
	 * @return retorna la cantidad de bytes usados para el buffer
	 * luego se debera hacer delete [] del buffer
	 */
	static int codificar(MensajeXml &mensajeXml,char * buffer);
	/**
	 * @param buffer buffer con los bytes que contienen la representacion de cada
	 * campo de un mensajeXml
	 * @param mensajeXml mensaje a cargar con los campos obtenidos desde mensajeXml
	 * @return retorna el size del mensaje obtenido desde el buffer
	 * Por las dudas que sea requerido para el metodo que lo llama para sumar al puntero
	 * y moverse al size del siguiente mensaje
	 */
	static int decodificar(char * buffer,MensajeXml *mensajeXml);

	// Devuelve el c�digo de error correspondiente o 0 en caso de que el mensaje sea v�lido
	static int validarMensaje(MensajeXml &mensaje);

	//los objetos se carga en forma lazy, aquellos que tienen contenedores solo tienen
	//carga parcial de datos
	static int codificar(SpriteXml &spriteXml,char * buffer);
	static int decodificar(char * buffer,SpriteXml *spriteXml);
	static int codificar(AvionXml &avionXml,char * buffer);
	static int decodificar(char * buffer,AvionXml *avionXml);
	static int codificar(ElementoXml &elementoXml,char * buffer);
	static int decodificar(char * buffer,ElementoXml *elementoXml);
	static int codificar(FondoXml &fondoXml,char * buffer);
	static int decodificar(char * buffer,FondoXml *fondoXml);
	static int codificar(VentanaXml &ventanaXml,char * buffer);
	static int decodificar(char * buffer,VentanaXml *ventanaXml);
	static int codificar(EscenarioXml &escenarioXml,char * buffer);
	static int decodificar(char * buffer,EscenarioXml *escenarioXml);
	static int codificar(ServidorXml &servidorXml,char * buffer);
	static int decodificar(char * buffer,ServidorXml *servidorXml);
	static int codificar(AvionEnemigoXml &avionEnemigoXml,char * buffer);
	static int decodificar(char * buffer,AvionEnemigoXml *avionEnemigoXml);
	static int codificar(PowerUpXml &powerUpXml,char * buffer);
	static int decodificar(char * buffer,PowerUpXml *powerUpXml);

	static int codificar(EstadoAvion &estadoProyectil,char * buffer);
	static int decodificar(char * buffer, EstadoAvion *estadoProyectil);

	static int codificar(EstadoProyectil &estadoProyectil,char * buffer);
	static int decodificar(char * buffer,EstadoProyectil *estadoProyectil);

	static int codificar(Posicion &posicion, char* buffer);
	static int decodificar(char* buffer, Posicion* posicion);

	static int codificar(Evento &evento, char* buffer);
	static int decodificar(char* buffer, Evento* posicion);

	static int codificar(EstadoMapa &estadoMapa, char* buffer);
	static int decodificar(char* buffer, EstadoMapa* estadoMapa);
	
	static int codificar(EstadoPowerUp &estadoPowerUp, char* buffer);
	static int decodificar(char* buffer, EstadoPowerUp &estadoPowerUp);
	
	static int codificar(EstadoJugador &estadoJugador, char* buffer);
	static int decodificar(char* buffer, EstadoJugador &estadoJugador);

	static int codificar(EstadoJuego &estadoJuego, char* buffer);
	//A diferencia de los otros codificar, este crea un nuevo estadoJuego
	//El puntero que se le manda no debe tener nada
	//Esto para evitar los sets en el estadoJuego
	static int decodificar(char* buffer,EstadoJuego*& estadoJuego);
};

#endif //_PROTOCOLO_H_
