#ifndef _JUEGO_H_
#define _JUEGO_H_

#include <vector>
#include <map>
#include <SDL2/SDL.h>
#include <SDL2\SDL_image.h>

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
using namespace std;

class Juego : public Observable, public ICargable
{

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

	void ejecutar();
	void close();
	void actualizarMovimientos(EstadoAvion* estadoAvion);

private:

	static bool instanceFlag;
	static Juego* instance;
	Juego();
	int ventanaAncho;
	int ventanaAlto;
	//este metodo realiza la inicializacion de la configuracion grafica de SDL
	bool init();
	void configuracionInicial();
	
	SDL_Window* gWindow;
	SDL_Renderer* gRenderer;

	SDL_mutex *mut; // mutex para proteger la lista de movimientos
	std::map<int,EstadoAvion*> movimientosDeCompetidores;

	void notificarMovimiento(EstadoAvion* estadoAvion);
};

#endif //_JUEGO_H_

