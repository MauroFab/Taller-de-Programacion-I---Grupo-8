#pragma once

class EstadoMapa {
private:
	int cantidadDePixelesQuePasaron;
	int codigoReinicio;	//flag que indica si se debe reinicar o no 1=true,0=false
	int idEtapa;
public:
	EstadoMapa();
	virtual ~EstadoMapa(void);
	void actualizar(int cantidadPixeles);
	int getSizeBytes();
	int getCantidadDePixeles();
	int getCodigoReinicio();
	int getIdEtapa();
	void setCantidaDePixeles(int pixeles);
	void setCodigoReinicio(int codigo);
	void setIdEtapa(int id);
};

