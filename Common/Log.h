#include <fstream>
#include <string>
#include <list>
#include <SDL2/SDL_thread.h>

using namespace std;

enum NivelLog {LOG_ERROR, LOG_ADVERTENCIA, LOG_INFORMACION, LOG_DEBUG}; 

class Log{

private:

	static const char* textoNiveles[];
	std::list<int> nivelesConfigurados;
	ofstream archivoLog;

    static bool instanceFlag;
	static Log* single;
    Log();

	void escribirFecha();
	void escribirMensaje(NivelLog nivel, string mensaje);
	SDL_mutex *mut; 

public:
	
	static Log* getInstance();
	virtual ~Log();

	void debug(string message);
	void info(string message);
	void warn(string message);
	void error(string message);

};