#include "VistaJuego.h"

bool VistaJuego::instanceFlag = false;
VistaJuego* VistaJuego::instance = NULL;

VistaJuego* VistaJuego::getInstance() {
	if(!instanceFlag){
        instance = new VistaJuego();
        instanceFlag = true;
    }
    return instance;
}

VistaJuego::VistaJuego(){
	this->cantidadDeVecesQueSeReinicio = 0;
	this->seReinicio = false;
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
	this->balaView = NULL;
	this->controlador = new Controlador();
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

// Inicializacion
bool VistaJuego::initSDL(char * nomClien) {
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
		string titulo;
		titulo.append("1942-[");
		titulo.append(nomClien);
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

void VistaJuego::close() {
	SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	gRenderer = NULL;

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

void VistaJuego::setJugar(){
	jugar = true;
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

BalaView*  VistaJuego::cargarBala(ServidorXml * confServidorXml){
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
	return new BalaView(balaModel,spriteX);
}

Jugador * VistaJuego::getJugador(){
	return this->jugador;
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
	seReinicio = true;
	resetElementos();
	resetAviones();
	static int tamanioMaximoMapa = 2000;
	cargarElementos(confServidorXml);
	cargarAviones(confServidorXml);
	cargarFondo(confServidorXml,tamanioMaximoMapa);
	BalaView * balaView = cargarBala(confServidorXml);

	Graficador::getInstance()->inicializar(gRenderer, this->ventanaAncho, this->ventanaAlto);

	//se cargan los aviones de la vista a la clase que luego los grafica
	for(int v = 0; v < this->canAvionV; v++){
		AvionView * avionV = this->listaAvionView[v];
		Graficador::getInstance()->agregarDatosAvion(avionV);
	}
	this->balaView = balaView;
	Graficador::getInstance()->agregarDatosBala(balaView);

	Mapa::getInstace()->inicializar(gRenderer,this->fondoView, posicionInicialMapa);

	for(int e = 0; e < this->canElemV; e++){
		ElementoView * elemV = this->listaElemView[e];
		Mapa::getInstace()->crearElemento(elemV);
	}

	int id_cliente = this->jugador->getIdCliente();

	Mapa::getInstace()->reiniciar();
	SDL_mutexV(mut);
}

void VistaJuego::ejecutar(ServidorXml * confServidorXml, int posicionInicialMapa) {

	static int tamanioMaximoMapa = 2000;
	cargarElementos(confServidorXml);
	cargarAviones(confServidorXml);
	cargarFondo(confServidorXml,tamanioMaximoMapa);
	BalaView * balaView = cargarBala(confServidorXml);

 	dibujarFondoInicio();

	bool quit = false;

	Graficador::getInstance()->inicializar(gRenderer, this->ventanaAncho, this->ventanaAlto);

	//se cargan los aviones de la vista a la clase que luego los grafica
	for(int v = 0; v < this->canAvionV; v++){
		AvionView * avionV = this->listaAvionView[v];
		Graficador::getInstance()->agregarDatosAvion(avionV);
	}

	this->balaView = balaView;
	Graficador::getInstance()->agregarDatosBala(balaView);

	Mapa::getInstace()->inicializar(gRenderer,this->fondoView, posicionInicialMapa);

	for(int e = 0; e < this->canElemV; e++){
		ElementoView * elemV = this->listaElemView[e];
		Mapa::getInstace()->crearElemento(elemV);
	}

	int id_cliente = this->jugador->getIdCliente();

	/*------------------------------------------------------------------*/

	SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
	//Clear screen
	SDL_RenderClear( gRenderer );

	//Render background
	Mapa::getInstace()->dibujarFondoYElementos();

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
			//Notifica al servidor de lo presionado
			controlador->procesarTeclasPresionadas( e );
		}

		//Clear screen
		SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
		SDL_RenderClear( gRenderer );

		SDL_mutexP(mut);
		//Render background
		Mapa::getInstace()->dibujarFondoYElementos();

		Graficador::getInstance()->graficarAviones(estadoAviones);
		SDL_mutexV(mut);

		//Update screen
		SDL_RenderPresent( gRenderer );
	}

	close();
}

void VistaJuego::actualizarMovimientos(EstadoAvion* estadoAvion){
	SDL_mutexP(mut);
	int idAvion = estadoAvion->getId();
	EstadoAvion* estadoAnterior = VistaJuego::getInstance()->estadoAviones[idAvion];
	delete estadoAnterior;
	VistaJuego::getInstance()->estadoAviones[idAvion] = estadoAvion;
	SDL_mutexV(mut);
}

void VistaJuego::agregarObservadorAlControlador(Observador* observador){
	this->controlador->agregarObservador(observador);
}