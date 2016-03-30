#include "../include/ColaBloqueante.h"

bool ColaBloqueante::instanceFlag = false;
ColaBloqueante* ColaBloqueante::single = NULL;

ColaBloqueante::ColaBloqueante(){
	this->n_cola = 0;
}

ColaBloqueante::~ColaBloqueante(){
	instanceFlag = false;
}

ColaBloqueante* ColaBloqueante::getInstance(){
    if(! instanceFlag){
        single = new ColaBloqueante();
        instanceFlag = true;
        return single;
    }
    else{
        return single;
    }
}

/**
 * inserta el elemento que se le pasa por argumento
 * @param elemento elemento a insertar
 */
void ColaBloqueante::fun_insertar_elemento(char * elemento){
	printf("\n[TH=%d]fun_insertar_elemento %s de %d",(int)GetCurrentThreadId(),elemento,n_cola);
	colaDeMensaje.push(elemento);
	//cola[n_cola] = elemento;
	n_cola++;
}
/**
 * elimina el ultimo elemento de la cola y decrementa la cantidad de elementos
 * @return retorna el elemento eliminado de la cola
 */
char * ColaBloqueante::fun_quitar_elemento(){
	char * elemento = colaDeMensaje.front();
	printf("\n[TH=%d]fun_quitar_elemento %s de %d",(int)GetCurrentThreadId(),elemento,n_cola);
	//luego de obtener el elemento, se elimina
	colaDeMensaje.pop();
	n_cola--;
	return elemento;
}

void ColaBloqueante::crearSemaforos(){
    ColaBloqueante::ghSemMutex = CreateSemaphore(
        NULL,           // default security attributes
        MAX_SEM_COUNT,  // initial count
        MAX_SEM_COUNT,  // maximum count
        NULL);          // unnamed semaphore
//en este caso vacias inicia con MAX_COLA, pero puede incrementarse hasta la cantidad total que seria MAX_COLA
    ColaBloqueante::ghSemVacias = CreateSemaphore(
        NULL,           // default security attributes
        MAX_COLA,  // initial count
        MAX_COLA,  // maximum count
        NULL);          // unnamed semaphore

//en este caso llenas inicia con 0, pero puede incrementarse hasta la cantidad total que seria MAX_COLA
    ColaBloqueante::ghSemLLenas = CreateSemaphore(
        NULL,           // default security attributes
        0,  // initial count
        MAX_COLA,  // maximum count
        NULL);          // unnamed semaphore
	printf("\nghSemMutex %d",(int)ghSemMutex);
	printf("\nghSemVacias %d",(int)ghSemVacias);
	printf("\nghSemLLenas %d",(int)ghSemLLenas);
}

int ColaBloqueante::crearHilos(){
    HANDLE aThreadProducer;
    HANDLE aThreadProducerDos;
	HANDLE aThreadConsumer;
	HANDLE aThreadConsumerDos;
    DWORD ThreadID,ThreadIDC,ThreadIDP2,ThreadIDC2;
    // Create worker threads
    aThreadProducer = CreateThread(
                 NULL,       // default security attributes
                 0,          // default stack size
                 (LPTHREAD_START_ROUTINE) &ColaBloqueante::productor,
                 NULL,       // no thread function arguments
                 0,          // default creation flags
                 &ThreadID); // receive thread identifier

    aThreadConsumer = CreateThread(
                 NULL,       // default security attributes
                 0,          // default stack size
                 (LPTHREAD_START_ROUTINE) &ColaBloqueante::consumidor,
                 NULL,       // no thread function arguments
                 0,          // default creation flags
                 &ThreadIDC); // receive thread identifier

    aThreadProducerDos = CreateThread(
                 NULL,       // default security attributes
                 0,          // default stack size
                 (LPTHREAD_START_ROUTINE) &ColaBloqueante::productor,
                 NULL,       // no thread function arguments
                 0,          // default creation flags
                 &ThreadIDP2); // receive thread identifier
    aThreadConsumerDos = CreateThread(
                 NULL,       // default security attributes
                 0,          // default stack size
                 (LPTHREAD_START_ROUTINE) &ColaBloqueante::consumidor,
                 NULL,       // no thread function arguments
                 0,          // default creation flags
                 &ThreadIDC2); // receive thread identifier

    if( aThreadProducer == NULL ){
        printf("CreateThread error: %d\n", (int)GetLastError());
        return 1;
    }
    if( aThreadProducerDos == NULL ){
        printf("CreateThread error: %d\n", (int)GetLastError());
        return 1;
    }
    if( aThreadConsumer == NULL ){
        printf("CreateThread error: %d\n", (int)GetLastError());
        return 1;
    }
	if( aThreadConsumerDos == NULL ){
        printf("CreateThread error: %d\n", (int)GetLastError());
        return 1;
    }
		// Wait for all threads to terminate
	WaitForSingleObject(aThreadProducer,INFINITE);
	WaitForSingleObject(aThreadConsumer,INFINITE);
	WaitForSingleObject(aThreadConsumerDos,INFINITE);
	WaitForSingleObject(aThreadProducerDos,INFINITE);

	CloseHandle(aThreadProducer);
	CloseHandle(aThreadConsumer);
	CloseHandle(aThreadProducerDos);
	CloseHandle(aThreadConsumerDos);

    CloseHandle(ghSemMutex);
    CloseHandle(ghSemVacias);
    CloseHandle(ghSemLLenas);
	return 0;
}

/*
 * decrementa el valor del semaforo y segun el caso se bloquea AQUI
 * se queda esperando hasta que el semaforo este signaled
 * */
void ColaBloqueante::fun_down(HANDLE semaphore){
	printf("\n[TH=%d]fun_down sem=%d",(int)GetCurrentThreadId(),(int)semaphore);
	DWORD dwWaitResult;
	//este seria el DOWN del producer/consumer
	dwWaitResult = WaitForSingleObject(
	    semaphore,   // handle to semaphore
	    INFINITE);// 0L);           // zero-second time-out interval
	printf("\n[TH=%d]dwWaitResult %d",(int)GetCurrentThreadId(),(int)dwWaitResult);
}

/*
 * incrementa el valor del semaforo
 * */
void ColaBloqueante::fun_up(HANDLE semaphore){
	printf("\n[TH=%d]fun_up sem=%d",(int)GetCurrentThreadId(),(int)semaphore);
	ReleaseSemaphore(
	    semaphore,  // handle to semaphore
	    1,            // increase count by one
	    NULL);
}

DWORD WINAPI ColaBloqueante::productor(LPVOID lpParam){
	ColaBloqueante * instan = ColaBloqueante::getInstance();
	return instan->fun_productor(lpParam);
}

DWORD WINAPI ColaBloqueante::consumidor(LPVOID lpParam){
	ColaBloqueante * instan = ColaBloqueante::getInstance();
	return instan->fun_consumidor(lpParam);
}

/**
 * funcion que ejecuta el productor para generar mensajes en la cola
 */
DWORD WINAPI ColaBloqueante::fun_productor(LPVOID lpParam){
	int iter = MAX_ITER;
//	return true;
	printf("\n[TH=%d]PROD",(int)GetCurrentThreadId());
	char * elemento;
	while(true && --iter>0){
		Sleep(3000);
		printf("\n---\n");
		fun_down(ghSemVacias);
		fun_down(ghSemMutex);
		elemento = fun_producir_elemento();
		fun_insertar_elemento(elemento);
		fun_up(ghSemMutex);
		fun_up(ghSemLLenas);
		printf("\n---\n");
	}
	return TRUE;
}
/**
 * funcion que ejecuta el consumidor para consumir mensajes de la cola
 */
DWORD WINAPI ColaBloqueante::fun_consumidor(LPVOID lpParam){
	int iter = MAX_ITER;
//	return true;
	printf("\n[TH=%d]CONS",(int)GetCurrentThreadId());
	char * elemento;
	while(true && --iter>0){
		Sleep(1000);
		printf("\n++++\n");
		fun_down(ghSemLLenas);
		fun_down(ghSemMutex);
		elemento = fun_quitar_elemento();
		fun_up(ghSemMutex);
		fun_up(ghSemVacias);
		fun_consumir_elemento(elemento);
		printf("\n++++\n");
	}
	return TRUE;
}

/**
 * funcion para crear elementos a insertar
 * @return retorna un elemento aleatorio
 */
char * ColaBloqueante::fun_producir_elemento(){
	char * elem = new char[20];
	int valor = (11*rand() % 100) + 3;
	sprintf(elem,"%d",valor);
	return elem;
	
}

/**
 * @param elemento, elemento a procesar
 */
void ColaBloqueante::fun_consumir_elemento(char * elemento){
	printf("\n[TH=%d]fun_consumir_elemento %s",(int)GetCurrentThreadId(),elemento);

}
