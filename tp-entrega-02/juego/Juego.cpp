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
	this->jugador = new Jugador();
	this->ventanaAncho = 0;
	this->ventanaAlto = 0;	
	gWindow = NULL;
	gRenderer = NULL;
	mut = SDL_CreateMutex();
	jugar=false;
	//inicializar elementos de la vista
	for(int i = 0; i < MAX_ELEM_VIEW; i++){
		this->listaElemView[i] = NULL;
	}
	this->canElemV = 0;
	//inicializar aviones de la vista
	for(int i = 0; i < MAX_AVION_VIEW; i++){
		this->listaAvionView[i] = NULL;
	}
	this->canAvionV = 0;
}

Juego::~Juego(){
	delete this->jugador;
	SDL_DestroyMutex(mut);
	close();
	//liberar elementos de la vista
	for(int i = 0; i < MAX_ELEM_VIEW; i++){
		if (this->listaElemView[i] != NULL)
			delete this->listaElemView[i];
	}	
}

int Juego::readServidorXml(ServidorXml * servidorXml){
	return this->readFrom(servidorXml);
}

int Juego::readFrom(IGenericaVO * objetoXML){
	ServidorXml * tempServidorXml = (ServidorXml*)objetoXML;
	//carga las dimensiones de la ventana
	this->ventanaAncho = tempServidorXml->getVentanaXmlCopy()->getAncho();
	this->ventanaAlto = tempServidorXml->getVentanaXmlCopy()->getAlto();
	return 0;
}

// Inicializacion
bool Juego::initSDL() {
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

void Juego::dibujarFondoInicio() {

	FondoInicio fondo(PATH_FONDO_INICIO, gRenderer);

	while( !jugar ) {
		SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
		//se limpia la pantalla
		SDL_RenderClear( gRenderer );
		fondo.render();
		//actualiza la pantalla
		SDL_RenderPresent( gRenderer );
	 }
}

void Juego::setJugar(){
	jugar = true;
}
int Juego::cargarElementos(ServidorXml * confServidorXml){
	//sprites
	int cantS = confServidorXml->getCanSprs();
	SpriteXml ** listaS = confServidorXml->getListaSprites();
	
	//elementos
	int cantE = confServidorXml->getEscenarioXmlCopy()->getCanElems();
	ElementoXml ** listaE = confServidorXml->getEscenarioXmlCopy()->getListaElementos();
	for(int i = 0;i <cantE; i++){
		ElementoXml * elemX = listaE[i];
		ElementoModel * elemModel = new ElementoModel(elemX);
		//se obtiene el id del sprite a buscar
		int idSp = elemX->getIdSprite();
		int bOut = false;
		SpriteXml * spriteX = NULL;
		for (int j = 0;j <cantS && !bOut;j++){
			spriteX = listaS[j];
			if (idSp == spriteX->getId()){
				bOut = true;
			}
		}
		this->listaElemView[i] = new ElementoView(elemModel,spriteX);
		this->canElemV++;
	}
	return 0;
}
//---carga de aviones de la vista
int Juego::cargarAviones(ServidorXml * confServidorXml){
	//sprites
	int cantS = confServidorXml->getCanSprs();
	SpriteXml ** listaS = confServidorXml->getListaSprites();

	//aviones
	int cantA = confServidorXml->getCanAvs();
	AvionXml ** listaA = confServidorXml->getListaAviones();
	for(int i = 0;i <cantA; i++){
		AvionXml * avionX = listaA[i];
		AvionModel * avionModel = new AvionModel(avionX);
		//se obtiene el id del sprite a buscar
		int idSp = avionX->getIdSpAvion();
		int bOut = false;
		SpriteXml * spriteX = NULL;
		for (int j = 0;j <cantS && !bOut;j++){
			spriteX = listaS[j];
			if (idSp == spriteX->getId()){
				bOut = true;
			}
		}
		this->listaAvionView[i] = new AvionView(avionModel,spriteX);
		this->canAvionV++;
	}
	return 0;
}
Jugador * Juego::getJugador(){
	return this->jugador;
}

void Juego::ejecutar(ServidorXml * confServidorXml) {

	// Si se pudo iniciar la ventana del juego
	if(!initSDL())
		return;
		
	cargarElementos(confServidorXml);
	cargarAviones(confServidorXml);

 	dibujarFondoInicio();

	static int tamanioMaximoMapa = 2000;
	bool quit = false;

	ConfiguracionJuegoXML::getInstance()->setCaracteristicasMapa("bg.bmp", tamanioMaximoMapa);
	
	ConfiguracionJuegoXML::getInstance()->setCaracteristicasProyectil("disparo_1.bmp", 1, 11, 25, 1);

	Graficador * instGraficador = Graficador::getInstance();
	// Test para ver si se grafican otros aviones
	instGraficador->inicializar(gRenderer);
	
	//se cargan los aviones de la vista a la clase que luego los grafica
	for(int v = 0; v < this->canAvionV; v++){
		AvionView * avionV = this->listaAvionView[v];
		instGraficador->agregarDatosAvion(avionV);
	}	
	Graficador::getInstance()->cargarDatosProyectil("disparo_1.bmp", 1, 11, 25);

	Mapa::getInstace()->inicializar(gRenderer);

	for(int e = 0; e < this->canElemV; e++){
		ElementoView * elemV = this->listaElemView[e];
		Mapa::getInstace()->crearElemento(elemV);
	}

	int id_cliente = this->jugador->getIdCliente();
	Avion avion(gRenderer,this->ventanaAncho,this->ventanaAlto,this->listaAvionView[id_cliente]);
	avion.setPosicion(this->jugador->getPosicion());

	/*------------------------------------------------------------------*/
	
	SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
	//Clear screen
	SDL_RenderClear( gRenderer );

	//Render background
	Mapa::getInstace()->dibujarFondoYElementos();

	//Render sprite
	avion.render();
	//se actualiza la pantalla
	SDL_RenderPresent( gRenderer );

	/*------------------------------------------------------------------*/
	SDL_Event e;
	//Mientras el usuario no desee salir
	while( !quit ) {
		//Agrego los eventos
		while( SDL_PollEvent( &e ) != 0 ) {

			// Si se desea salir del juego
			if( e.type == SDL_QUIT || (e.type == SDL_KEYUP && e.key.keysym.sym == SDLK_ESCAPE) ) {

				quit = true;
			}

			if( e.type == SDL_KEYUP && e.key.keysym.sym == SDLK_r){
				//Ese movimiento indica a los demas clientes que deben reiniciar el mapa
				notificarMovimiento(new EstadoAvion(-2,0,0,0));
				Mapa::getInstace()->reiniciar();
			}
			// Registrar mov del teclado
			avion.handleEvent( e );
		}

		//Clear screen
		SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
		SDL_RenderClear( gRenderer );

		//Render background
		Mapa::getInstace()->dibujarFondoYElementos();

		avion.mover();

		notificarMovimiento(avion.getEstado());

//ESTA LINEA debe readptarse pues el modelo requiere actualizacion, en lugar de enviar movimientos
//se deben enviar "posiciones"
		instGraficador->graficarAvionesAll();
		//Render sprite
		avion.render();

		SDL_mutexP(mut);
		Graficador::getInstance()->graficarAviones(movimientosDeCompetidores);
		SDL_mutexV(mut);

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
	notificar(&argv[0]);
}

