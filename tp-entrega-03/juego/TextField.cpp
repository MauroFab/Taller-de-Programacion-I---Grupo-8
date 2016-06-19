#include "TextField.h"

TextField::TextField(SDL_Renderer* renderer, TTF_Font* font) {

	this->renderer = renderer;
	this->font = font;
	SDL_Color textColor = { 0, 0, 0, 0xFF };
	this->color = textColor;
	this->texto.assign("");
	this->textura = new TexturaFuente();
	this->textura->loadFromRenderedText(this->font, this->renderer, this->texto, this->color);
}

TextField::~TextField(void) {
	this->textura->free();
}

void TextField::setPosicion(int x, int y) {
	this->posX = x;
	this->posY = y;
}

std::string TextField::getTexto() {
	return this->texto;
}

void TextField::render() {

	if( this->renderTextFlag ) {

		if ( this->texto.compare( "" ) != 0) {
			this->textura->loadFromRenderedText(this->font, this->renderer, this->texto, this->color);
		}
		else {
			this->textura->loadFromRenderedText(this->font, this->renderer, "", this->color);
		}
	}
	this->textura->render(this->renderer, this->posX, this->posY);
}

void TextField::manejarEvento(SDL_Event e) {

	if( e.type == SDL_KEYDOWN ) {
		//Tecla Backspace
		if( e.key.keysym.sym == SDLK_BACKSPACE && this->texto.length() > 0 ) {
			this->texto.pop_back();
			this->renderTextFlag = true;
		}
		//Copiar
		else if( e.key.keysym.sym == SDLK_c && SDL_GetModState() & KMOD_CTRL ) {
			SDL_SetClipboardText( this->texto.c_str() );
		}
		//Pegar
		else if( e.key.keysym.sym == SDLK_v && SDL_GetModState() & KMOD_CTRL ) {
			this->texto = SDL_GetClipboardText();
			this->renderTextFlag = true;
		}
	}
	//Evento de input de texto
	else if( e.type == SDL_TEXTINPUT ) {
		//se desahibilita copy or pasting
		if( !( ( e.text.text[ 0 ] == 'c' || e.text.text[ 0 ] == 'C' ) && ( e.text.text[ 0 ] == 'v' || e.text.text[ 0 ] == 'V' ) && SDL_GetModState() & KMOD_CTRL ) ) {
			this->texto += e.text.text;
			this->renderTextFlag = true;
		}
	}
}

void TextField::limpiar() {
	this->texto.assign("");
}