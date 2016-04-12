#include "codificador.h"

Codificador::Codificador(void) {
}

Codificador::~Codificador(void) {
}

// Funciones privadas

int Codificador::agregarDatoDeA(char* enteroEnChar, char* datoConvertido) {

	int i = 0;
	while (enteroEnChar[i] != NULL) {
		datoConvertido[i+1] = enteroEnChar[i];
		i++;
	}
	return i;
}

char* Codificador::convertirAMinuscula(char* palabra) {

	char* resultado = new char[strlen(palabra)+1];
	strcpy(resultado, palabra);

	for (int i = 0; palabra[i]; i++) {
		resultado[i] = tolower(palabra[i]);
	}
	return resultado;
}

// Funciones públicas

char* Codificador::convertir(int unEntero) {

	char* datoConvertido = new char[1024];
	char* enteroEnChar = new char[1024];

	datoConvertido[0] = '0'; // El primer bit en 40 indica un int
	sprintf_s(enteroEnChar, 4,"%d", unEntero);
	int pos_ultimo_caracter = agregarDatoDeA(enteroEnChar, datoConvertido);
	datoConvertido[pos_ultimo_caracter+1] = 0;

	return datoConvertido;
}

char* Codificador::convertir(char unCaracter) {
	
	char* datoConvertido = new char[1024];

	datoConvertido[0] = unCaracter;
	datoConvertido[1] = '\0';
	
	return datoConvertido;
}

char* Codificador::convertir(char unaCadena[]) {
	
	char* datoConvertido = new char[1024];

	strcpy(datoConvertido, unaCadena);
	
	return datoConvertido;
}

char* Codificador::convertir(double unDouble) {
	
	char* datoConvertido = new char[1024];
	char* doubleEnChar = new char[1024];
	
	datoConvertido[0] = 'd';
	sprintf(doubleEnChar,"%lf", unDouble);
	int pos_ultimo_caracter = agregarDatoDeA(doubleEnChar, datoConvertido);
	datoConvertido[pos_ultimo_caracter+1] = 0;

	return datoConvertido;
}

int Codificador::convertir(MensajeXml &mensaje, char* buffer) {

	int cantBytes = mensaje.getSizeBytes();
	int id = mensaje.getId();
	int tipoDato = mensaje.getTipo();
	char* valor = mensaje.getValor();

	int largoValor = cantBytes - (3*sizeof(int));

	int offset = 0;

	memcpy(buffer + offset, &cantBytes, sizeof(int));
	offset += sizeof(int);
	
	memcpy(buffer + offset, &id, sizeof(int));
	offset += sizeof(int);
	
	memcpy(buffer + offset, &tipoDato, sizeof(int));
	offset += sizeof(int);
	
	memcpy(buffer + offset, valor, largoValor);

	return cantBytes;
}