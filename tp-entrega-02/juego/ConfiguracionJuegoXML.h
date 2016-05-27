#pragma once
#ifndef _CONFIGURACIONJUEGOXML_H_
#define _CONFIGURACIONJUEGOXML_H_

#include "../common/view/BalaView.h"

class ConfiguracionJuegoXML {
public:

	static ConfiguracionJuegoXML* getInstance();
	virtual ~ConfiguracionJuegoXML(void);

	void setBalaView(BalaView * balaView);

	BalaView * balaView;
private:

	ConfiguracionJuegoXML(void);

	static bool instanceFlag;
	static ConfiguracionJuegoXML* instance;
};

#endif //_CONFIGURACIONJUEGOXML_H_
