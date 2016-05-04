#include "Avion.h"

Avion::Avion(SDL_Renderer* rendererRecibido, std::string dirImagenAvion, int cantidadDeFotogramas, int anchoFotograma, int altoFotograma)
{
    //Initialize the offsets
    mPosX = 200;
    mPosY = 400;

    //Initialize the velocity
    mVelX = 0;
    mVelY = 0;

	frame = 0;
	rollFlag = false;

	cantDeFotogramas = cantidadDeFotogramas;
	renderer = rendererRecibido;
	texturaAvion = new Textura();
	fotogramas = new SDL_Rect[cantDeFotogramas];

	if( !texturaAvion->cargarDeArchivo( dirImagenAvion, renderer ) )
	{
		printf( "Failed to load plane animation texture!\n" );
	}
	else
	{
		for(int i=0; i < cantDeFotogramas; i++){

			SDL_Rect fotograma;

			fotograma.x = anchoFotograma * i;
			fotograma.y = 0;
			fotograma.w = anchoFotograma;
			fotograma.h = altoFotograma;

			fotogramas[ i ] = fotograma;
		}
	}
}

Avion::~Avion() {

	delete [] fotogramas;
	texturaAvion->liberar();
}

void Avion::handleEvent( SDL_Event& e )
{
    //If a key was pressed
	if( e.type == SDL_KEYDOWN && e.key.repeat == 0 )
    {
        switch( e.key.keysym.sym )
        {
			//Adjust the velocity
            case SDLK_UP: mVelY -= DOT_VEL; break;
            case SDLK_DOWN: mVelY += DOT_VEL; break;
            case SDLK_LEFT: mVelX -= DOT_VEL; break;
            case SDLK_RIGHT: mVelX += DOT_VEL; break;
			
			// Realiza el roll
			case SDLK_RETURN: rollFlag = true; break;
        }
    }
    //If a key was released
    else if( e.type == SDL_KEYUP && e.key.repeat == 0 )
    {
        switch( e.key.keysym.sym )
        {
			//Adjust the velocity
            case SDLK_UP: mVelY += DOT_VEL; break;
            case SDLK_DOWN: mVelY -= DOT_VEL; break;
            case SDLK_LEFT: mVelX += DOT_VEL; break;
            case SDLK_RIGHT: mVelX -= DOT_VEL; break;

			// Realiza un disparo
			case SDLK_SPACE: {

				Proyectil proyectil(renderer, "proyectilAvion.bmp", 1, 50, 50);
				proyectil.setCoordenasDeComienzo(mPosX, mPosY);
				proyectil.move();
							 } break;
        }
    }
}

void Avion::move()
{
    //Move the dot left or right
    mPosX += mVelX;

    //If the dot went too far to the left or right
	// aca cambiar para no salir de la pantalla X
    if( ( mPosX < 0 ) || ( mPosX + DOT_WIDTH > SCREEN_WIDTH ) )
    {
        //Move back
        mPosX -= mVelX;
    }

    //Move the dot up or down
    mPosY += mVelY;

    //If the dot went too far up or down
	// aca cambiar para no salir de la pantalla Y
    if( ( mPosY < 0 ) || ( mPosY + DOT_HEIGHT > SCREEN_HEIGHT ) )
    {
        //Move back
        mPosY -= mVelY;
    }
}

void Avion::render()
{
	if (rollFlag) ++frame;

	SDL_Rect* currentClip = &fotogramas[ frame / cantDeFotogramas ];

	if ((frame / cantDeFotogramas) >= cantDeFotogramas){
		frame = 0;
		rollFlag = false;
	}

    //Show the dot
	texturaAvion->render( mPosX, mPosY, renderer, currentClip );
}
