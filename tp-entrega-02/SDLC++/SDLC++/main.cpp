#include "Avion.h"
#include "Mapa.h"
#include "ConfiguracionJuegoXML.h"
#include "Graficador.h"

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The window renderer
SDL_Renderer* gRenderer = NULL;

// Inicializacion
bool init() {

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

void close() {

	//Destroy window	
	SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}


void configuracionInicial() {

}

void juego1942() {

	if( !init() ) {

		printf( "Failed to initialize!\n" );
	}
	else {

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

		//While application is running
		while( !quit ) {

			//Handle events on queue
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
			std::list<EstadoAvion*> lista;
			lista.push_back(new EstadoAvion(id, 0, 200, 200));
			Graficador::getInstance()->graficarAviones(lista);

			//Update screen
			SDL_RenderPresent( gRenderer );
		}
	}
}

int main( int argc, char* args[] ) {

	configuracionInicial();

	juego1942();

	close();

	return 0;
}
