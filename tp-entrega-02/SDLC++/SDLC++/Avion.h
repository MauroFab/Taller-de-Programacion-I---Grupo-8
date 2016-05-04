#pragma once

#include "Constantes.h"
#include "Textura.h"
#include "Mapa.h"
#include "Proyectil.h"

class Avion
{
    public:
		//The dimensions of the dot
		static const int DOT_WIDTH = 64;
		static const int DOT_HEIGHT = 206;

		//Maximum axis velocity of the dot
		static const int DOT_VEL = 10;

		//Initializes the variables
		Avion(SDL_Renderer* renderer, std::string dirImagenAvion, int cantidadDeFrames, int anchoFotograma, int altoFotograma);

		~Avion();

		//Takes key presses and adjusts the dot's velocity
		void handleEvent( SDL_Event& e );

		//Moves the dot
		void move();

		//Shows the dot on the screen
		void render();

    private:

		SDL_Rect *fotogramas;
		Textura* texturaAvion;
		SDL_Renderer* renderer;
		int frame;
		int cantDeFotogramas;

		//The X and Y offsets of the dot
		int mPosX, mPosY;

		//The velocity of the dot
		int mVelX, mVelY;
};