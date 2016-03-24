#pragma once
class Codificador
{
public:
	Codificador(void);
	~Codificador(void);
	char* convertir(int unEntero);
private:
	void agregarDatoDeA(char* enteroEnChar, char* datoConvertido);
};

