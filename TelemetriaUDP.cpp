#include "TelemetriaUDP.h"
#include "ExcepcionRedUDP.h"
#include "Consola.h"


ServidorUDP::ServidorUDP(int _puerto) : puerto(_puerto), fd(INVALID_SOCKET) {}

ServidorUDP::~ServidorUDP() {
	if (fd != INVALID_SOCKET) {
		closesocket(fd);
	}
}

void ServidorUDP::iniciar() {
	fd = socket(AF_INET, SOCK_DGRAM, 0);   
	if (fd == INVALID_SOCKET) {
		throw ExcepcionRedUDP("Fallo al crear socket UDP", WSAGetLastError());
	}
	sockaddr_in dir{};
	dir.sin_family = AF_INET;
	dir.sin_addr.s_addr = INADDR_ANY;
	dir.sin_port = htons(puerto);
	if (bind(fd, (sockaddr*)&dir, sizeof(dir)) < 0) {
		throw ExcepcionRedUDP("Error en bind() UDP", WSAGetLastError());
	}
	
	
	DWORD tiempo = 3000;
	setsockopt(fd, SOL_SOCKET, SO_RCVTIMEO, (const char*)&tiempo, sizeof(tiempo));
	
	registrarEventoSeguro("[Servidor UDP] Esperando telemetria en puerto "
						  + std::to_string(puerto) + " (timeout 3 s)");
}

TramaSensor ServidorUDP::recibirTrama() {
	TramaSensor trama;
	sockaddr_in cliente{};
	int len = sizeof(cliente);
	
	int bytes = recvfrom(fd, reinterpret_cast<char*>(&trama), sizeof(trama), 0,
						 (sockaddr*)&cliente, &len);
	if (bytes < 0) {
		int codigo = WSAGetLastError();
		if (codigo == WSAETIMEDOUT) {
			throw ExcepcionRedUDP("TIMEOUT: No se recibio datagrama", codigo);
		}
		throw ExcepcionRedUDP("ERROR CATASTROFICO UDP", codigo);
	}
	return trama;
}

void ServidorUDP::escuchar() {
	int recibidas = 0;
	try {
		while (true) {
			TramaSensor t = recibirTrama();
			recibidas++;
			registrarEventoSeguro("[UDP RX] Estacion " + std::to_string(t.idEstacion)
								  + " (" + t.tipoDispositivo + ") Temp: "
								  + std::to_string(t.temperatura) + " C");
		}
	}
	catch (const ExcepcionRedUDP& e) {
	
		registrarEventoSeguro(std::string("[Servidor UDP] ") + e.what());
		registrarEventoSeguro("[Servidor UDP] Tramas recibidas: " + std::to_string(recibidas)
							  + ". El sistema sigue estable.");
	}
}


ClienteUDP::ClienteUDP() {
	fd = socket(AF_INET, SOCK_DGRAM, 0);
	if (fd == INVALID_SOCKET) {
		throw ExcepcionRedUDP("Fallo al crear socket UDP del cliente", WSAGetLastError());
	}
}

ClienteUDP::~ClienteUDP() {
	if (fd != INVALID_SOCKET) {
		closesocket(fd);
	}
}

void ClienteUDP::enviarTrama(const TramaSensor& trama, const std::string& ipDestino, int puerto) {
	sockaddr_in destino{};
	destino.sin_family = AF_INET;
	destino.sin_port = htons(puerto);
	destino.sin_addr.s_addr = inet_addr(ipDestino.c_str());
	
	
	int enviados = sendto(fd, reinterpret_cast<const char*>(&trama), sizeof(trama), 0,
						  (sockaddr*)&destino, sizeof(destino));
	if (enviados < 0) {
		throw ExcepcionRedUDP("Error en sendto()", WSAGetLastError());
	}
}
