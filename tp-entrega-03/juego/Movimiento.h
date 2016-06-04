#ifndef _MOVIMIENTO_H_
#define _MOVIMIENTO_H_

class Movimiento {

public:
	
	Movimiento(int id, int tipo, int posX, int posY);
	~Movimiento();

	int getId();
	int getTipo();
	int getPosX();
	int getPosY();

	void setId(int id);
	void setTipo(int tipo);
	void setPosX(int posX);
	void setPosY(int posY);

private:

	int id;
	int tipo;
	int x;
	int y;
};

#endif // _MOVIMIENTO_H_
