#include "EventoIngenieria2027.h"
#include "Consola.h"

EventoIngenieria2027::EventoIngenieria2027(std::string _nombre, std::string _fecha, std::string _lugar)
	: nombre(_nombre), fecha(_fecha), lugar(_lugar) {}

void EventoIngenieria2027::mostrar() const {
	registrarEventoSeguro("Evento 2027: " + nombre + " | " + fecha + " | " + lugar);
}
