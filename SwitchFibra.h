#ifndef SWITCHFIBRA_H
#define SWITCHFIBRA_H

#include "DispositivoComunicacion.h"

class SwitchFibra : public DispositivoComunicacion {
private:
	int velocidadGbps;
public:
	SwitchFibra(std::string _ip, int _velocidad);
	void transmitir() const override;        
	std::string serializar() const override; 
};

#endif
