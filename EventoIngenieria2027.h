#ifndef EVENTOINGENIERIA2027_H
#define EVENTOINGENIERIA2027_H

#include <string>

class EventoIngenieria2027 {
private:
	std::string nombre;
	std::string fecha;
	std::string lugar;
public:
	EventoIngenieria2027(std::string _nombre, std::string _fecha, std::string _lugar);
	void mostrar() const;
};

#endif
