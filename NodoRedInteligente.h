#ifndef NODOREDINTELIGENTE_H
#define NODOREDINTELIGENTE_H

#include <string>
#include <ostream>
#include "DispositivoRed.h"
#include "SensorIoT.h"

class NodoRedInteligente : public DispositivoRed, public SensorIoT {
private:
	int idNodo;
	int paquetesProcesados;  
public:
	NodoRedInteligente(int _id, int _paquetes,
					   std::string _ip, std::string _mac, bool _estado,
					   std::string _tipo, double _valor);
	~NodoRedInteligente();
	
	
	NodoRedInteligente operator+(const NodoRedInteligente& otro) const;
	
	friend std::ostream& operator<<(std::ostream& os, const NodoRedInteligente& nodo);
};

#endif
