#include "Movimiento.h"
#include "Avion.h"
#include "Mapa.h"
#include "ConfiguracionJuegoXML.h"
#include "Graficador.h"
#include "FondoInicio.h"
#include <vector>
#include "Juego.h"

using namespace std;

bool Juego::instanceFlag = false;
Juego* Juego::instance = NULL;

Juego* Juego::getInstance() {

	if(!instanceFlag){
        instance = new Juego();
        instanceFlag = true;
    }
    return instance;
}

Juego::Juego(){

	SDL_Window* gWindow = NULL;
	SDL_Renderer* gRenderer = NULL;

	mut = SDL_CreateMutex();
}

Juego::~Juego(){

	SDL_DestroyMutex(mut);

	close();
}

// Inicializacion
bool Juego::init() {

	//Initialization flag
	bool success = true;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			printf( "Warning: Linear texture filtering not enabled!" );
		}

		//Create window

		gWindow = SDL_CreateWindow( "1942", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( gWindow == NULL )
		{
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			//Create vsynced renderer for window
			gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
			if( gRenderer == NULL )
			{
				printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if( !( IMG_Init( imgFlags ) & imgFlags ) )
				{
					printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
					success = false;
				}
			}
		}
	}

	return success;
}

void Juego::close() {

	SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	gRenderer = NULL;

	IMG_Quit();
	SDL_Quit();
}

void Juego::configuracionInicial() {

	bool jugar = false;
	SDL_Event e;

	FondoInicio fondo("fondoInicio.bmp", gRenderer);

	// TODO: PENDIENTE INICIAR LA PARTIDA CUANDO TODOS LOS USUARIOS ESTEN CONECTADOS
	while( !jugar ) {

		while( SDL_PollEvent( &e ) != 0 ) {

			if (e.type == SDL_KEYUP) jugar = true;
		}

		SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
		SDL_RenderClear( gRenderer );

		fondo.render();

		SDL_RenderPresent( gRenderer );
	}
}

void Juego::ejecutar() {

	// Si se pudo iniciar la ventana del juego
	if(!init())
		return;

	configuracionInicial();

	static int tamanioMaximoMapa = 2000;
	bool quit = false;
	SDL_Event e;

	ConfiguracionJuegoXML::getInstance()->setCaracteristicasMapa("bg.bmp", "isla.bmp", "carrier.bmp", tamanioMaximoMapa);
	ConfiguracionJuegoXML::getInstance()->setCaracteristicasAvion(1, "f22b.bmp", 6, 113, 195, 10);
	//ConfiguracionJuegoXML::getInstance()->setCaracteristicasAvion(2,"mig51.bmp", 6, 102, 195, 10);
	ConfiguracionJuegoXML::getInstance()->setCaracteristicasProyectil("proyectilAvion.bmp", 1, 11, 25, 1);

	// Test para ver si se grafican otros aviones
	Graficador::getInstance()->inicializar(gRenderer);
	Graficador::getInstance()->cargarDatosAvion(2, "mig51.bmp", 6, 102, 195);
	//Graficador::getInstance()->cargarDatosAvion(1, "f22b.bmp", 6, 113,195);

	Mapa::getInstace()->inicializar(gRenderer);
	Mapa::getInstace()->crearIslaEn(1, 300);
	Mapa::getInstace()->crearIslaEn(300, 800);
	Mapa::getInstace()->crearIslaEn(50, 500);
	Mapa::getInstace()->crearCarrierEn(300, 1200);
	Mapa::getInstace()->crearCarrierEn(200, 1);

	Avion avion(gRenderer);

	/*------------------------------------------------------------------*/
	//Clear screen
	SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
	SDL_RenderClear( gRenderer );

	//Render background
	Mapa::getInstace()->graficar();

	//Render sprite
	avion.render();

	SDL_RenderPresent( gRenderer );

	// TODO: VOLAR LO QUE SIGUE ahora solo queda para dar tiempo a empezar en "paralelo"
	int test = 0;
	while(test < 1000000000)
		test++;
	/*------------------------------------------------------------------*/
	EstadoAvion* estadoAnterior = NULL;

	//Mientras el usuario no desee salir
	while( !quit ) {

		//Agrego los eventos
		while( SDL_PollEvent( &e ) != 0 ) {

			// Si se desea salir del juego
			if( e.type == SDL_QUIT || (e.type == SDL_KEYUP && e.key.keysym.sym == SDLK_ESCAPE) ) {

				quit = true;
			}

			if( e.type == SDL_KEYUP && e.key.keysym.sym == SDLK_r)
				Mapa::getInstace()->reiniciar();

			// Registrar mov del teclado
			avion.handleEvent( e );
		}

		//// Envio los movimientos del avion solo si cambiaron
		// TODO2: redefinir los operadores == != en estadoAvion.
		EstadoAvion* estadoActual = avion.getEstado();

		if(estadoAnterior == NULL || !(estadoAnterior->getFrame() == estadoActual->getFrame()
			&& estadoAnterior->getPosX() == estadoActual->getPosX() && estadoAnterior->getPosY() == estadoActual->getPosY()))
		{
			estadoAnterior = estadoActual;
			notificarMovimiento(estadoActual->getId(), 1, estadoActual->getPosX(), estadoActual->getPosY());
		}
		else {
			delete estadoActual;
		}

		//Clear screen
		SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
		SDL_RenderClear( gRenderer );

		//Render background
		Mapa::getInstace()->graficar();

		avion.mover();

		//Render sprite
		avion.render();

		Graficador::getInstance()->graficarMovimientos(movimientosDeCompetidores);

		//Update screen
		SDL_RenderPresent( gRenderer );
	}

	close();
}

void Juego::actualizarMovimientos(Movimiento* movimiento){

	SDL_mutexP(mut);

	int idAvion = movimiento->getId();
	map<int,Movimiento*>::iterator  it = Juego::getInstance()->movimientosDeCompetidores.find(idAvion);

	if( it != Juego::getInstance()->movimientosDeCompetidores.end() ){

		it->second->setTipo(movimiento->getTipo());
		it->second->setPosX(movimiento->getPosX());
		it->second->setPosY(movimiento->getPosY());

		delete movimiento;
	}
	else{

		Juego::getInstance()->movimientosDeCompetidores[idAvion] = movimiento;
	}

	SDL_mutexV(mut);
}

void Juego::notificarMovimiento(int id, int tipo, int x, int y){

	vector<void*> argv;

	argv.push_back(new Movimiento(id, tipo, x, y));

	// indicar bien la cantidad de valores que son enviados
	notificar(0, &argv[0]);
}

