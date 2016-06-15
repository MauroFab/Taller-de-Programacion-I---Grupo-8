#ifndef _JUEGO_H_
#define _JUEGO_H_

class Juego
{
public:
	Juego();
	virtual ~Juego();
	void run();
	void inicializar();
	void clean();
	void handleEvents();
	void update();
	void render();
	
};

#endif //_JUEGO_H_
