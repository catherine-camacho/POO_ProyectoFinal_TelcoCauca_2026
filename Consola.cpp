#include "Consola.h"
#include <iostream>
#include <thread>
#include <mutex>

std::mutex mtx_consola;  

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
