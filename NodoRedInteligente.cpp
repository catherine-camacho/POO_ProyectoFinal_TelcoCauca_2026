#include "NodoRedInteligente.h"
#include "ExcepcionNodoRed.h"

NodoRedInteligente::NodoRedInteligente(int _id, int _paquetes,
									   std::string _ip, std::string _mac, bool _estado,
									   std::string _tipo, double _valor)
	: DispositivoRed(_ip, _mac, _estado), SensorIoT(_tipo, _valor),
	idNodo(_id), paquetesProcesados(_paquetes) {}

NodoRedInteligente::~NodoRedInteligente() {}

NodoRedInteligente NodoRedInteligente::operator+(const NodoRedInteligente& otro) const {
	if (direccionIP != otro.direccionIP) {
		throw ExcepcionNodoRed("IP incompatibles: " + direccionIP + " y " + otro.direccionIP);
	}
	int idCombinado = idNodo * 100 + otro.idNodo;
	int paquetesTotales = paquetesProcesados + otro.paquetesProcesados;
	double lecturaPromedio = (valorLectura + otro.valorLectura) / 2.0;
	
	return NodoRedInteligente(idCombinado, paquetesTotales,
							  direccionIP, direccionMAC, estadoOperativo,
							  tipoSensor, lecturaPromedio);
}

std::ostream& operator<<(std::ostream& os, const NodoRedInteligente& nodo) {
	os << "  Nodo #" << nodo.idNodo
		<< " | IP: " << nodo.direccionIP
		<< " | MAC: " << nodo.direccionMAC
		<< " | Estado: " << (nodo.estadoOperativo ? "Activo" : "Inactivo")
		<< " | Sensor: " << nodo.tipoSensor << " = " << nodo.valorLectura
		<< " | Paquetes: " << nodo.paquetesProcesados;
	return os;
}
