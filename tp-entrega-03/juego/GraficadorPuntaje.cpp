#include "GraficadorPuntaje.h"


GraficadorPuntaje::GraficadorPuntaje(){
}
void GraficadorPuntaje::renderizarPuntaje(SDL_Renderer* renderer, int puntaje){
	TTF_Font* Sans = TTF_OpenFont("sfd/FreeSans.ttf", 24); 
	
	SDL_Color White = {255, 255, 255}; 

	char puntajeEnString[32];
	char texto[50] = "Puntaje: ";
	
	sprintf(puntajeEnString, "%d", puntaje);
	strcat(texto, puntajeEnString);

	SDL_Surface* surfaceMessage = TTF_RenderText_Solid(Sans, texto, White); 

	SDL_Texture* Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);

	SDL_Rect Message_rect; 
	Message_rect.x = 0;  
	Message_rect.y = 0;
	Message_rect.w = 100; 
	Message_rect.h = 50; 

	SDL_RenderCopy(renderer, Message, NULL, &Message_rect); 
}

GraficadorPuntaje::~GraficadorPuntaje(void)
{
}
