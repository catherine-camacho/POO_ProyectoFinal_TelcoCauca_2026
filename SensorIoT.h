#ifndef SENSORIOT_H
#define SENSORIOT_H

#include <string>

class SensorIoT {
protected:
	std::string tipoSensor;
	double valorLectura;
public:
	SensorIoT(std::string _tipo, double _valor);
	~SensorIoT();
	
	std::string getTipoSensor() const;
	double getValorLectura() const;
};

#endif
