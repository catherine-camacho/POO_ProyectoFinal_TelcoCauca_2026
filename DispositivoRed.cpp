#include "DispositivoRed.h"
#include <stdexcept>

DispositivoRed::DispositivoRed(std::string _ip, std::string _mac, bool _estado)
	: direccionIP(_ip), direccionMAC(_mac), estadoOperativo(_estado) {
	
	if (direccionIP.empty()) {
		throw std::invalid_argument("La direccion IP no puede estar vacia");
	}
}

DispositivoRed::~DispositivoRed() {}

std::string DispositivoRed::getDireccionIP() const { return direccionIP; }
std::string DispositivoRed::getDireccionMAC() const { return direccionMAC; }
bool DispositivoRed::getEstadoOperativo() const { return estadoOperativo; }
