#pragma once

class EstadoMapa {

public:
	EstadoMapa();
	virtual ~EstadoMapa(void);
	void actualizar(int cantidadPixeles);
	int getSizeBytes();
	int getCantidadDePixeles();
	int getCodigoReinicio();
	void setCantidaDePixeles(int pixeles);
	void setCodigoReinicio(int codigo);

private:
	int cantidadDePixelesQuePasaron;
	int codigoReinicio;
};

