#pragma once
#ifndef _CONFIGURACIONPROYECTILXML_H_
#define _CONFIGURACIONPROYECTILXML_H_

#include <string>
using namespace std;

class ConfiguracionProyectilXML {

public:

	ConfiguracionProyectilXML(std::string pathProyectil, int cantidadDeFotogramas, int anchoFotograma, int altoFotograma, int velocidad);
	virtual ~ConfiguracionProyectilXML(void);

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

#endif //_CONFIGURACIONPROYECTILXML_H_