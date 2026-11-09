#ifndef ANTENA_H
#define ANTENA_H

#include <string>
#include "Tecnico.h"

class Antena {
private:
	int idAntena;
	double frecuenciaMHz;
	std::string tecnologia; //             
	Tecnico* responsableMantenimiento;   
public:
	Antena(int _id, double _frecuencia, std::string _tecnologia);
	~Antena();
	
	int getIdAntena() const;
	double getFrecuenciaMHz() const;
	std::string getTecnologia() const;
	Tecnico* getResponsable() const;
	
	void asignarTecnico(Tecnico* t);
	void mostrarDetalles() const;
};

#endif
