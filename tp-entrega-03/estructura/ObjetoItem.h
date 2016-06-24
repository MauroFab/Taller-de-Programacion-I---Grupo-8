#ifndef _OBJETOITEM_H_
#define _OBJETOITEM_H_

#include <iostream>
#include "UtilJuego.h"
using namespace std;

typedef struct posFPoint{
                int x;
                int y;
               }FPoint;
               
typedef struct posFlxRect{
                int x;
                int y;
                int width;
                int height;
               }FRect;

class ObjetoItem
{
public:
    int x;
    int y;
public:
    bool existe;
    bool activo;
    bool visible;
	bool  _solid;
	bool  moves;
	bool  _group;
	bool  bMuerto;
	FRect colHullX;
	FRect colHullY;
	FPoint colVector;
	FPoint velocity;
	FPoint _pZero;
	FPoint _point;
	FRect this_rect;
	
public:
	ObjetoItem();
	virtual ~ObjetoItem();
	void destroy();
	bool get_solid();
	void refreshHulls();
	void updateMotion();
	virtual void update();
	virtual void render();
	bool overlaps(ObjetoItem arg1);
	virtual void kill();
	void getScreenXY(FPoint * arg1);
	bool onScreen();
	virtual void reset(int arg1,int arg2);
};

#endif //_OBJETOITEM_H_
