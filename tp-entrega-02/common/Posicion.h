#ifndef _POSICION_H_
#define _POSICION_H_

class Posicion {

private:

    int x;
    int y;

	int sizeBytes;

public:

	Posicion();

    Posicion(int x, int y);

    virtual ~Posicion();

    int getPosX();

    int getPosY();

	void setPosX(int x);

	void setPosY(int y);

	int getSizeBytes();

	void calculateSizeBytes();
};

#endif //_POSICION_H_

