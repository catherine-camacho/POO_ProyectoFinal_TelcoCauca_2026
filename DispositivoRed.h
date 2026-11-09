#ifndef DISPOSITIVORED_H
#define DISPOSITIVORED_H

#include <string>

class DispositivoRed {
protected:
	std::string direccionIP;
	std::string direccionMAC;
	bool estadoOperativo;
public:
	DispositivoRed(std::string _ip, std::string _mac, bool _estado);
	~DispositivoRed();
	
	std::string getDireccionIP() const;
	std::string getDireccionMAC() const;
	bool getEstadoOperativo() const;
};

#endif
