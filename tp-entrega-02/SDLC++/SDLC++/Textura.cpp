#include "Textura.h"

Textura::Textura()
{
	//Initialize
	mTextura = NULL;
	mWidth = 0;
	mHeight = 0;
}

Textura::~Textura()
{
	//Deallocate
	liberar();
}

bool Textura::cargarDeArchivo( std::string path, SDL_Renderer* gRenderer)
{
	//Get rid of preexisting texture
	liberar();

	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
	if( loadedSurface == NULL )
	{
		printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
	}
	else
	{
		//Color key image
		SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0, 0xFF, 0xFF ) );

		//Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
		if( newTexture == NULL )
		{
			printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
		}
		else
		{
			//Get image dimensions
			mWidth = loadedSurface->w;
			mHeight = loadedSurface->h;
		}

		//Get rid of old loaded surface
		SDL_FreeSurface( loadedSurface );
	}

	//Return success
	mTextura = newTexture;
	return mTextura != NULL;
}

void Textura::liberar()
{
	//Free texture if it exists
	if( mTextura != NULL )
	{
		SDL_DestroyTexture( mTextura );
		mTextura = NULL;
		mWidth = 0;
		mHeight = 0;
	}
}

void Textura::setColor( Uint8 red, Uint8 green, Uint8 blue )
{
	//Modulate texture rgb
	SDL_SetTextureColorMod( mTextura, red, green, blue );
}

void Textura::setBlendMode( SDL_BlendMode blending )
{
	//Set blending function
	SDL_SetTextureBlendMode( mTextura, blending );
}
		
void Textura::setAlpha( Uint8 alpha )
{
	//Modulate texture alpha
	SDL_SetTextureAlphaMod( mTextura, alpha );
}

void Textura::render( int x, int y,SDL_Renderer* gRenderer, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip)
{
	//Set rendering space and render to screen
	SDL_Rect renderQuad = { x, y, mWidth, mHeight };

	//Set clip rendering dimensions
	if( clip != NULL )
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	//Render to screen
	SDL_RenderCopyEx( gRenderer, mTextura, clip, &renderQuad, angle, center, flip );
}

int Textura::getWidth()
{
	return mWidth;
}

int Textura::getHeight()
{
	return mHeight;
}
