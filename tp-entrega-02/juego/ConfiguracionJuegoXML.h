#pragma once
#ifndef _CONFIGURACIONJUEGOXML_H_
#define _CONFIGURACIONJUEGOXML_H_

#include "../common/xml/AvionXml.h"
#include "ConfiguracionAvionXML.h"
#include "ConfiguracionProyectilXML.h"

class ConfiguracionJuegoXML {

public:

	static ConfiguracionJuegoXML* getInstance();

	virtual ~ConfiguracionJuegoXML(void);

	void setCaracteristicasMapa(std::string fondo, int tamanioMaximoFondo);
	void setCaracteristicasAvion(int id, std::string avion, int cantFotogramas, int anchoFotograma, int altoFotograma, int velocidad);
	void setCaracteristicasAvion(AvionXml * avionXml);
	void setCaracteristicasProyectil(std::string proyectil, int cantFotogramas, int anchoFotograma, int altoFotograma, int velocidad);

	ConfiguracionAvionXML* getConfiguracionAvion();
	ConfiguracionProyectilXML* getConfiguracionProyectil();
	std::string getPathFondo();
	int getTamanioMaximoFondo();

	//attr para acceso a config del modelo
	AvionXml * confAvionXml;

private:

	ConfiguracionJuegoXML(void);

	static bool instanceFlag;
	static ConfiguracionJuegoXML* instance;

	std::string pathImagenFondo;
	int tamanioMaximoFondo;

	ConfiguracionAvionXML* configAvion;
	ConfiguracionProyectilXML* configProyectil;
};

#endif //_CONFIGURACIONJUEGOXML_H_
