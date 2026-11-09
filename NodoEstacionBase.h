#ifndef NODOESTACIONBASE_H
#define NODOESTACIONBASE_H

#include <string>
#include "Red.h"
#include "ITransmisible.h"

class NodoEstacionBase {
private:
	std::string nombre;
	std::string ipServidor;
	int puerto;
	SOCKET fd;
public:
	NodoEstacionBase(std::string _nombre, std::string _ipServidor, int _puerto);
	~NodoEstacionBase();   
	
	void conectar();
	void enviarTrama(const std::string& trama);
	std::string recibirRespuesta();
	

	void ejecutarSesion(const ITransmisible* datos);
};

#endif
