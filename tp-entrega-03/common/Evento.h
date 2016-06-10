#pragma once

const int apretadaLaTeclaDeMovimientoHaciaIzquierda = 1;
const int soltadaLaTeclaDeMovimientoHaciaIzquierda = 2;

const int apretadaLaTeclaDeMovimientoHaciaDerecha = 3;
const int soltadaLaTeclaDeMovimientoHaciaDerecha = 4;

const int apretadaLaTeclaDeMovimientoHaciaArriba = 5;
const int soltadaLaTeclaDeMovimientoHaciaArriba = 6;

const int apretadaLaTeclaDeMovimientoHaciaAbajo = 7;
const int soltadaLaTeclaDeMovimientoHaciaAbajo = 8;

const int apretadaLaTeclaDeDisparo= 9;
const int soltadaLaTeclaDeDisparo = 10;

const int apretadaLaTeclaDeRoll = 11;
const int soltadaLaTeclaDeRoll = 12;

const int apretadaLaTeclaDeReinicio= 13;
const int soltadaLaTeclaDeReinicio = 14;

const int seNecesitaLaPosicionDelMapa = 15;
class Evento
{
public:
	//El evento se crea con una de las constantes puestas arriba, se podrían redefinir por herencia cada uno.
	Evento(int numeroDeEvento);
	int getNumeroDeEvento();
	void setNumeroDeEvento(int numero);
	int getSizeBytes();
	~Evento();
private:
	int numeroDeEvento;
};

