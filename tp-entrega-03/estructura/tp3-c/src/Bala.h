#ifndef _BALA_H_
#define _BALA_H_

class Bala
{
protected:
	int idOwner;
	bool bMuerto;	
public:
	Bala();
	virtual ~Bala();
	void morir();
};

#endif //_BALA_H_
