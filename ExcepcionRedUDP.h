#ifndef EXCEPCIONREDUDP_H
#define EXCEPCIONREDUDP_H

#include <stdexcept>
#include <string>

class ExcepcionRedUDP : public std::runtime_error {
private:
	int codigoError;
public:
	ExcepcionRedUDP(const std::string& msg, int codigo)
		: std::runtime_error("[ExcepcionRedUDP] " + msg + " [Codigo: " + std::to_string(codigo) + "]"),
		codigoError(codigo) {}
	
	int getCodigoError() const { return codigoError; }
};

#endif
