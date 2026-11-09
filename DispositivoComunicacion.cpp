#include "DispositivoComunicacion.h"
#include <stdexcept>

DispositivoComunicacion::DispositivoComunicacion(std::string _ip, std::string _tipo)
	: ip(_ip), tipo(_tipo) {}

std::string DispositivoComunicacion::getIp() const { return ip; }
std::string DispositivoComunicacion::getTipo() const { return tipo; }

void procesarDispositivo(const DispositivoComunicacion* dev) {
	if (dev == nullptr) {
		throw std::invalid_argument("Puntero nulo detectado en el contenedor");
	}
	dev->transmitir();   
}
