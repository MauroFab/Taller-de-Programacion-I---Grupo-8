#pragma once

#include <stdio.h>
#include <string.h>
#include "../common/IGenericaVO.h"

class EstadoMapa : public IGenericaVO {

private:
	int sizeBytes;
	int cantidadDePixelesQuePasaron;
	int codigoReinicio;	//flag que indica si se debe reinicar o no 1=true,0=false
	int idEtapa;
	bool mostrarInformacion;
public:
	EstadoMapa();
	virtual ~EstadoMapa(void);
	EstadoMapa(const EstadoMapa& e):sizeBytes(e.sizeBytes),cantidadDePixelesQuePasaron(e.cantidadDePixelesQuePasaron),
	codigoReinicio(e.codigoReinicio),idEtapa(e.idEtapa),mostrarInformacion(e.mostrarInformacion){};
	void EstadoMapa::operator=(const EstadoMapa &e){this->sizeBytes=e.sizeBytes; this->cantidadDePixelesQuePasaron=e.cantidadDePixelesQuePasaron;
	this->codigoReinicio=e.codigoReinicio;this->idEtapa=e.idEtapa;this->mostrarInformacion=e.mostrarInformacion;};
	void actualizar(int cantidadPixeles);
	int getSizeBytes();
	int getCantidadDePixeles();
	int getCodigoReinicio();
	int getIdEtapa();
	void terminoEtapa();
	void empezoEtapa();
	bool hayQueMostrarInformacion();
	void setCantidaDePixeles(int pixeles);
	void setCodigoReinicio(int codigo);
	void setIdEtapa(int id);
	void calculateSizeBytes();
	void toString(TCadena1000 cadena);
};

