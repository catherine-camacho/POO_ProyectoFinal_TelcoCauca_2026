#include "MonitorRed.h"
#include "Consola.h"
#include <stdexcept>

void MonitorRed::supervisarDispositivo(const DispositivoComunicacion* dev, int& transmisionesExitosas) {
	try {
		procesarDispositivo(dev);
		
		{
			// Seccion critica protegida con lock_guard (RAII): libera el mutex aun si ocurre una excepcion
			std::lock_guard<std::mutex> lock(mtxContador);
			transmisionesExitosas++;
		}
	}
	// La excepcion se captura dentro del hilo para evitar std::terminate
	catch (const std::exception& e) {
		registrarEventoSeguro(std::string("EXCEPCION EN HILO: ") + e.what());
	}
}

void MonitorRed::procesarEventos2027(const std::vector<EventoIngenieria2027>& agenda) {
	for (const EventoIngenieria2027& ev : agenda) {
		ev.mostrar();
	}
}
