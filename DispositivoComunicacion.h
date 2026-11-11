#ifndef DISPOSITIVOCOMUNICACION_H
#define DISPOSITIVOCOMUNICACION_H

#include <string>
#include "ITransmisible.h"

// Clase base abstracta: no se pueden crear objetos de ella
class DispositivoComunicacion : public ITransmisible {
protected:
	std::string ip;
	std::string tipo;
public:
	DispositivoComunicacion(std::string _ip, std::string _tipo);
	
	// Destructor virtual obligatorio: al hacer delete se libera en cascada
	// (primero la clase hija y luego la base)
	virtual ~DispositivoComunicacion() = default;
	
	// Metodo virtual puro (= 0): cada clase hija debe implementarlo
	virtual void transmitir() const = 0;
	
	std::string getIp() const;
	std::string getTipo() const;
};

void procesarDispositivo(const DispositivoComunicacion* dev);

#endif
