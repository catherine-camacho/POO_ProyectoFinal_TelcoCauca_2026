#include "RouterWiFi.h"
#include "Consola.h"
#include <thread>
#include <chrono>

RouterWiFi::RouterWiFi(std::string _ip, int _canales)
	: DispositivoComunicacion(_ip, "Router WiFi 6"), canalesActivos(_canales) {}

void RouterWiFi::transmitir() const {

	std::this_thread::sleep_for(std::chrono::milliseconds(150));
	registrarEventoSeguro("Router WiFi 6 [" + ip + "] transmitio datos");
}


std::string RouterWiFi::serializar() const {
	return tipo + "|" + ip + "|" + std::to_string(canalesActivos) + " canales";
}
