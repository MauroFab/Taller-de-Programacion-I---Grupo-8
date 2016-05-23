#ifndef _JUEGO_H_
#define _JUEGO_H_

#include <vector>
#include <map>
#include <SDL2/SDL.h>
#include <SDL2\SDL_image.h>

#define PATH_FONDO_INICIO "fondoInicio.bmp"

#include "Movimiento.h"
#include "Avion.h"
#include "Mapa.h"
#include "ConfiguracionJuegoXML.h"
#include "Graficador.h"
#include "FondoInicio.h"
#include "../common/observer/Observable.h"
#include "EstadoAvion.h"
#include "ICargable.h"
#include "../common/xml/ServidorXml.h"

#define MAX_ELEM_VIEW	20
#define MAX_AVION_VIEW	4
#include "../common/view/ElementoView.h"
#include "../common/model/ElementoModel.h"
#include "../common/view/AvionView.h"
#include "../common/model/AvionModel.h"

using namespace std;

class Juego : public Observable, public ICargable
{
//private:	
public:
	ElementoView * listaElemView[MAX_ELEM_VIEW];
	int canElemV;
	AvionView * listaAvionView[MAX_AVION_VIEW];
	int canAvionV;
public:

	static Juego* getInstance();
	~Juego();
	/**
	 * @param servidorXml contiene toda la configuracion tanto del servidor como del escenario
	 * este metodo carga los datos desde el servidorXml hacia el juego
	 */
	int readServidorXml(ServidorXml * servidorXml);
	//se lee el servidorXML como un objeto generico
	int readFrom(IGenericaVO * objetoXML);

	void ejecutar(ServidorXml * confServidorXml);
	void close();
	void actualizarMovimientos(EstadoAvion* estadoAvion);
	void setJugar();
	//---carga de elementos de la vista
	int cargarElementos(ServidorXml * confServidorXml);
	//---carga de aviones de la vista
	int cargarAviones(ServidorXml * confServidorXml);

	void setIdJugador(int idJugador);

private:

	static bool instanceFlag;
	static Juego* instance;
	Juego();
	int idJugador;
	int ventanaAncho;
	int ventanaAlto;
	bool jugar; // para avisar que debe de inciar el juego
	//este metodo realiza la inicializacion de la configuracion grafica de SDL
	bool initSDL();
	//este metodo dibuja un fondo incial
	//pero su tama�o esta harcodeado, deberia sacarse
	void dibujarFondoInicio();
	
	SDL_Window* gWindow;
	SDL_Renderer* gRenderer;

	SDL_mutex *mut; // mutex para proteger la lista de movimientos
	std::map<int,EstadoAvion*> movimientosDeCompetidores;

	void notificarMovimiento(EstadoAvion* estadoAvion);
};

#endif //_JUEGO_H_

