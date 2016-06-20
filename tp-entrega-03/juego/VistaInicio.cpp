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
	this->ventanaAncho = WIDTH;
	this->ventanaAlto = HEIGHT;
	gWindow = NULL;
	gRenderer = NULL;
	
}

VistaInicio::~VistaInicio(void) {

	for (int i = 0; i < CANTIDAD_FONDOS; i++) {
		delete this->fondos[i];
	}

	delete this->textoDeEntrada;

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

void VistaInicio::cargarFondos() {

	this->fondos[0] = new FondoInicio(PATH_FONDO_IP, this->gRenderer);
	this->fondos[1] = new FondoInicio(PATH_FONDO_PUERTO, this->gRenderer);
	this->fondos[2] = new FondoInicio(PATH_FONDO_USUARIO, this->gRenderer);
}

void VistaInicio::mostrar() {

	cargarFondos();

	this->textoDeEntrada = new TextField(this->gRenderer, this->gFont);
	this->textoDeEntrada->setPosicion(130, 270);
	
	bool quit = false;
	SDL_Event e;
	int numeroFondo = 0;

	// Se habilita el ingreso de texto
	SDL_StartTextInput();

	FondoInicio* fondoActual = this->fondos[numeroFondo];

	fondoActual->render();

	while( !quit ) {

		while( SDL_PollEvent( &e ) != 0 ) {

			// Si se desea salir del juego
			if( e.type == SDL_QUIT || (e.type == SDL_KEYUP && e.key.keysym.sym == SDLK_ESCAPE) ) {
				quit = true;
			}

			if (e.type == SDL_KEYUP && e.key.keysym.sym == SDLK_RETURN && (textoDeEntrada->getTexto().compare("") != 0)) {
				this->datos[numeroFondo] = textoDeEntrada->getTexto();
				textoDeEntrada->limpiar();
				numeroFondo++;
				fondoActual = this->fondos[numeroFondo];
			} else {
				textoDeEntrada->manejarEvento(e);
			}
		}

		if (numeroFondo == CANTIDAD_FONDOS) {
			quit = true;
		} 
		else {
			SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
			SDL_RenderClear( gRenderer );

			fondoActual->render();
			textoDeEntrada->render();
			
			SDL_RenderPresent( gRenderer );
		}
	}

	// Se desahabilita el ingreso de texto
	SDL_StopTextInput();
}

void VistaInicio::mostrarMensajeInformacion(string mensaje) {

	this->gFont = TTF_OpenFont(FUENTE_PATH, 14 );

	FondoInicio* fondo = new FondoInicio("bg.bmp", this->gRenderer);
	Etiqueta* etiquetaMensaje = new Etiqueta(this->gRenderer, this->gFont, mensaje);
	etiquetaMensaje->setPosicion(13, 270);

	bool quit = false;
	SDL_Event e;

	fondo->render();
	etiquetaMensaje->render();

	while( !quit ) {

		while( SDL_PollEvent( &e ) != 0 ) {

			// Si se desea salir del juego
			if( e.type == SDL_QUIT || (e.type == SDL_KEYUP && e.key.keysym.sym == SDLK_ESCAPE) ) {
				quit = true;
			}
		}

		SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
		SDL_RenderClear( gRenderer );

		fondo->render();
		etiquetaMensaje->render();
			
		SDL_RenderPresent( gRenderer );
	}

	close();
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

string VistaInicio::getIP() {
	return this->datos[IP];
}

string VistaInicio::getPuerto() {
	return this->datos[PUERTO];
}

string VistaInicio::getUsuario() {
	return this->datos[USUARIO];
}