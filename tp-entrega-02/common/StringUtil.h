#ifndef STRING_UTIL_H_
#define STRING_UTIL_H_

#include <string>

class StringUtil{

public:

	//Fechas
	static std::string obtenerFechaAAAAMMDD(char separador = '/');

	static std::string obtenerFechaDDMMAAAA(char separador = '/');

	static std::string obtenerFechaDDMMAAAAmmss(char separadorFecha = '/', char separadorTiempo = ' ');

	// Conversion 
	static std::string intToString(int value);
	
	// Replace
	static std::string reemplazarString(std::string str, std::string strOriginal, std::string strNuevo);	
};

#endif 

