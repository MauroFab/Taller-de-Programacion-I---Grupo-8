#include <string>

class StringUtil{

public:

	// fechas
	static std::string obtenerFechaAAAAMMDD(char separador = '/');

	static std::string obtenerFechaDDMMAAAA(char separador = '/');

	static std::string obtenerFechaDDMMAAAAmmss(char separadorFecha = '/', char separadorTiempo = ' ');

	static std::string intToString(int value);
};

