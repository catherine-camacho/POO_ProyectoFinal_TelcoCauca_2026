#include "Antena.h"
#include <iostream>

Antena::Antena(int _id, double _frecuencia, std::string _tecnologia)
	: idAntena(_id), frecuenciaMHz(_frecuencia), tecnologia(_tecnologia),
	responsableMantenimiento(nullptr) {}
  
Antena::~Antena() {}

int Antena::getIdAntena() const { return idAntena; }
double Antena::getFrecuenciaMHz() const { return frecuenciaMHz; }
std::string Antena::getTecnologia() const { return tecnologia; }
Tecnico* Antena::getResponsable() const { return responsableMantenimiento; }

void Antena::asignarTecnico(Tecnico* t) {
	responsableMantenimiento = t;
}

void Antena::mostrarDetalles() const {
	std::cout << "   * Antena #" << idAntena << " (" << tecnologia << ", "
		<< frecuenciaMHz << " MHz)";
	if (responsableMantenimiento != nullptr) {
		std::cout << " -> Resp: " << responsableMantenimiento->getNombre();
	} else {
		std::cout << " -> Resp: [SIN ASIGNAR]";
	}
	std::cout << std::endl;
}
