#include "CacheSonido.h"

bool CacheSonido::instanceFlag = false;
CacheSonido* CacheSonido::instance = NULL;

CacheSonido* CacheSonido::getInstance() {
	if(!instanceFlag){
        instance = new CacheSonido();
        instanceFlag = true;
    }
    return instance;
}

CacheSonido::CacheSonido() {
	for (int i = 0;i<MAX_ID_CACHE_MUSIC; i++){
		this->vecMusic[i] = NULL;
	}
	for (int i = 0;i<MAX_ID_CACHE_CHUNK; i++){
		this->vecMusic[i] = NULL;
	}	
}

CacheSonido::~CacheSonido() {
}

int CacheSonido::addMusic(Mix_Music * pMusic,enum niveles idxSon){
	int idx = (int)idxSon;
	this->vecMusic[idx] = pMusic;
	return idx;
}

int CacheSonido::addChunk(Mix_Chunk * pChunk,enum sonidos idxSon){
	int idx = (int)idxSon;
	this->vecChunk[idx] = pChunk;
	return idx;
}

Mix_Music * CacheSonido::getMusic(enum niveles idxSon){
	int idx = (int)idxSon;
	return this->vecMusic[idx];
}
Mix_Chunk * CacheSonido::getChunk(enum sonidos idxSon){
	int idx = (int)idxSon;
	return this->vecChunk[idx];
}	

void CacheSonido::releaseMusic(){
	for (int i = 0;i<MAX_ID_CACHE_MUSIC; i++){
		if (this->vecMusic[i] != NULL){
			Mix_FreeMusic( this->vecMusic[i]);
		}
	}
}
void CacheSonido::releaseChunk(){
	for (int i = 0;i<MAX_ID_CACHE_CHUNK; i++){
		if (this->vecChunk[i] != NULL){
			Mix_FreeChunk(this->vecChunk[i]);
		}
	}
}
void CacheSonido::release(){
	this->releaseMusic();
	this->releaseChunk();
}