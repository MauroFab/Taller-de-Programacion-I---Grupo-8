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
	//inicializar aviones de la vista
	for(int i = 0; i < MAX_AVION_VIEW; i++){
		this->listaAvionView[i] = NULL;
	}
	this->canAvionV = 0;
	//inicializar escenarios de la vista
	for(int i = 0; i < MAX_ESCENARIO_VIEW; i++){
		this->listaEscenariosView[i] = NULL;
	}
	this->canEscenariosV = 0;
	this->balaView = NULL;
	this->controlador = new ControladorTeclado();
}

VistaJuego::~VistaJuego(){

	delete this->jugador;
	SDL_DestroyMutex(mut);
	close();
	
	//liberar escenarios de la vista
	for(int i = 0; i < MAX_ESCENARIO_VIEW; i++){
		if (this->listaEscenariosView[i] != NULL)
			delete this->listaEscenariosView[i];
	}
	this->canEscenariosV = 0;
	//liberar aviones de la vista
	for(int i = 0; i < MAX_AVION_VIEW; i++){
		if (this->listaAvionView[i] != NULL)
			delete this->listaAvionView[i];
	}
	this->canAvionV = 0;

	if(estadoJuego != NULL){
		delete this->estadoJuego;
	}
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

//---carga de Enemigos de la vista
int VistaJuego::cargarEnemigos(ServidorXml * confServidorXml, EscenarioView* escenarioV, int idEscenario){
	//sprites
	int cantS = confServidorXml->getCanSprs();
	SpriteXml ** listaS = confServidorXml->getListaSprites();
	//Enemigos
	int canEnes = confServidorXml->getListaEscenario()[idEscenario]->getCanEnes();
	AvionEnemigoXml ** listaA = confServidorXml->getListaEscenario()[idEscenario]->getListaEnemigos();
	for(int i = 0;i <canEnes; i++){
		AvionEnemigoXml * avionX = listaA[i];
		//se obtiene el id del sprite a buscar y luego se obtiene ese sprite
		SpriteXml * spriteX = SpriteXml::findSpriteById(avionX->getIdSprite(),listaS,cantS);
		if (spriteX != NULL){	//solo en caso de encontrarlo
			AvionEnemigoModel * avionEnemigoModel = new AvionEnemigoModel(avionX);
			escenarioV->addAvionEnemigoView(new AvionEnemigoView(avionEnemigoModel,spriteX));
		}
	}
	return 0;
}

// carga elementos del escenario correpondiente a idEscenario
int VistaJuego::cargarElementos(ServidorXml * confServidorXml, EscenarioView* escenarioV, int idEscenario){
	//sprites
	int cantS = confServidorXml->getCanSprs();
	SpriteXml ** listaS = confServidorXml->getListaSprites();
	//elementos
	int cantE = confServidorXml->getListaEscenario()[idEscenario]->getCanElems();
	ElementoXml ** listaE = confServidorXml->getListaEscenario()[idEscenario]->getListaElementos();
	for(int i = 0;i <cantE; i++){
		ElementoXml * elemX = listaE[i];
		//se obtiene el id del sprite a buscar y luego se obtiene ese sprite
		SpriteXml * spriteX = SpriteXml::findSpriteById(elemX->getIdSprite(),listaS,cantS);
		if (spriteX != NULL){ //solo en caso de encontrarlo
			ElementoModel * elemModel = new ElementoModel(elemX);
			escenarioV->addElementoView(new ElementoView(elemModel,spriteX));
		}
	}
	return 0;
}

int VistaJuego::cargarEscenarios(ServidorXml* confServidorXml) {
	//sprites
	int cantS = confServidorXml->getCanSprs();
	SpriteXml ** listaS = confServidorXml->getListaSprites();
	//Escenarios
	int cantE = confServidorXml->getCanEsc();
	EscenarioXml ** listaE = confServidorXml->getListaEscenario();
	for (int e = 0; e < cantE; e++) {
		FondoXml* fondoXml = listaE[e]->getFondoXmlCopy();
		FondoModel * fondoModel = new FondoModel(fondoXml);
		//se obtiene el id del sprite a buscar y luego se obtiene ese sprite
		SpriteXml * spriteX = SpriteXml::findSpriteById(fondoXml->getIdSprite(),listaS,cantS);
		if (spriteX != NULL) {
			FondoView* fondoV = new FondoView(fondoModel,spriteX);
			EscenarioView* escenarioV = new EscenarioView(fondoV);
			cargarElementos(confServidorXml, escenarioV, e);
			cargarEnemigos(confServidorXml, escenarioV, e);
			this->listaEscenariosView[e] = escenarioV;
			this->canEscenariosV++;
		}
	}
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

int VistaJuego::resetEscenarios() {
	//liberar aviones de la vista
	for(int i = 0; i < MAX_ESCENARIO_VIEW; i++){
		if (this->listaEscenariosView[i] != NULL){
			delete this->listaEscenariosView[i];
			this->listaEscenariosView[i] = NULL;
		}
	}
	this->canEscenariosV = 0;
	return 0;
}

// Por ahora este metodo no está en uso
void VistaJuego::reiniciar(ServidorXml * confServidorXml, int posicionInicialMapa) {
	SDL_mutexP(mut);

	resetEscenarios();
	resetAviones();
	cargarAviones(confServidorXml);
	cargarEscenarios(confServidorXml);
	cargarBala(confServidorXml);

	Graficador::getInstance()->inicializar(gRenderer, this->ventanaAncho, this->ventanaAlto);
	Graficador::getInstance()->agregarDatosAviones(this->listaAvionView, this->canAvionV);
	Graficador::getInstance()->agregarDatosBala(this->balaView);
	Graficador::getInstance()->agregarDatosMapa(this->listaEscenariosView, this->canEscenariosV, posicionInicialMapa);
	Graficador::getInstance()->reiniciarMapa();

	SDL_mutexV(mut);
}

//Como no los cargo del xml, lo cargo desde aca.
void VistaJuego::agregarDatosDeAvionesEnemigosHardcodeados(){
	char spriteStr[20] = "nave_mediana";
	char path[100] = "nave_mediana.bmp";

	int idMiddle = 101;
	SpriteXml* spriteNaveEnemigaMediana = new SpriteXml(idMiddle, spriteStr,path,1,68,120);
	AvionXml* avionXml = new AvionXml(idMiddle,5,5,idMiddle,spriteStr,5,"asd",3,"zxc");
	AvionModel* avionModel = new AvionModel(avionXml);
	AvionView** avionView = new AvionView*;
	avionView[0] = new AvionView(avionModel,spriteNaveEnemigaMediana);
	Graficador::getInstance()->agregarDatosAviones(avionView,1);

	char spriteStr2[20] = "nave_grande";
	char path2[100] = "nave_grande.bmp";
	int idBig = 100;
	SpriteXml* spriteNaveEnemigaGrande = new SpriteXml(idBig, spriteStr2,path2,1,118,200);
	AvionXml* avionXml2 = new AvionXml(idBig,5,5,idBig,spriteStr2,5,"asd",3,"zxc");
	AvionModel* avionModel2 = new AvionModel(avionXml2);
	AvionView** avionView2 = new AvionView*;
	avionView2[0] = new AvionView(avionModel2,spriteNaveEnemigaGrande);
	Graficador::getInstance()->agregarDatosAviones(avionView2,1);
	
	char spriteStr3[20] = "nave_chica";
	char path3[100] = "nave_chica.bmp";
	int numeroDeFramesDeLaNaveChica = 16;
	int idMini = 102;
	SpriteXml* spriteNaveEnemigaChica = new SpriteXml(idMini, spriteStr3,path3,
														numeroDeFramesDeLaNaveChica,19,16);
	AvionXml* avionXml3 = new AvionXml(idMini,5,5,idMini,spriteStr3,5,"asd",3,"zxc");
	AvionModel* avionModel3 = new AvionModel(avionXml3);
	AvionView** avionView3 = new AvionView*;
	avionView3[0] = new AvionView(avionModel3,spriteNaveEnemigaChica);
	Graficador::getInstance()->agregarDatosAviones(avionView3,1);
}

void VistaJuego::ejecutar(ServidorXml * confServidorXml, int posicionInicialMapa) {

	cargarAviones(confServidorXml);
	cargarEscenarios(confServidorXml);
	cargarBala(confServidorXml);

 	dibujarFondoInicio();
	inicializarMusica();

	/*Se inicializa y se cargan los datos en el Graficador*/

	Graficador::getInstance()->inicializar(gRenderer, this->ventanaAncho, this->ventanaAlto);
	Graficador::getInstance()->agregarDatosAviones(this->listaAvionView, this->canAvionV);
	Graficador::getInstance()->agregarDatosBala(this->balaView);
	Graficador::getInstance()->agregarDatosMapa(this->listaEscenariosView, this->canEscenariosV, posicionInicialMapa);

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
		
		//recibir actualizaciones
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