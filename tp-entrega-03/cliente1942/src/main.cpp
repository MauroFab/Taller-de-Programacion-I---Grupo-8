#include <winsock2.h> //la cabezera para usar las funciones de winsock
#include <stdio.h>
#pragma comment(lib,"ws2_32.lib")

#include "MainCliente.h"

int main(int argc, char* argv[]){
	MainCliente* mainCliente = MainCliente::getInstance();
#ifdef FAKE_DEBUG_CLIENTE		
	mainCliente->parsearArchivoXml(argc,argv);
#endif		

	mainCliente->menu();
	return 0;
}