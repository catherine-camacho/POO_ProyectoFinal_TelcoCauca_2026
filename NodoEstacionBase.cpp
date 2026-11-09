#include "NodoEstacionBase.h"
#include "ExcepcionSocket.h"
#include "Consola.h"
#include <stdexcept>

NodoEstacionBase::NodoEstacionBase(std::string _nombre, std::string _ipServidor, int _puerto)
	: nombre(_nombre), ipServidor(_ipServidor), puerto(_puerto), fd(INVALID_SOCKET) {}

NodoEstacionBase::~NodoEstacionBase() {
	if (fd != INVALID_SOCKET) {
		closesocket(fd);
	}
}

void NodoEstacionBase::conectar() {

	fd = socket(AF_INET, SOCK_STREAM, 0);
	if (fd == INVALID_SOCKET) {
		throw ExcepcionSocket(nombre + ": fallo al crear socket");
	}
	sockaddr_in servidor{};
	servidor.sin_family = AF_INET;
	servidor.sin_port = htons(puerto);
	
	servidor.sin_addr.s_addr = inet_addr(ipServidor.c_str());
	

	if (connect(fd, (sockaddr*)&servidor, sizeof(servidor)) < 0) {
		throw ExcepcionSocket(nombre + ": no se pudo conectar a "
							  + ipServidor + ":" + std::to_string(puerto));
	}
}

void NodoEstacionBase::enviarTrama(const std::string& trama) {

	if (send(fd, trama.c_str(), trama.size(), 0) < 0) {
		throw ExcepcionSocket(nombre + ": error en send()");
	}
}

std::string NodoEstacionBase::recibirRespuesta() {
	char buffer[128];
	int bytes = recv(fd, buffer, sizeof(buffer) - 1, 0);
	if (bytes <= 0) {
		throw ExcepcionSocket(nombre + ": el servidor no respondio");
	}
	buffer[bytes] = '\0';
	return std::string(buffer);
}

void NodoEstacionBase::ejecutarSesion(const ITransmisible* datos) {
	try {
		if (datos == nullptr) {
			throw std::invalid_argument(nombre + ": no hay datos para transmitir (nullptr)");
		}
		conectar();
		enviarTrama(datos->serializar());   
		registrarEventoSeguro("[Cliente " + nombre + "] Respuesta del servidor: " + recibirRespuesta());
	}
	catch (const ExcepcionSocket& e) {          
		registrarEventoSeguro(std::string("[Cliente] ") + e.what());
	}
	catch (const std::exception& e) {           
		registrarEventoSeguro(std::string("[Cliente] Excepcion general: ") + e.what());
	}
	
}
