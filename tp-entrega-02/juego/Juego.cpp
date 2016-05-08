#include "Avion.h"
#include "Mapa.h"
#include "ConfiguracionJuegoXML.h"
#include "Graficador.h"

#include "Juego.h"

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
}

Juego::~Juego(){
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

		gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
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

void Juego::cargarConfiguracion() {

	static int tamanioMaximoMapa = 2000;

	ConfiguracionJuegoXML::getInstance()->setCaracteristicasMapa("bg.bmp", "isla.bmp", "carrier.bmp", tamanioMaximoMapa);
	ConfiguracionJuegoXML::getInstance()->setCaracteristicasAvion(1, "f22b.bmp", 6, 113, 195, 10);
	ConfiguracionJuegoXML::getInstance()->setCaracteristicasProyectil("proyectilAvion.bmp", 1, 11, 25, 1);
}

void Juego::ejecutar() {

	// Si se pudo iniciar la ventana del juego
	if(!init())
		return;

	static int tamanioMaximoMapa = 2000;
	bool quit = false;
	SDL_Event e;

	ConfiguracionJuegoXML::getInstance()->setCaracteristicasMapa("bg.bmp", "isla.bmp", "carrier.bmp", tamanioMaximoMapa);
	ConfiguracionJuegoXML::getInstance()->setCaracteristicasAvion(1, "f22b.bmp", 6, 113, 195, 10);
	ConfiguracionJuegoXML::getInstance()->setCaracteristicasProyectil("proyectilAvion.bmp", 1, 11, 25, 1);

	// Test para ver si se grafican otros aviones
	static int id = 2;
	Graficador::getInstance()->inicializar(gRenderer);
	Graficador::getInstance()->cargarDatosAvion(id, "mig51.bmp", 6, 102, 195);

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

	// Test del graficador
	std::list<EstadoAvion*> aviones;
	aviones.push_back(new EstadoAvion(id, 0, 200, 200));
	Graficador::getInstance()->graficarAviones(aviones);

	SDL_RenderPresent( gRenderer );

	int test = 0;
	while(test < 1000000000)
		test++;
	/*------------------------------------------------------------------*/

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

		//Clear screen
		SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
		SDL_RenderClear( gRenderer );

		//Render background
		Mapa::getInstace()->graficar();

		avion.mover();

		//Render sprite
		avion.render();

		// Test del graficador
		std::list<EstadoAvion*> aviones;
		aviones.push_back(new EstadoAvion(id, 0, 200, 200));
		Graficador::getInstance()->graficarAviones(aviones);

		//Update screen
		SDL_RenderPresent( gRenderer );
	}
}


