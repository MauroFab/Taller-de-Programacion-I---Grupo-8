#pragma once

class Temporizador {

public:
	Temporizador();
	Temporizador(int segundos);
	virtual ~Temporizador(void);
	bool pasoElTiempoEstablecido();
	void resetear();
	void avanzarTiempo();
	void setTiempo(int segundos);
	int getTiempo();
private:
	int tiempoEstablecido;
	int contadorTiempo;
	int cantidadIteraciones;
	float baseDeTiempo;
};

