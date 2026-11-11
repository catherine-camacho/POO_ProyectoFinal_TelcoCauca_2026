#ifndef MONITORRED_H
#define MONITORRED_H

#include <vector>
#include <mutex>
#include "DispositivoComunicacion.h"
#include "EventoIngenieria2027.h"

class MonitorRed {
private:
	std::mutex mtxContador;
public:
	void supervisarDispositivo(const DispositivoComunicacion* dev, int& transmisionesExitosas);
	
	void procesarEventos2027(const std::vector<EventoIngenieria2027>& agenda);
};

#endif
