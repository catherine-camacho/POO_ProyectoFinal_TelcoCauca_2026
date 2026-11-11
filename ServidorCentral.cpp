#include "ServidorCentral.h"
#include "ExcepcionSocket.h"
#include "Consola.h"
#include <thread>
#include <vector>
#include <string>

ServidorCentral::ServidorCentral(int _puerto)
	: puerto(_puerto), server_fd(INVALID_SOCKET) {}

ServidorCentral::~ServidorCentral() {
	if (server_fd != INVALID_SOCKET) {
		closesocket(server_fd);
	}
}

void ServidorCentral::iniciar() {
	// 1. socket(): crea el socket TCP (SOCK_STREAM)
	server_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (server_fd == INVALID_SOCKET) {
		throw ExcepcionSocket("Fallo al crear socket del puerto " + std::to_string(puerto));
	}
	
	sockaddr_in dir{};
	dir.sin_family = AF_INET;
	dir.sin_addr.s_addr = INADDR_ANY;
	dir.sin_port = htons(puerto);
	// 2. bind(): asocia el socket al puerto
	if (bind(server_fd, (sockaddr*)&dir, sizeof(dir)) < 0) {
		throw ExcepcionSocket("Error en bind() del puerto " + std::to_string(puerto));
	}
	
	// 3. listen(): deja el socket esperando conexiones
	if (listen(server_fd, 5) < 0) {
		throw ExcepcionSocket("Error en listen() del puerto " + std::to_string(puerto));
	}
	registrarEventoSeguro("[Servidor TCP] Escuchando en puerto " + std::to_string(puerto) + "...");
}

void ServidorCentral::aceptarClientes(int cantidad) {
	std::vector<std::thread> hilosClientes;
	try {
		for (int i = 1; i <= cantidad; i++) {
			// 4. accept(): acepta un cliente y devuelve un socket nuevo para el
			SOCKET client_fd = accept(server_fd, nullptr, nullptr);
			if (client_fd == INVALID_SOCKET) {
				throw ExcepcionSocket("Error en accept() del puerto " + std::to_string(puerto));
			}
			
			// Un hilo dedicado por cada cliente aceptado
			hilosClientes.push_back(std::thread(&ServidorCentral::atenderCliente, this, client_fd, i));
		}
	}
	catch (const std::exception& e) {
		registrarEventoSeguro(std::string("[Servidor TCP] ") + e.what());
	}
	for (std::thread& t : hilosClientes) {
		if (t.joinable()) {
			t.join();
		}
	}
}

void ServidorCentral::atenderCliente(SOCKET client_fd, int idCliente) {
	try {
		char buffer[256];
		// Deteccion de desconexion: recv() devuelve <= 0 si hay error o el cliente se cayo
		int bytes = recv(client_fd, buffer, sizeof(buffer) - 1, 0);
		if (bytes < 0) {
			throw ExcepcionSocket("Error en recv() con el cliente " + std::to_string(idCliente));
		}
		if (bytes == 0) {
			throw ExcepcionSocket("El cliente " + std::to_string(idCliente) + " cerro la conexion");
		}
		buffer[bytes] = '\0';
		
		registrarEventoSeguro("[Servidor TCP] Cliente " + std::to_string(idCliente)
							  + " envio trama: " + std::string(buffer));
		
		std::string respuesta = "ACK " + std::to_string(idCliente);
		int enviados = send(client_fd, respuesta.c_str(), respuesta.size(), 0);
		if (enviados < 0) {
			throw ExcepcionSocket("Error en send() con el cliente " + std::to_string(idCliente));
		}
	}
	catch (const std::exception& e) {
		registrarEventoSeguro(std::string("[Servidor TCP] ") + e.what());
	}
	// Cierre defensivo del socket del cliente al finalizar la sesion
	closesocket(client_fd);
}
