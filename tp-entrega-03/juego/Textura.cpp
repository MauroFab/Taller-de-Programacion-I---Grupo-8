#include "Textura.h"

Textura::Textura()
{
	mTextura = NULL;
	mWidth = 0;
	mHeight = 0;
}

Textura::~Textura()
{
	liberar();
}

bool Textura::cargarDeArchivo( std::string path, SDL_Renderer* gRenderer){
	liberar();
	SDL_Texture* newTexture = NULL;

	SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
	if( loadedSurface == NULL )
	{
		printf( "no se puede cargar la imagen %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
	}
	else
	{
		SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0, 0xFF, 0xFF ) );
        newTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
		if( newTexture == NULL )
		{
			printf( "No se puede creaar la textura %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
		}
		else
		{
			// cargar las dimensiones
			mWidth = loadedSurface->w;
			mHeight = loadedSurface->h;
		}
		SDL_FreeSurface( loadedSurface );
	}
	mTextura = newTexture;
	return mTextura != NULL;
}

void Textura::liberar()
{
	if( mTextura != NULL )
	{
		SDL_DestroyTexture( mTextura );
		mTextura = NULL;
		mWidth = 0;
		mHeight = 0;
	}
}

int Textura::getWidth()
{
	return mWidth;
}

int Textura::getHeight()
{
	return mHeight;
}

void Textura::render( int x, int y,SDL_Renderer* gRenderer, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip)
{
	SDL_Rect renderQuad = { x, y, mWidth, mHeight };

	if( clip != NULL ){
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}
	SDL_RenderCopyEx( gRenderer, mTextura, clip, &renderQuad, angle, center, flip );
}
