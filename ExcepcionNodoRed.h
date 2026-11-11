#ifndef EXCEPCIONNODORED_H
#define EXCEPCIONNODORED_H

#include <stdexcept>
#include <string>

// Excepcion personalizada derivada de std::runtime_error
// Se lanza ante lecturas fuera de rango o fallas de IP
class ExcepcionNodoRed : public std::runtime_error {
public:
	explicit ExcepcionNodoRed(const std::string& mensaje)
		: std::runtime_error("[ExcepcionNodoRed] " + mensaje) {}
};

#endif
