#include "GatewayLoRa.h"
#include "Consola.h"
#include <thread>
#include <chrono>

GatewayLoRa::GatewayLoRa(std::string _ip, int _frecuencia)
	: DispositivoComunicacion(_ip, "Gateway LoRaWAN"), frecuenciaMHz(_frecuencia) {}

void GatewayLoRa::transmitir() const {
	
	std::this_thread::sleep_for(std::chrono::milliseconds(200));
	registrarEventoSeguro("Gateway LoRaWAN [" + ip + "] transmitio datos");
}


std::string GatewayLoRa::serializar() const {
	return tipo + "|" + ip + "|" + std::to_string(frecuenciaMHz) + " MHz";
}
