#pragma once

class EstadoMapa {
private:
	int cantidadDePixelesQuePasaron;
	int codigoReinicio;	//flasg que indica si se debe reinicar o no 1=true,0=false
public:
	EstadoMapa();
	virtual ~EstadoMapa(void);
	void actualizar(int cantidadPixeles);
	int getSizeBytes();
	int getCantidadDePixeles();
	int getCodigoReinicio();
	void setCantidaDePixeles(int pixeles);
	void setCodigoReinicio(int codigo);
};

