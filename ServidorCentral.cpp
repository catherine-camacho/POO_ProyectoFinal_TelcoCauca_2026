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
	
	server_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (server_fd == INVALID_SOCKET) {
		throw ExcepcionSocket("Fallo al crear socket");
	}
	
	
	sockaddr_in dir{};
	dir.sin_family = AF_INET;
	dir.sin_addr.s_addr = INADDR_ANY;
	dir.sin_port = htons(puerto);
	if (bind(server_fd, (sockaddr*)&dir, sizeof(dir)) < 0) {
		throw ExcepcionSocket("Error en bind() del puerto " + std::to_string(puerto));
	}
	
	// 3. listen(): habilita la cola de conexiones (hasta 5 en espera)
	if (listen(server_fd, 5) < 0) {
		throw ExcepcionSocket("Error en listen()");
	}
	registrarEventoSeguro("[Servidor TCP] Escuchando en puerto " + std::to_string(puerto) + "...");
}

void ServidorCentral::aceptarClientes(int cantidad) {
	std::vector<std::thread> hilosClientes;
	try {
		for (int i = 1; i <= cantidad; i++) {
			// 4. accept(): espera un cliente y devuelve un socket NUEVO solo para el
			SOCKET client_fd = accept(server_fd, nullptr, nullptr);
			if (client_fd == INVALID_SOCKET) {
				throw ExcepcionSocket("Error en accept()");
			}
			// Un hilo por cliente. "this" es el objeto servidor (como &instancia en la diapositiva)
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
		int bytes = recv(client_fd, buffer, sizeof(buffer) - 1, 0);
		if (bytes < 0) {
			throw ExcepcionSocket("Error en recv() con el cliente " + std::to_string(idCliente));
		}
		if (bytes == 0) {
			throw ExcepcionSocket("El cliente " + std::to_string(idCliente) + " cerro la conexion");
		}
		buffer[bytes] = '\0';   // Fin del texto recibido
		
		registrarEventoSeguro("[Servidor TCP] Cliente " + std::to_string(idCliente)
							  + " envio trama: " + std::string(buffer));
		
		std::string respuesta = "ACK " + std::to_string(idCliente);
		send(client_fd, respuesta.c_str(), respuesta.size(), 0);
	}
	catch (const std::exception& e) {
		// Un error con un cliente NO tumba el servidor
		registrarEventoSeguro(std::string("[Servidor TCP] ") + e.what());
	}
	closesocket(client_fd);
}
