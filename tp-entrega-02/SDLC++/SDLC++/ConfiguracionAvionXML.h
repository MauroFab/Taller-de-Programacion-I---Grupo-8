#pragma once
#include "Constantes.h"

class ConfiguracionAvionXML {

public:

	ConfiguracionAvionXML(std::string pathAvion, int cantidadDeFotogramas, int anchoFotograma, int altoFotograma, int velocidad);
	virtual ~ConfiguracionAvionXML(void);

	std::string getPathImagen();
	int getCantidadDeFotogramas();
	int getAnchoFotograma();
	int getAltoFotograma();
	int getVelocidad();

private:

	std::string pathImagen;
	int cantidadDeFotogramas;
	int anchoFotograma;
	int altoFotograma;
	int velocidad;
};

