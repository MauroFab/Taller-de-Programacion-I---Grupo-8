#ifndef _AVIONJUGADOR_H_
#define _AVIONJUGADOR_H_

class AvionJugador
{
public:
	int idEquipo;
	int puntaje;
	bool bMuerto;	
public:
	AvionJugador();
	virtual ~AvionJugador();
	bool sinEquipo();
	void aumentarBala();
	void takePuntaje(int puntaje);
	void morir();
};

#endif //_AVIONJUGADOR_H_
