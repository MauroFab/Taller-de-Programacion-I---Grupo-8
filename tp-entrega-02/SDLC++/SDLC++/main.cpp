
#include "Avion.h"
#include "Textura.h"
#include "ElementoDelMapa.h"
#include "Mapa.h"

//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The window renderer
SDL_Renderer* gRenderer = NULL;

//Scene textures
Textura gIslaTextura;
Textura gBGTexture;

// Textura avion
const int WALKING_ANIMATION_FRAMES = 7;
SDL_Rect gSpriteClips[ WALKING_ANIMATION_FRAMES ];
Textura gSpriteSheetTexture;


//Walking animation
//const int WALKING_ANIMATION_FRAMES = 4;
//SDL_Rect gSpriteClips[ WALKING_ANIMATION_FRAMES ];
//Textura gSpriteSheetTexture;

// Inicio No tocar
bool init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			printf( "Warning: Linear texture filtering not enabled!" );
		}

		//Create window
		gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( gWindow == NULL )
		{
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
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

bool loadMedia()
{
	//Loading success flag
	bool success = true;

	//Load dot texture (ya no es necesaria quitar)
	if( !gIslaTextura.cargarDeArchivo( "isla.bmp",gRenderer) )
	{
		printf( "Failed to load dot texture!\n" );
		success = false;
	}

	//Load background texture
	if( !gBGTexture.cargarDeArchivo( "bg.bmp",gRenderer ) )
	{
		printf( "Failed to load background texture!\n" );
		success = false;
	}

	//SPRITES

	//Load sprite sheet texture
	if( !gSpriteSheetTexture.cargarDeArchivo( "rollTest.bmp",gRenderer ) )
	{
		printf( "Failed to load walking animation texture!\n" );
		success = false;
	}
	else
	{
		//Configurable desde xml
		//id
		//path a la imagen
		//cantidad de fotogramas
		//ancho (en unidades lógicas)
		//alto	(en	unidades	lógicas)
		int cantidadDeFotogramas = 7;
		int altoFotograma = 195;
		int anchoFotograma = 112;

		for(int i=0; i < cantidadDeFotogramas; i++){

			gSpriteClips[ i ].x = anchoFotograma * i;
			gSpriteClips[ i ].y = 0;
			gSpriteClips[ i ].w = anchoFotograma;
			gSpriteClips[ i ].h = altoFotograma;
		}
	}
	return success;
}

void close()
{
	//Free loaded images
	gIslaTextura.liberar();
	gBGTexture.liberar();
	gSpriteSheetTexture.liberar();
	//Destroy window	
	SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}

int main( int argc, char* args[] )
{
	//Start up SDL and create window
	if( !init() )
	{
		printf( "Failed to initialize!\n" );
	}
	else
	{
		//Load media
		if( !loadMedia() )
		{
			printf( "Failed to load media!\n" );
		}
		else
		{	
			//Main loop flag
			bool quit = false;

			//Event handler
			SDL_Event e;

			//The dot that will be moving around on the screen
			Avion avion;

			//The background scrolling offset
			int scrollingOffset = 0;
			int globalOffset = 0;
			int frame=0;

			Mapa mapa(gRenderer, &gBGTexture, &gIslaTextura);
			mapa.crearIslaEn(100, 700);
			mapa.crearIslaEn(300, 900);
			//While application is running
			while( !quit )
			{
				//Handle events on queue
				while( SDL_PollEvent( &e ) != 0 )
				{
					//User requests quit
					if( e.type == SDL_QUIT )
					{
						quit = true;
					}

					//Handle input for the dot
					// registrar mov del teclado
					avion.handleEvent( e );
				}

				//Clear screen
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
				SDL_RenderClear( gRenderer );

				//Render background
				mapa.graficar();
				//isla
				SDL_Rect* currentClip = &gSpriteClips[ frame / 7 ];
				//otro frame
				++frame;

				//para poder ciclar
				if( frame / 7 >= WALKING_ANIMATION_FRAMES )
				{
					frame = 0;
				}

				// mover el muñequito
				avion.move();
				//Render sprite
				avion.render(gSpriteSheetTexture,currentClip,gRenderer);

				//Update screen
				SDL_RenderPresent( gRenderer );
			}
		}
	}

	//Free resources and close SDL
	close();

	return 0;
}
