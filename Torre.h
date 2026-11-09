#ifndef TORRE_H
#define TORRE_H

#include <string>
#include <vector>

class Antena;   // Declaracion adelantada: evita la inclusion ciclica

class Torre {
private:
	int idTorre;
	std::string ubicacion;
	double alturaMetros;
	std::vector<Antena*> listaAntenas;   // Asociacion 1:N
public:
	Torre(int _id, std::string _ubicacion, double _altura);
	~Torre();
	
	void agregarAntena(Antena* a);
	int contarAntenas() const;
	void mostrarReporteTorre() const;
};

#endif
