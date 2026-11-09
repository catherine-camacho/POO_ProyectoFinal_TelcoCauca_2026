#ifndef ROUTERWIFI_H
#define ROUTERWIFI_H

#include "DispositivoComunicacion.h"

class RouterWiFi : public DispositivoComunicacion {
private:
	int canalesActivos;
public:
	RouterWiFi(std::string _ip, int _canales);
	void transmitir() const override;        
	std::string serializar() const override; 
};

#endif
