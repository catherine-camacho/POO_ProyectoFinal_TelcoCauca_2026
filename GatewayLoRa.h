#ifndef GATEWAYLORA_H
#define GATEWAYLORA_H

#include "DispositivoComunicacion.h"

class GatewayLoRa : public DispositivoComunicacion {
private:
	int frecuenciaMHz;
public:
	GatewayLoRa(std::string _ip, int _frecuencia);
	void transmitir() const override;       
	std::string serializar() const override; 
};

#endif
