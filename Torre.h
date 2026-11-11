#ifndef TORRE_H
#define TORRE_H

#include <string>
#include <vector>

// Declaracion adelantada: evita la inclusion ciclica entre Torre.h y Antena.h
class Antena;

class Torre {
private:
	int idTorre;
	std::string ubicacion;
	double alturaMetros;
	// Asociacion 1:N: una torre tiene varias antenas
	std::vector<Antena*> listaAntenas;
public:
	Torre(int _id, std::string _ubicacion, double _altura);
	~Torre();
	
	void agregarAntena(Antena* a);
	int contarAntenas() const;
	void mostrarReporteTorre() const;
};

#endif
