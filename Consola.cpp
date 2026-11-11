#include "Consola.h"
#include <iostream>
#include <thread>
#include <mutex>

// Mutex que protege la consola compartida por los hilos (evita la condicion de carrera)
std::mutex mtx_consola;

// RAII: lock_guard bloquea el mutex al crearse y lo libera al salir de la funcion
void registrarEventoSeguro(const std::string& mensaje) {
	std::lock_guard<std::mutex> lock(mtx_consola);
	std::cout << "[HILO " << std::this_thread::get_id() << "] " << mensaje << std::endl;
}

void imprimirTitulo(const std::string& titulo) {
	std::lock_guard<std::mutex> lock(mtx_consola);
	std::cout << std::endl << "==================================================" << std::endl;
	std::cout << " " << titulo << std::endl;
	std::cout << "==================================================" << std::endl;
}
