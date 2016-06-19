#include "VistaInicio.h"

bool VistaInicio::instanceFlag = false;
VistaInicio* VistaInicio::instance = NULL;

VistaInicio* VistaInicio::getInstance() {
	if (!instanceFlag) {
		instance = new VistaInicio();
		instanceFlag = true;
	}
	return instance;
}

VistaInicio::VistaInicio() {
	this->ventanaAncho = 0;
	this->ventanaAlto = 0;
	gWindow = NULL;
	gRenderer = NULL;
}

VistaInicio::~VistaInicio(void) {
	close();
}

bool VistaInicio::inicializar() {
	bool success = true;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 ){
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else{
		//Set texture filtering to linear
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) ){
			printf( "Warning: Linear texture filtering not enabled!" );
		}
		//Create window
		string titulo;
		titulo.append("1942-Menu de Inicio");
		gWindow = SDL_CreateWindow(titulo.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, this->ventanaAncho, this->ventanaAlto, SDL_WINDOW_SHOWN );
		if( gWindow == NULL ){
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else{
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
				if( !( IMG_Init( imgFlags ) & imgFlags ) ){
					printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
					success = false;
				}
				 //Initialize SDL_ttf
				if( TTF_Init() == -1 ){
					printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
					success = false;
				}
			}
		}
	}

	gFont = TTF_OpenFont(FUENTE_PATH, 20 );

	return success;
}

void VistaInicio::mostrar() {

	
}

void VistaInicio::close() {

	SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
	TTF_CloseFont( gFont );
	gFont = NULL;
	gWindow = NULL;
	gRenderer = NULL;

	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}