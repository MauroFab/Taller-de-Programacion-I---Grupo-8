#include "StdAfx.h"
#include "TestCodificador.h"
#include "codificador.h"
#include <string.h>

TestCodificador::TestCodificador(void)
{
}


TestCodificador::~TestCodificador(void)
{
}


void TestCodificador::siConviertoUnInt10Obtengo010()
{
	char* deseado;
	char* obtenido;
	deseado = "010";
	obtenido = codificador.convertir(10);
	if (strcmp(deseado, obtenido) == 0){
		printf("Test exitoso\n");
	}else{
		printf("Test fallido\n");
	}
}
