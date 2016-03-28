#include "StringUtil.h"

#include <time.h>
#include <sstream>

using namespace std;

string StringUtil::obtenerFechaAAAAMMDD(char separador){

	ostringstream os;

	time_t segundos = time(NULL);
	tm* d = localtime(&segundos);

	if (separador == NULL)
		os << (d->tm_year + 1900) << (d->tm_mon + 1) << (d->tm_mday) ;
	else
		os << (d->tm_year + 1900) << separador << (d->tm_mon + 1) << separador << (d->tm_mday) ;

	return os.str();
}

string StringUtil::obtenerFechaDDMMAAAA(char separador){

	ostringstream os;

	time_t segundos = time(NULL);
	tm* d = localtime(&segundos);

	if(separador == NULL)
		os << d->tm_mday << (d->tm_mon + 1) << (1900 + d->tm_year);
	else
		os << d->tm_mday << separador << (d->tm_mon + 1) << separador << (1900 + d->tm_year);

	return os.str();
}


string StringUtil::obtenerFechaDDMMAAAAmmss(char separadorFecha, char separadorTiempo){

	ostringstream os;

	time_t segundos = time(NULL);
	tm* d = localtime(&segundos);

	os << d->tm_mday << separadorFecha << (d->tm_mon + 1) << separadorFecha << (1900 + d->tm_year);
	os << separadorTiempo << d->tm_hour << ":" << d->tm_min << ":" << d->tm_sec ;

	return os.str();
}

string StringUtil::intToString(int value){

	ostringstream valueString;

	valueString << value;

	return valueString.str();
}
