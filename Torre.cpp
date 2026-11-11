#include "Torre.h"
#include "Antena.h"
#include <iostream>

Torre::Torre(int _id, std::string _ubicacion, double _altura)
	: idTorre(_id), ubicacion(_ubicacion), alturaMetros(_altura) {}

// Asociacion: la torre no hace delete de las antenas, solo vacia su lista
Torre::~Torre() {
	listaAntenas.clear();
}

void Torre::agregarAntena(Antena* a) {
	if (a != nullptr) {
		listaAntenas.push_back(a);
	}
}

int Torre::contarAntenas() const {
	return listaAntenas.size();
}

void Torre::mostrarReporteTorre() const {
	std::cout << "  ESTACION BASE TORRE #" << idTorre << " | " << ubicacion
		<< " (" << alturaMetros << " m)" << std::endl;
	std::cout << "  Antenas instaladas (" << listaAntenas.size() << "):" << std::endl;
	for (const Antena* a : listaAntenas) {
		if (a != nullptr) {
			a->mostrarDetalles();
		}
	}
}
