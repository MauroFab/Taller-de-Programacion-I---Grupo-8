#ifndef LOG_H_
#define LOG_H_

#include <fstream>
#include <string>
#include <vector>
#include <SDL2/SDL_thread.h>

#define ERROR	"ERROR"
#define WARN    "WARN"
#define INFO	"INFO"
#define DEBUG	"DEBUG"	

using namespace std;

class Log{

private:

	SDL_mutex *mut; 
	string nombreLog;
	ofstream archivoLog;
	vector<string> nivelesConfigurados;

    static bool instanceFlag;
	static Log* single;
    Log();

	void cargarConfiguracion();
	void escribirMensaje(string nivel, string mensaje);

public:
	
	static Log* getInstance();
	virtual ~Log();

	void debug(string message);
	void info(string message);
	void warn(string message);
	void error(string message);
};

#endif 

