#include "SwitchFibra.h"
#include "Consola.h"
#include <thread>
#include <chrono>

SwitchFibra::SwitchFibra(std::string _ip, int _velocidad)
	: DispositivoComunicacion(_ip, "Switch de Fibra"), velocidadGbps(_velocidad) {}

void SwitchFibra::transmitir() const {
	std::this_thread::sleep_for(std::chrono::milliseconds(100));
	registrarEventoSeguro("Switch de Fibra [" + ip + "] transmitio datos");
}

std::string SwitchFibra::serializar() const {
	return tipo + "|" + ip + "|" + std::to_string(velocidadGbps) + " Gbps";
}
