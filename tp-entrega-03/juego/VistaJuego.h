#ifndef _VISTAJUEGO_H_
#define _VISTAJUEGO_H_

#include <vector>
#include <map>
#include <SDL2/SDL.h>
#include <SDL2\SDL_image.h>
#include "Controlador\Controlador.h"

#define PATH_FONDO_INICIO "fondoInicio.bmp"

#include "Mapa.h"
#include "Graficador.h"
#include "FondoInicio.h"
#include "../common/observer/Observable.h"
#include "EstadoJuego.h"
#include "ICargable.h"
#include "../common/xml/ServidorXml.h"

#define MAX_ELEM_VIEW	20
#define MAX_AVION_VIEW	4
#include "../common/view/ElementoView.h"
#include "../common/model/ElementoModel.h"
#include "../common/view/AvionView.h"
#include "../common/model/AvionModel.h"
#include "../common/view/FondoView.h"
#include "../common/model/FondoModel.h"
#include "../common/view/BalaView.h"
#include "../common/Jugador.h"

using namespace std;

class VistaJuego : public ICargable
{
public:
	ElementoView * listaElemView[MAX_ELEM_VIEW];
	int canElemV;
	AvionView * listaAvionView[MAX_AVION_VIEW];
	int canAvionV;
	FondoView * fondoView;
	//por ahora solo 1(UNA) bala, pero deberian ser N balas, 1 por avion
	BalaView * balaView;
public:

	static VistaJuego* getInstance();
	~VistaJuego();
	/**
	 * @param servidorXml contiene toda la configuracion tanto del servidor como del escenario
	 * este metodo carga los datos desde el servidorXml hacia el juego
	 */
	int readServidorXml(ServidorXml * servidorXml);
	//se lee el servidorXML como un objeto generico
	int readFrom(IGenericaVO * objetoXML);
	/**
	 * este metodo realiza la inicializacion de la configuracion grafica de SDL
	 * @param nomClien  nombre del cliente usado en el titulo de la ventana
	 */
	bool initSDL(char * nomClien);
	void reiniciar(ServidorXml * confServidorXml, int posicionInicialMapa);
	void ejecutar(ServidorXml * confServidorXml, int posicionInicialMapa);
	void close();
	void actualizarEstadoJuego(EstadoJuego* estadoJuego);
	void setJugar();
	//---carga de elementos de la vista
	int cargarElementos(ServidorXml * confServidorXml);
	//---carga de aviones de la vista
	int cargarAviones(ServidorXml * confServidorXml);
	//realiza la carga del fondo la 1era vez
	int cargarFondo(ServidorXml * confServidorXml,int altoFondo);
	//realiza la carga de una bala tipo, con la velocidad del 1er avion
	int cargarBala(ServidorXml * confServidorXml);
	Jugador * getJugador();
	//operaciones de reset
	//se encarga del reset de los elementos liberando la memoria usada por los objetos
	//tanto de la view como de los que estos contienen
	int resetElementos();
	//se encarga del reset de los aviones liberando la memoria usada por los objetos
	//tanto de la view como de los que estos contienen
	int resetAviones();
	void agregarObservadorAlControlador(Observador* observador);

private:
	Controlador* controlador;
	static bool instanceFlag;
	static VistaJuego* instance;
	VistaJuego();
	Jugador * jugador;//este objeto contiene los datos del jugador, por ahora solo el id_cliente
	int ventanaAncho;
	int ventanaAlto;
	bool jugar; // para avisar que debe de inciar el juego
	bool seReinicio;
	int cantidadDeVecesQueSeReinicio;

	//este metodo dibuja un fondo incial
	//pero su tamaño esta harcodeado, deberia sacarse
	void dibujarFondoInicio();

	SDL_Window* gWindow;
	SDL_Renderer* gRenderer;

	SDL_mutex *mut; // mutex para proteger la lista de movimientos
	std::map<int,EstadoAvion*> estadoAviones;
	EstadoMapa* estadoMapa;
};

#endif //_VISTAJUEGO_H_