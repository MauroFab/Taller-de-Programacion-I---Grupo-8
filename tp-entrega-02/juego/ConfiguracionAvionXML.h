#pragma once
#ifndef _CONFIGURACIONAVIONXML_H_
#define _CONFIGURACIONAVIONXML_H_
#include <string>
using namespace std;

class ConfiguracionAvionXML {

public:

	ConfiguracionAvionXML(int id, std::string pathAvion, int cantidadDeFotogramas, int anchoFotograma, int altoFotograma, int velocidad);
	virtual ~ConfiguracionAvionXML(void);

	std::string getPathImagen();
	int getCantidadDeFotogramas();
	int getAnchoFotograma();
	int getAltoFotograma();
	int getVelocidad();
	int getId();

//private:
public:

	std::string pathImagen;
	int cantidadDeFotogramas;
	int anchoFotograma;
	int altoFotograma;
	int velocidad;
	int id;
};
#endif //_CONFIGURACIONAVIONXML_H_
