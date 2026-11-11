#ifndef NODOREDINTELIGENTE_H
#define NODOREDINTELIGENTE_H

#include <string>
#include <ostream>
#include "DispositivoRed.h"
#include "SensorIoT.h"

// Herencia multiple: hereda de DispositivoRed y de SensorIoT
class NodoRedInteligente : public DispositivoRed, public SensorIoT {
private:
	int idNodo;
	int paquetesProcesados;
public:
	NodoRedInteligente(int _id, int _paquetes,
					   std::string _ip, std::string _mac, bool _estado,
					   std::string _tipo, double _valor);
	~NodoRedInteligente();
	
	// Sobrecarga del operador + (metodo miembro): fusiona dos nodos
	NodoRedInteligente operator+(const NodoRedInteligente& otro) const;
	
	// Sobrecarga del operador << (funcion amiga): imprime el nodo en consola
	friend std::ostream& operator<<(std::ostream& os, const NodoRedInteligente& nodo);
};

#endif
