#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <string>

#define FUENTE_PATH "./sfd/DejaVuSans.ttf"
#define PATH_FONDO_IP "fondoMenuIP.bmp"
#define PATH_FONDO_PUERTO "fondoMenuPuerto.bmp"
#define PATH_FONDO_USUARIO "fondoMenuUsuario.bmp"

#define WIDTH 480;
#define HEIGHT 640;

using namespace std;

class VistaInicio {

public:
	static VistaInicio* getInstance();
	virtual ~VistaInicio(void);

	bool inicializar();
	void close();
	void mostrar();
	string getPuerto();
	string getIP();
	string getUsuario();

private:
	VistaInicio();
	static bool instanceFlag;
	static VistaInicio* instance;

	int ventanaAncho;
	int ventanaAlto;
	SDL_Window* gWindow;
	SDL_Renderer* gRenderer;
	TTF_Font* gFont;
};

