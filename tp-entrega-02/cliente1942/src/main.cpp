#include <winsock2.h> //la cabezera para usar las funciones de winsock
#include <stdio.h>
#pragma comment(lib,"ws2_32.lib")

#include "MainCliente.h"

int main(int argc, char* argv[]){
	MainCliente mainCliente;
	mainCliente.parsearArchivoXml(argc,argv);

	mainCliente.menu();
	// mainCliente.principal();

	return 0;
}