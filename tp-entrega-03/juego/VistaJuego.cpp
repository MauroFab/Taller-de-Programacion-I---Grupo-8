#include "VistaJuego.h"

VistaJuego* VistaJuego::instance = NULL;

VistaJuego* VistaJuego::getInstance() {
	if(instance == NULL){
        instance = new VistaJuego();
    }
    return instance;
}

VistaJuego::VistaJuego(){
	this->jugador = new Jugador();
	this->ventanaAncho = 0;
	this->ventanaAlto = 0;
	gWindow = NULL;
	gRenderer = NULL;
	this->estadoJuego = NULL;
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
	this->balaView = NULL;
	this->controlador = new ControladorTeclado();
}

VistaJuego::~VistaJuego(){
	delete this->jugador;
	SDL_DestroyMutex(mut);
	close();
	//liberar elementos de la vista
	for(int i = 0; i < MAX_ELEM_VIEW; i++){
		if (this->listaElemView[i] != NULL)
			delete this->listaElemView[i];
	}
	this->canElemV = 0;
	//liberar aviones de la vista
	for(int i = 0; i < MAX_AVION_VIEW; i++){
		if (this->listaAvionView[i] != NULL)
			delete this->listaAvionView[i];
	}
	this->canAvionV = 0;
}

int VistaJuego::readServidorXml(ServidorXml * servidorXml){
	return this->readFrom(servidorXml);
}

int VistaJuego::readFrom(IGenericaVO * objetoXML){
	ServidorXml * tempServidorXml = (ServidorXml*)objetoXML;
	//carga las dimensiones de la ventana
	this->ventanaAncho = tempServidorXml->getVentanaXmlCopy()->getAncho();
	this->ventanaAlto = tempServidorXml->getVentanaXmlCopy()->getAlto();
	return 0;
}

bool VistaJuego::inicializar() {

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
		titulo.append("1942-[");
		titulo.append(this->jugador->nombreDeUsuario);
		titulo.append("]");
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
				 //Initialize SDL_mixer
				if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 ){
					printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
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

	return success;
}

void VistaJuego::close() {
	SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	gRenderer = NULL;

	Mix_Quit();
	IMG_Quit();
	SDL_Quit();
}

void VistaJuego::dibujarFondoInicio() {

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

void VistaJuego::inicializarMusica() {

	Mix_Music * musicaPrincipal = Mix_LoadMUS( "./Musica/Musica_Principal.wav" );
	CacheSonido::getInstance()->addMusic(musicaPrincipal, NIVEL_1);
	Mix_Chunk* disparo = Mix_LoadWAV( "./Musica/Disparo.wav" );
	CacheSonido::getInstance()->addChunk(disparo, DISPARO);
	Mix_Chunk* explosion = Mix_LoadWAV( "./Musica/Explosion.wav" );
	CacheSonido::getInstance()->addChunk(explosion, EXPLOSION);
}

void VistaJuego::setJugar(){
	jugar = true;
}

Jugador * VistaJuego::getJugador(){
	return this->jugador;
}

int VistaJuego::cargarElementos(ServidorXml * confServidorXml){
	//sprites
	int cantS = confServidorXml->getCanSprs();
	SpriteXml ** listaS = confServidorXml->getListaSprites();

	//elementos
	int cantE = confServidorXml->getEscenarioXmlCopy()->getCanElems();
	ElementoXml ** listaE = confServidorXml->getEscenarioXmlCopy()->getListaElementos();
	for(int i = 0;i <cantE; i++){
		ElementoXml * elemX = listaE[i];
		//se obtiene el id del sprite a buscar y luego se obtiene ese sprite
		SpriteXml * spriteX = SpriteXml::findSpriteById(elemX->getIdSprite(),listaS,cantS);
		if (spriteX != NULL){	//solo en caso de encontrarlo
			ElementoModel * elemModel = new ElementoModel(elemX);
			this->listaElemView[i] = new ElementoView(elemModel,spriteX);
			this->canElemV++;
		}
	}
	return 0;
}
//---carga de aviones de la vista
int VistaJuego::cargarAviones(ServidorXml * confServidorXml){
	//sprites
	int cantS = confServidorXml->getCanSprs();
	SpriteXml ** listaS = confServidorXml->getListaSprites();
	//aviones
	int cantA = confServidorXml->getCanAvs();
	AvionXml ** listaA = confServidorXml->getListaAviones();
	for(int i = 0;i <cantA; i++){
		AvionXml * avionX = listaA[i];
		//se obtiene el id del sprite a buscar y luego se obtiene ese sprite
		SpriteXml * spriteX = SpriteXml::findSpriteById(avionX->getIdSpAvion(),listaS,cantS);
		if (spriteX != NULL){	//solo en caso de encontrarlo
			AvionModel * avionModel = new AvionModel(avionX);
			this->listaAvionView[i] = new AvionView(avionModel,spriteX);
			this->canAvionV++;
		}
	}
	return 0;
}

int VistaJuego::cargarFondo(ServidorXml * confServidorXml,int altoFondo){
	FondoXml * fondoXml = confServidorXml->getEscenarioXmlCopy()->getFondoXmlCopy();
	FondoModel * fondoModel = new FondoModel(fondoXml);
	//sprites
	int cantS = confServidorXml->getCanSprs();
	SpriteXml ** listaS = confServidorXml->getListaSprites();
	//se obtiene el id del sprite a buscar y luego se obtiene ese sprite
	SpriteXml * spriteX = SpriteXml::findSpriteById(fondoXml->getIdSprite(),listaS,cantS);
	this->fondoView = new FondoView(fondoModel,spriteX);
	this->fondoView->altoFondo = altoFondo;
	return 0;
}

int VistaJuego::cargarBala(ServidorXml * confServidorXml){
	//del 1er avion se toman los datos de una bala
	AvionXml ** listaA = confServidorXml->getListaAviones();
	AvionXml * avionXml_0 = listaA[0];
	BalaModel * balaModel = new BalaModel(avionXml_0);
	//sprites
	int cantS = confServidorXml->getCanSprs();
	SpriteXml ** listaS = confServidorXml->getListaSprites();
	//se obtiene el id del sprite a buscar y luego se obtiene ese sprite
	SpriteXml * spriteX = SpriteXml::findSpriteById(avionXml_0->getIdSpBala(),listaS,cantS);
	AvionView * avionV_0 = this->listaAvionView[0];
	this->balaView = new BalaView(balaModel,spriteX);
	return 0;
}

//operaciones de reset
//se encarga del reset de los elementos liberando la memoria usada por los objetos
//tanto de la view como de los que estos contienen
int VistaJuego::resetElementos(){
	//liberar elementos de la vista
	for(int i = 0; i < MAX_ELEM_VIEW; i++){
		if (this->listaElemView[i] != NULL){
			delete this->listaElemView[i];
			this->listaElemView[i] = NULL;
		}

	}
	this->canElemV = 0;
	return 0;
}
//se encarga del reset de los aviones liberando la memoria usada por los objetos
//tanto de la view como de los que estos contienen
int VistaJuego::resetAviones(){
	//liberar aviones de la vista
	for(int i = 0; i < MAX_AVION_VIEW; i++){
		if (this->listaAvionView[i] != NULL){
			delete this->listaAvionView[i];
			this->listaAvionView[i] = NULL;
		}
	}
	this->canAvionV = 0;
	return 0;
}

//Se que no es correcto proteger todo el metodo con un mutex, peroooo el señor
// hilo recibir_mensajes esta tocando cosas que solo el hilo main deberia de tocar
// el hilo recibir_mensajes solo deberia de notificar los cambios.
void VistaJuego::reiniciar(ServidorXml * confServidorXml, int posicionInicialMapa) {
	SDL_mutexP(mut);
	resetElementos();
	resetAviones();
	static int tamanioMaximoMapa = 2000;
	cargarElementos(confServidorXml);
	cargarAviones(confServidorXml);
	cargarFondo(confServidorXml,tamanioMaximoMapa);
	cargarBala(confServidorXml);

	Graficador::getInstance()->inicializar(gRenderer, this->ventanaAncho, this->ventanaAlto);
	Graficador::getInstance()->agregarDatosAviones(this->listaAvionView, this->canAvionV);
	Graficador::getInstance()->agregarDatosBala(this->balaView);
	Graficador::getInstance()->agregarDatosMapa(this->fondoView, this->listaElemView, this->canElemV, posicionInicialMapa);
	Graficador::getInstance()->reiniciarMapa();

	SDL_mutexV(mut);
}

//Como no los cargo del xml, lo cargo desde aca.
void VistaJuego::agregarDatosDeAvionesEnemigosHardcodeados(){
	char spriteStr[20] = "nave";
	char path[100] = "nave_mediana.bmp";

	//Que la id sea 100 fue una convencion para los aviones enemigos. Minimamente
	//Se cambiare a una constante con nombre
	SpriteXml* spriteNaveEnemiga = new SpriteXml(100, spriteStr,path,1,68,120);
	AvionXml* avionXml = new AvionXml(100,5,5,100,spriteStr,5,"asd",3,"zxc");
	AvionModel* avionModel = new AvionModel(avionXml);
	AvionView** avionView = new AvionView*;
	avionView[0] = new AvionView(avionModel,spriteNaveEnemiga);
	Graficador::getInstance()->agregarDatosAviones(avionView,1);
}

void VistaJuego::ejecutar(ServidorXml * confServidorXml, int posicionInicialMapa) {

	static int tamanioMaximoMapa = 2000;
	cargarElementos(confServidorXml);
	cargarAviones(confServidorXml);
	cargarFondo(confServidorXml,tamanioMaximoMapa);
	cargarBala(confServidorXml);

 	dibujarFondoInicio();
	inicializarMusica();

	/*Se inicializa y se cargan los datos en el Graficador*/

	Graficador::getInstance()->inicializar(gRenderer, this->ventanaAncho, this->ventanaAlto);
	Graficador::getInstance()->agregarDatosAviones(this->listaAvionView, this->canAvionV);
	Graficador::getInstance()->agregarDatosBala(this->balaView);
	Graficador::getInstance()->agregarDatosMapa(this->fondoView, this->listaElemView, this->canElemV, posicionInicialMapa);

	agregarDatosDeAvionesEnemigosHardcodeados();
	/*------------------------------------------------------------------*/

	SDL_Event e;
	bool quit = false;

	// Reproduce el tema de fondo
	Mix_PlayMusic( CacheSonido::getInstance()->getMusic(NIVEL_1), -1 );

	//Mientras el usuario no desee salir
	while( !quit ) {
		//Agrego los eventos
		while( SDL_PollEvent( &e ) != 0 ) {

			// Si se desea salir del juego
			if( e.type == SDL_QUIT || (e.type == SDL_KEYUP && e.key.keysym.sym == SDLK_ESCAPE) ) {

				quit = true;
			}
			//Notifica al servidor de lo presionado
			controlador->procesarTeclasPresionadas( e );
		}

		//Clear screen
		SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
		SDL_RenderClear( gRenderer );

		SDL_mutexP(mut);
		Graficador::getInstance()->graficarJuego(estadoJuego, jugador->getIdCliente());
		
		SDL_mutexV(mut);

		//Update screen
		SDL_RenderPresent( gRenderer );
	}

	// Detiene la musica
	Mix_HaltMusic();

	close();
}

void VistaJuego::actualizarEstadoJuego(EstadoJuego* estadoJuego){
	SDL_mutexP(mut);
	if(estadoJuego != NULL)
		delete this->estadoJuego;
	this->estadoJuego = estadoJuego;
	SDL_mutexV(mut);
}

void VistaJuego::agregarObservador(Observador* observador){
	this->controlador->agregarObservador(observador);
}