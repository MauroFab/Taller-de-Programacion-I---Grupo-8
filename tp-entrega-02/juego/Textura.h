#ifndef TEXTURA_H_
#define TEXTURA_H_
#include <string>
#include <SDL2\SDL.h>
#include <SDL2\SDL_image.h>
using namespace std;

class Textura
{
	public:
		//Initializes variables
		Textura();

		//Deallocates memory
		~Textura();

		//Loads image at specified path
		bool cargarDeArchivo( std::string path,SDL_Renderer* gRenderer );
		
		//Deallocates texture
		void liberar();

		//Set color modulation
		void setColor( Uint8 red, Uint8 green, Uint8 blue );

		//Set blending
		void setBlendMode( SDL_BlendMode blending );

		//Set alpha modulation
		void setAlpha( Uint8 alpha );
		
		//Renders texture at given point
		void render( int x, int y,SDL_Renderer* gRenderer , SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);

		//Gets image dimensions
		int getWidth();
		int getHeight();

	private:
		//The actual hardware texture
		SDL_Texture* mTextura;

		//Image dimensions
		int mWidth;
		int mHeight;
};

#endif