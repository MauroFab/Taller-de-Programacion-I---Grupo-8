/*
 * esta clase se encarga de realizar un cache sobre los objetos
 * de reproduccion del sonido
 * la idea es que distintas instancias comparten los mismos sonidos
 * cbenez
 * */
#ifndef CACHESONIDO_H_
#define CACHESONIDO_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

//se define la cantiada maxima de temas, 1 tema por cada nivel
#define MAX_ID_CACHE_MUSIC	1
//se define la cantidad maxima de efectos de sonidos distintos
#define MAX_ID_CACHE_CHUNK	3

/// sonidos o musica generales de un Entidad
enum sonidos
{
	DISPARO,
	EXPLOSION
};
/// sonidos o musica generales de un Entidad
enum niveles
{
	NIVEL_1,
	NIVEL_2
};

class CacheSonido {

public:
	static CacheSonido* getInstance();

	virtual ~CacheSonido();
	/**
	 * @param pMusic, puntero al Music a guardar
	 * @param idxSon indicador del sonido a buscar, usado como posicion
	 * @return retorna el idx en donde se guardo el ptr a Music
	 */	
	int addMusic(Mix_Music * pMusic,enum niveles idxSon);
	/**
	 * @param pChunk, puntero al pChunk a guardar
	 * @param idxSon indicador del sonido a buscar, usado como posicion
	 * @return retorna el idx en donde se guardo el ptr a pChunk
	 */		
	int addChunk(Mix_Chunk * pChunk,enum sonidos idxSon);	
	/**
	 * @param idxSon indicador del sonido a buscar, usado como posicion
	 * @return retorna el ptr guardado en la posicion de idxSon 
	 */	
	Mix_Music * getMusic(enum niveles idxSon);
	/**
	 * @param idxSon indicador del sonido a buscar, usado como posicion
	 * @return retorna el ptr guardado en la posicion de idxSon 
	 */	
	Mix_Chunk * getChunk(enum sonidos idxSon);	
	/**
	 * libera todos los ptr guardados de music
	 */	
	void releaseMusic();
	/**
	 * libera todos los ptr guardados de chunk
	 */	
	void releaseChunk();
	/**
	 * libera todos los vectores que tenga
	 */	
	void release();

private:
	CacheSonido();
	//la musica de fondo del juego para cada nivel
	Mix_Music *vecMusic[MAX_ID_CACHE_MUSIC];
	//los sonidos de efectos usados
	Mix_Chunk *vecChunk[MAX_ID_CACHE_CHUNK];
	static CacheSonido* instance;
	static bool instanceFlag;
};

#endif /*CACHESONIDO_H_*/
