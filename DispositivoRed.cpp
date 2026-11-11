#include "DispositivoRed.h"
#include "ExcepcionNodoRed.h"

DispositivoRed::DispositivoRed(std::string _ip, std::string _mac, bool _estado)
	: direccionIP(_ip), direccionMAC(_mac), estadoOperativo(_estado) {
	if (direccionIP.empty()) {
		throw ExcepcionNodoRed("Falla de IP: el nodo con MAC " + direccionMAC
							   + " no tiene direccion IP");
	}
}

DispositivoRed::~DispositivoRed() {}

std::string DispositivoRed::getDireccionIP() const { return direccionIP; }
std::string DispositivoRed::getDireccionMAC() const { return direccionMAC; }
bool DispositivoRed::getEstadoOperativo() const { return estadoOperativo; }
