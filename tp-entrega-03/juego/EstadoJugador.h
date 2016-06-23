#pragma once
class EstadoJugador
{
public:
	EstadoJugador(int id, int puntajeAcumulado);

	//No usar este constructor por fuera del protocolo
	EstadoJugador();

	~EstadoJugador(void);
	int getid();
	int getPuntajeAcumulado();

private:
	int id;
	int puntajeAcumulado;
};

