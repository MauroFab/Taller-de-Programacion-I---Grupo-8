#include "StdAfx.h"
#include "codificador.h"
#include <string.h>

Codificador::Codificador(void)
{
}


Codificador::~Codificador(void)
{
}


char* Codificador::convertir(int unEntero)
{
	char* datoConvertido = new char[1024];
	char* enteroEnChar = new char[1024];
	datoConvertido[0] = '0'; // El primer bit en 40 indica un int
	sprintf(enteroEnChar, "%d", unEntero);
	agregarDatoDeA(enteroEnChar, datoConvertido);
	return datoConvertido;

}

void Codificador::agregarDatoDeA(char* enteroEnChar, char* datoConvertido)
{
	int i = 0;
	while (enteroEnChar[i] != NULL){
		datoConvertido[i+1] = enteroEnChar[i];
		i++;
	}
	datoConvertido[i+1] = 0;
}
