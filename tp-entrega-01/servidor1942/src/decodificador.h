#ifndef _DECODIFICADOR_H_
#define _DECODIFICADOR_H_

#pragma once

#include "MensajeXml.h"
#include "ParserXml.h"
#include <string.h>
#include <stdio.h>
#include <tchar.h>
#include <stdlib.h>

class Decodificador {

public:
	Decodificador(void);
	~Decodificador(void);

	// Devuelve la cantidad de Bytes que decodific�
	int decodificar(char* buffer, MensajeXml* mensaje);

	// Devuelve el c�digo de error correspondiente o 0 en caso de que el mensaje sea v�lido
	int validarMensaje(MensajeXml* mensaje);

	// Devuelve un string informando sobre el tipo de error
	char* informacionSobreError(int codigoError);
};

#endif //_DECODIFICADOR_H_

