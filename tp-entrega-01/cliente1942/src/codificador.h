#ifndef _CODIFICADOR_H_
#define _CODIFICADOR_H_

#pragma once

#include "../../common/MensajeXml.h"
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <tchar.h>
#include <stdlib.h>

class Codificador {

public:
	Codificador(void);
	~Codificador(void);

	char* convertir(int unEntero);
	char* convertir(double unDouble);
	char* convertir(char unaCadena[]);
	char* convertir(char unCarater);

	// Devuelve la cantidad de Bytes que codificó
	int convertir(MensajeXml &mensaje, char* buffer);

private:
	int agregarDatoDeA(char* enteroEnChar, char* datoConvertido);
	char* convertirAMinuscula(char* palabra);
};

#endif //_CODIFICADOR_H_
