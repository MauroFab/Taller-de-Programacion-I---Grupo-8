#include "decodificador.h"

Decodificador::Decodificador(void) {
}

Decodificador::~Decodificador(void) {
}

int Decodificador::decodificar(char* buffer, MensajeXml* mensaje) {
	
	int cantBytes;
	int id;
	int tipoDato;
	char* valor;

	int offset = 0;

	memcpy(&cantBytes, buffer + offset, sizeof(int));
	offset += sizeof(int);
	
	memcpy(&id, buffer + offset, sizeof(int));
	offset += sizeof(int);
	
	memcpy(&tipoDato, buffer + offset, sizeof(int));
	offset += sizeof(int);

	int largoValor = cantBytes - (3*sizeof(int));
	valor = new char[largoValor];
	memcpy(valor, buffer + offset, largoValor);

	mensaje->setId(id);
	mensaje->setTipo(tipoDato);
	mensaje->setValor(valor,largoValor);
	mensaje->calculateSizeBytes();

	delete [] valor;

	return cantBytes;
}

int Decodificador::validarMensaje(MensajeXml* mensaje) {
	
	char* valor = mensaje->getValor();
	int tipoDato = mensaje->getTipo();

	int codigoError = ParserXml::isValidValor(valor, tipoDato);
	
	if (codigoError < 0) {

		if (tipoDato == TIPO_INT) {
			
			if (ParserXml::isValidDouble(valor) == 0) return 1;
			if (ParserXml::isValidChar(valor) == 0) return 2;
			return 3;

		} else if (tipoDato == TIPO_CHAR) {

			if (ParserXml::isValidDouble(valor) == 0) return 4;
			return 5;

		} else if (tipoDato == TIPO_DOUBLE) {

			if (ParserXml::isValidChar(valor) == 0) return 6;
			return 7;
		}
	}

	return codigoError;
}

char* Decodificador::informacionSobreError(int codigoError) {
	
	if (codigoError == 1) return "Error: se esperaba un (int) y se recibió un (double)";
	if (codigoError == 2) return "Error: se esperaba un (int) y se recibió un (char)";
	if (codigoError == 3) return "Error: se esperaba un (int) y se recibió un (string)";

	if (codigoError == 4) return "Error: se esperaba un (char) y se recibió un (double)";
	if (codigoError == 5) return "Error: se esperaba un (char) y se recibió un (string)";

	if (codigoError == 6) return "Error: se esperaba un (double) y se recibió un (char)";
	if (codigoError == 7) return "Error: se esperaba un (double) y se recibió un (string)";

	return "Ok: valor y tipo de dato correctos";
}