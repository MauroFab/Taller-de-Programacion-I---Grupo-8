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
	this->ventanaAncho = 0;
	this->ventanaAlto = 0;	
	//TODO los siguientes datos no se estan usando, deberian ser atributo no variables en otro metodo
	SDL_Window* gWindow = NULL;
	SDL_Renderer* gRenderer = NULL;
	mut = SDL_CreateMutex();
	jugar=false;
}

Juego::~Juego(){
	SDL_DestroyMutex(mut);
	close();
}
int Juego::readServidorXml(ServidorXml * servidorXml){
	return this->readFrom(servidorXml);
}

int Juego::readFrom(IGenericaVO * objetoXML){
	ServidorXml * tempServidorXml = (ServidorXml*)objetoXML;
	//carga la cantidad total de aviones 
	int canAvs = tempServidorXml->getCanAvs();
	//carga las dimensiones de la ventana
	this->ventanaAncho = tempServidorXml->getVentanaXmlCopy()->getAncho();
	this->ventanaAlto = tempServidorXml->getVentanaXmlCopy()->getAlto();
	return 0;
}

// Inicializacion
bool Juego::init() {
	//Initialization flag
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
		gWindow = SDL_CreateWindow( "1942", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, this->ventanaAncho, this->ventanaAlto, SDL_WINDOW_SHOWN );
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

	FondoInicio fondo("fondoInicio.bmp", gRenderer);

	while( !jugar ) {

		SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
		SDL_RenderClear( gRenderer );

		fondo.render();

		SDL_RenderPresent( gRenderer );
	}
}

void Juego::setJugar(){
	jugar=true;
}

void Juego::ejecutar() {

	// Si se pudo iniciar la ventana del juego
	if(!init())
		return;

	configuracionInicial();
	// usar el flag para indicar que se puede jugar, no en necesario protegerlo, pues solo uno escribe
	// no importa si se pierde unos loops
	// seria mejor lanzar un evento, pero por ahora que quede asi.

	SDL_Delay(5000); // comienza en 5 seg luego que dio el ok el server
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
	Graficador::getInstance()->cargarDatosProyectil("proyectilAvion.bmp", 1, 11, 25);

	Mapa::getInstace()->inicializar(gRenderer);
	Mapa::getInstace()->crearIslaEn(1, 300);
	Mapa::getInstace()->crearIslaEn(300, 800);
	Mapa::getInstace()->crearIslaEn(50, 500);
	Mapa::getInstace()->crearCarrierEn(300, 1200);
	Mapa::getInstace()->crearCarrierEn(200, 1);

	Avion avion(gRenderer,this->ventanaAncho,this->ventanaAlto);

	/*------------------------------------------------------------------*/
	//Clear screen
	SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
	SDL_RenderClear( gRenderer );

	//Render background
	Mapa::getInstace()->graficar();

	//Render sprite
	avion.render();

	SDL_RenderPresent( gRenderer );
	
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

		//Clear screen
		SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
		SDL_RenderClear( gRenderer );

		//Render background
		Mapa::getInstace()->graficar();

		avion.mover();

		notificarMovimiento(avion.getEstado());

		//Render sprite
		avion.render();

		Graficador::getInstance()->graficarAviones(movimientosDeCompetidores);

		//Update screen
		SDL_RenderPresent( gRenderer );
	}

	close();
}

void Juego::actualizarMovimientos(EstadoAvion* estadoAvion){

	SDL_mutexP(mut);

	int idAvion = estadoAvion->getId();

	EstadoAvion* estadoAnterior = Juego::getInstance()->movimientosDeCompetidores[idAvion];

	delete estadoAnterior;

	Juego::getInstance()->movimientosDeCompetidores[idAvion] = estadoAvion;

	SDL_mutexV(mut);
}

void Juego::notificarMovimiento(EstadoAvion* estadoAvion){

	vector<void*> argv;

	argv.push_back(estadoAvion);

	notificar(0, &argv[0]);
}

