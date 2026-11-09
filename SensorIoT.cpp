#include "SensorIoT.h"
#include <stdexcept>

SensorIoT::SensorIoT(std::string _tipo, double _valor)
	: tipoSensor(_tipo), valorLectura(_valor) {

	if (valorLectura < -50.0 || valorLectura > 100.0) {
		throw std::out_of_range("Lectura del sensor fuera del rango [-50.0, 100.0]");
	}
}

SensorIoT::~SensorIoT() {}

std::string SensorIoT::getTipoSensor() const { return tipoSensor; }
double SensorIoT::getValorLectura() const { return valorLectura; }
