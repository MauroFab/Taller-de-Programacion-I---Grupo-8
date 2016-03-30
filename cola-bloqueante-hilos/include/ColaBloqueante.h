#ifndef _COLABLOQUEANTE_H_
#define _COLABLOQUEANTE_H_
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <queue>

#define MAX_SEM_COUNT 1

//indica la cantidad maxima de elemento de la cola/pila/lista
#define MAX_COLA 4
#define MAX_ITER 50

class ColaBloqueante
{
private:
    static bool instanceFlag;
    static ColaBloqueante *single;
    ColaBloqueante();
public:	
	//cola de enteros
	int cola[MAX_COLA];
	//cantidad de elementos de la cola de enteros
	int n_cola;
	//cola para los mensajes, limitada por la cantidad maxima MAX_COLA
	std::queue<char*> colaDeMensaje;
	
	//semaforos
	HANDLE ghSemMutex;
	HANDLE ghSemVacias;
	HANDLE ghSemLLenas;	
public:
	virtual ~ColaBloqueante();
	static ColaBloqueante* getInstance();
	
	void fun_insertar_elemento(char * elemento);
	char * fun_quitar_elemento();
	void crearSemaforos();
	int crearHilos();
	void fun_down(HANDLE semaphore);
	void fun_up(HANDLE semaphore);
	static DWORD WINAPI productor(LPVOID lpParam);
	static DWORD WINAPI consumidor(LPVOID lpParam);
	DWORD WINAPI fun_productor(LPVOID lpParam);
	DWORD WINAPI fun_consumidor(LPVOID lpParam);
	char * fun_producir_elemento();
	void fun_consumir_elemento(char * elemento);
};

#endif //_COLABLOQUEANTE_H_
