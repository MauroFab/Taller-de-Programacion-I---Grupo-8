#ifndef _VISTAJUEGO_H_
#define _VISTAJUEGO_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>

#include <vector>
#include <map>
#include "Mapa.h"
#include "Graficador.h"
#include "FondoInicio.h"
#include "EstadoJuego.h"
#include "CacheSonido.h"
#include "ControladorTeclado.h"
#include "../common/xml/ServidorXml.h"
#include "../common/view/ElementoView.h"
#include "../common/model/ElementoModel.h"
#include "../common/view/AvionView.h"
#include "../common/model/AvionModel.h"
#include "../common/view/FondoView.h"
#include "../common/model/FondoModel.h"
#include "../common/view/BalaView.h"
#include "../common/view/EscenarioView.h"
#include "../common/view/AvionEnemigoView.h"
#include "../common/Jugador.h"
#include "../estructura/Juego.h"
#include "../estructura/MenuEscenario.h"
#include "../estructura/NivelHandle.h"

#define PATH_FONDO_INICIO "fondoInicio.bmp"
#define MAX_AVION_VIEW	4
#define MAX_ESCENARIO_VIEW 10

using namespace std;

class VistaJuego {

public:
	AvionView * listaAvionView[MAX_AVION_VIEW];
	int canAvionV;
	EscenarioView * listaEscenariosView[MAX_ESCENARIO_VIEW];
	int canEscenariosV;
	//por ahora solo 1(UNA) bala, pero deberian ser N balas, 1 por avion
	BalaView * balaView;
	Juego * juego;
private:
	ControladorTeclado* controlador;
	static VistaJuego* instance;
	Jugador * jugador;//este objeto contiene los datos del jugador, por ahora solo el id_cliente
	int ventanaAncho;
	int ventanaAlto;
	bool jugar; // para avisar que debe de inciar el juego

	//Como no los cargo del xml, los carga a mano con este metodo.
	void agregarDatosDeAvionesEnemigosHardcodeados();

	SDL_Window* gWindow;
	SDL_Renderer* gRenderer;

	SDL_mutex *mut; // mutex para proteger la lista de movimientos
	EstadoJuego* estadoJuego;

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
	 */
	bool inicializar();
	void reiniciar(ServidorXml * confServidorXml, int posicionInicialMapa);
	void ejecutar(ServidorXml * confServidorXml, int posicionInicialMapa);
	void close();
	void actualizarEstadoJuego(EstadoJuego* estadoJuego);
	void setJugar();
	//---carga de aviones de la vista
	int cargarAviones(ServidorXml * confServidorXml);
	//---carga de elementos de la vista
	int cargarElementos(ServidorXml * confServidorXml, EscenarioView* escenarioV, int idEscenario);
	//---carga de los enemigos
	int cargarEnemigos(ServidorXml * confServidorXml, EscenarioView* escenarioV, int idEscenario);
	//---carga de los power-ups
	int cargarPowerUps(ServidorXml * confServidorXml, EscenarioView* escenarioV, int idEscenario);
	//realiza la carga de los escenarios
	int cargarEscenarios(ServidorXml * servidorXml);
	//realiza la carga de una bala tipo, con la velocidad del 1er avion
	int cargarBala(ServidorXml * confServidorXml);
	Jugador * getJugador();
	//operaciones de reset
	//se encarga del reset de los aviones liberando la memoria usada por los objetos
	//tanto de la view como de los que estos contienen
	int resetAviones();
	int resetEscenarios();
	void agregarObservador(Observador* observador);

private:
	VistaJuego();
	void dibujarFondoInicio();
	// Inicializa la musica de fondo, disparos y explosiones
	void inicializarMusica();
};

#endif //_VISTAJUEGO_H_