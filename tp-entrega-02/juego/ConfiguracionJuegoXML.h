#pragma once
#ifndef _CONFIGURACIONJUEGOXML_H_
#define _CONFIGURACIONJUEGOXML_H_

#include "ConfiguracionProyectilXML.h"

class ConfiguracionJuegoXML {
public:

	static ConfiguracionJuegoXML* getInstance();
	virtual ~ConfiguracionJuegoXML(void);

	void setCaracteristicasMapa(std::string fondo, int tamanioMaximoFondo);
	void setCaracteristicasProyectil(std::string proyectil, int cantFotogramas, int anchoFotograma, int altoFotograma, int velocidad);

	ConfiguracionProyectilXML* getConfiguracionProyectil();
	std::string getPathFondo();
	int getTamanioMaximoFondo();

private:

	ConfiguracionJuegoXML(void);

	static bool instanceFlag;
	static ConfiguracionJuegoXML* instance;

	std::string pathImagenFondo;
	int tamanioMaximoFondo;

	ConfiguracionProyectilXML* configProyectil;
};

#endif //_CONFIGURACIONJUEGOXML_H_
