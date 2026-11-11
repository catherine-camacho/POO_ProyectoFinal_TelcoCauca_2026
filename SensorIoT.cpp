#include "SensorIoT.h"
#include "ExcepcionNodoRed.h"

SensorIoT::SensorIoT(std::string _tipo, double _valor)
	: tipoSensor(_tipo), valorLectura(_valor) {
	if (valorLectura < -50.0 || valorLectura > 100.0) {
		throw ExcepcionNodoRed("Lectura fuera de rango [-50.0, 100.0] en sensor de "
							   + tipoSensor + ": " + std::to_string(valorLectura));
	}
}

SensorIoT::~SensorIoT() {}

std::string SensorIoT::getTipoSensor() const { return tipoSensor; }
double SensorIoT::getValorLectura() const { return valorLectura; }
