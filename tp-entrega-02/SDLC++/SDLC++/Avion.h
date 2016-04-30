#ifndef AVION_H_
#define AVION_H_

#include "Constantes.h"
#include "Textura.h"

class Avion
{
    public:
		//The dimensions of the dot
		static const int DOT_WIDTH = 64;
		static const int DOT_HEIGHT = 205;

		//Maximum axis velocity of the dot
		static const int DOT_VEL = 10;

		//Initializes the variables
		Avion();

		//Takes key presses and adjusts the dot's velocity
		void handleEvent( SDL_Event& e );

		//Moves the dot
		void move();

		//Shows the dot on the screen
		void render(Textura& gAvionTextura,SDL_Rect* currentClip,SDL_Renderer* gRenderer);

    private:
		//The X and Y offsets of the dot
		int mPosX, mPosY;

		//The velocity of the dot
		int mVelX, mVelY;
};

#endif