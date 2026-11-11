#ifndef TELEMETRIAUDP_H
#define TELEMETRIAUDP_H

#include <string>
#include "Red.h"
#include "TramaSensor.h"

class ServidorUDP {
private:
	int puerto;
	SOCKET fd;
public:
	ServidorUDP(int _puerto);
	~ServidorUDP();
	
	void iniciar();
	TramaSensor recibirTrama();
	void escuchar();
};

class ClienteUDP {
private:
	SOCKET fd;
public:
	ClienteUDP();
	~ClienteUDP();
	void enviarTrama(const TramaSensor& trama, const std::string& ipDestino, int puerto);
};

#endif
