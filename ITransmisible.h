#ifndef ITRANSMISIBLE_H
#define ITRANSMISIBLE_H

#include <string>

// Interfaz pura: solo metodos virtuales puros y sin atributos
class ITransmisible {
public:
	virtual ~ITransmisible() = default;
	virtual std::string serializar() const = 0;
};

#endif
