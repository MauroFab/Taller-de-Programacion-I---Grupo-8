#pragma once

class EstadoMapa {

public:
	EstadoMapa();
	virtual ~EstadoMapa(void);
	void actualizar(int cantidadPixeles, int offSet);
	int getScrollingOffSet();
	int getCantidadDePixeles();
	int getSizeBytes();
	int getCodigoReinicio();
	void setScrollingOffSet(int offSet);
	void setCantidaDePixeles(int pixeles);
	void setCodigoReinicio(int codigo);

private:
	int scrollingOffSet;
	int cantidadDePixelesQuePasaron;
	int codigoReinicio;
};

