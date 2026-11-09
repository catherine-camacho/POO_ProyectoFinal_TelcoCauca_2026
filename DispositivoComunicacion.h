#ifndef DISPOSITIVOCOMUNICACION_H
#define DISPOSITIVOCOMUNICACION_H

#include <string>
#include "ITransmisible.h"

class DispositivoComunicacion : public ITransmisible {
protected:
	std::string ip;
	std::string tipo;
public:
	DispositivoComunicacion(std::string _ip, std::string _tipo);
	
	virtual ~DispositivoComunicacion() = default;
	

	virtual void transmitir() const = 0;
	
	std::string getIp() const;
	std::string getTipo() const;
};


void procesarDispositivo(const DispositivoComunicacion* dev);

#endif
