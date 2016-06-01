#ifndef TEXTURA_H_
#define TEXTURA_H_
#include <string>
#include <SDL2\SDL.h>
#include <SDL2\SDL_image.h>
using namespace std;

class Textura
{
	public:
		Textura();
		~Textura();
		// cargo la textura desde archivo
		bool cargarDeArchivo( std::string path,SDL_Renderer* gRenderer );
		
		//liberar textura
		void liberar();
		
		void render( int x, int y,SDL_Renderer* gRenderer , SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);

		//Getter's dimenciones de la imagen
		int getWidth();
		int getHeight();

	private:
		SDL_Texture* mTextura;
		int mWidth;
		int mHeight;
};

#endif