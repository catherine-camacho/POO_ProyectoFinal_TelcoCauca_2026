#ifndef TECNICO_H
#define TECNICO_H

#include <string>

class Tecnico {
private:
	int idTecnico;
	std::string nombre;
	std::string especialidad;
public:
	Tecnico(int _id, std::string _nombre, std::string _especialidad);
	~Tecnico();
	
	int getIdTecnico() const;
	std::string getNombre() const;
	std::string getEspecialidad() const;
	
	void setNombre(std::string _nombre);
	void setEspecialidad(std::string _especialidad);
	
	void mostrarInformacion() const;
};

#endif
