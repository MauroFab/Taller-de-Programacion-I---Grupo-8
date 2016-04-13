#ifndef _PROTOCOLO_H_
#define _PROTOCOLO_H_

#include <stdio.h>
#include "MensajeXml.h"
#include "ParserXml.h"

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
	
	// Devuelve el código de error correspondiente o 0 en caso de que el mensaje sea válido
	static int validarMensaje(MensajeXml &mensaje);	
};

#endif //_PROTOCOLO_H_
