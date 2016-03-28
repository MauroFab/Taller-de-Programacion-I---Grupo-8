#include <fstream>
#include <string>

using namespace std;

enum LogTipo {LOG_ERROR, LOG_INFORMACION, lOG_DEBUG}; 

class Log{

private:

	ofstream archivoLog;

    static bool instanceFlag;
	static Log* single;
    Log();

	static const char* tipos[];
	void escribirFecha();

public:
	
	static Log* getInstance();
	virtual ~Log();

	void escribirMensaje(string mensaje);

	void escribirMensaje(LogTipo tipo, string mensaje);
};