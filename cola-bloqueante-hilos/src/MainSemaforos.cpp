#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../include/ColaBloqueante.h"

int main( void ){
	srand (time(NULL));
	ColaBloqueante * pColaBloqueante = ColaBloqueante::getInstance();
	pColaBloqueante->crearSemaforos();
	pColaBloqueante->crearHilos();
	printf("\nEND");
	return 0;
}




