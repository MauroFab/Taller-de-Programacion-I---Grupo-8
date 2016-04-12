#include <iostream>
#include <string>
#include <stdio.h>
#include "MainServidor.h"

int main(int argc, char *argv[]){
	
	MainServidor * pMainServidor = MainServidor::getInstance();
	pMainServidor->parsearArchivoXml(argc,argv);
	pMainServidor->mainPrincipal();
	return 0;
}
