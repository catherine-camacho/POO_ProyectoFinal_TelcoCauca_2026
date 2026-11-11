#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include <cstring>
#include <stdexcept>
#include <functional>

#include "Tecnico.h"
#include "Antena.h"
#include "Torre.h"
#include "NodoRedInteligente.h"
#include "ExcepcionNodoRed.h"
#include "RouterWiFi.h"
#include "GatewayLoRa.h"
#include "SwitchFibra.h"
#include "MonitorRed.h"
#include "EventoIngenieria2027.h"
#include "Consola.h"
#include "Red.h"
#include "ServidorCentral.h"
#include "NodoEstacionBase.h"
#include "TelemetriaUDP.h"
#include "ExcepcionSocket.h"
#include "ExcepcionRedUDP.h"

const int PUERTO_TCP = 8080;
const int PUERTO_UDP = 8081;
const int PUERTO_SIN_SERVIDOR = 9090;

int main() {
	imprimirTitulo("MODULO 1: Torre, Antenas y Tecnicos (UML)");
	Tecnico t1(101, "Carlos Mendoza", "Infraestructura y Torres");
	Tecnico t2(102, "Laura Restrepo", "Radiofrecuencia 5G");
	t1.mostrarInformacion();
	t2.mostrarInformacion();
	
	Antena a1(1, 1800.0, "4G");
	Antena a2(2, 3500.0, "5G");
	Antena a3(3, 700.0, "4G");
	a1.asignarTecnico(&t1);
	a2.asignarTecnico(&t2);
	a3.asignarTecnico(&t1);
	
	Torre torreCentro(1, "Popayan Centro - Tulcan", 45.0);
	torreCentro.agregarAntena(&a1);
	torreCentro.agregarAntena(&a2);
	torreCentro.agregarAntena(&a3);
	torreCentro.mostrarReporteTorre();
	
	imprimirTitulo("MODULO 2: NodoRedInteligente, operadores y excepciones");
	try {
		NodoRedInteligente n1(1, 120, "192.168.1.10", "AA:BB:CC:00:00:01", true, "Temperatura", 24.5);
		NodoRedInteligente n2(2, 80, "192.168.1.10", "AA:BB:CC:00:00:02", true, "Temperatura", 27.5);
		NodoRedInteligente n3(3, 50, "10.0.0.5", "AA:BB:CC:00:00:03", true, "Humedad", 60.0);
		std::cout << n1 << std::endl;
		std::cout << n2 << std::endl;
		std::cout << n3 << std::endl;
		
		NodoRedInteligente fusion = n1 + n2;
		std::cout << "  Fusion n1 + n2:" << std::endl << fusion << std::endl;
		
		std::cout << "  Intentando n1 + n3 (IP distintas)..." << std::endl;
		NodoRedInteligente invalida = n1 + n3;
		std::cout << invalida << std::endl;
	}
	catch (const ExcepcionNodoRed& e) {
		std::cout << "  CAPTURADA: " << e.what() << std::endl;
	}
	catch (const std::exception& e) {
		std::cout << "  CAPTURADA (general): " << e.what() << std::endl;
	}
	
	try {
		std::cout << "  Creando un nodo con lectura 150.0 (fuera de rango)..." << std::endl;
		NodoRedInteligente malo(4, 10, "192.168.1.30", "AA:BB:CC:00:00:04", true, "Temperatura", 150.0);
	}
	catch (const ExcepcionNodoRed& e) {
		std::cout << "  CAPTURADA: " << e.what() << std::endl;
	}
	
	try {
		std::cout << "  Creando un nodo con IP vacia..." << std::endl;
		NodoRedInteligente sinIP(5, 10, "", "AA:BB:CC:00:00:05", false, "Humedad", 40.0);
	}
	catch (const ExcepcionNodoRed& e) {
		std::cout << "  CAPTURADA: " << e.what() << std::endl;
	}
	
	imprimirTitulo("MODULO 3: Vector polimorfico con guarda nullptr");
	// Coleccion polimorfica: punteros de la base que apuntan a objetos hijos creados con new
	std::vector<DispositivoComunicacion*> red;
	red.push_back(new RouterWiFi("192.168.1.1", 12));
	red.push_back(new GatewayLoRa("192.168.1.50", 868));
	red.push_back(new SwitchFibra("192.168.1.100", 10));
	red.push_back(nullptr);
	
	for (DispositivoComunicacion* dev : red) {
		try {
			procesarDispositivo(dev);
		}
		catch (const std::invalid_argument& e) {
			registrarEventoSeguro(std::string("[Argumento Invalido] ") + e.what());
		}
		catch (const std::exception& e) {
			registrarEventoSeguro(std::string("[Excepcion Generica] ") + e.what());
		}
	}
	
	imprimirTitulo("MODULO 4: Supervision en paralelo (std::thread + mutex)");
	std::vector<EventoIngenieria2027> agenda;
	agenda.push_back(EventoIngenieria2027("XII Congreso Iberoamericano de Innovacion en Salud, Discapacidad y Medicina de Precision", "2-3 marzo 2027", "Bogota, Colombia"));
	agenda.push_back(EventoIngenieria2027("IV Congreso Internacional de Ciencia e Ingenieria CICI 2027 (Universidad Mariana)", "14-16 abril 2027", "Pasto, Colombia"));
	agenda.push_back(EventoIngenieria2027("IEEE LatinIoT 2027 (IEEE Latin American Conference on Internet of Things)", "28-30 abril 2027", "Santiago, Chile"));
	agenda.push_back(EventoIngenieria2027("IEEE ICASSP 2027 (International Conference on Acoustics, Speech and Signal Processing)", "16-21 mayo 2027", "Toronto, Canada"));
	
	MonitorRed monitor;
	int transmisionesExitosas = 0;
	
	std::vector<std::thread> hilos;
	for (DispositivoComunicacion* dev : red) {
		// Hilo sobre funcion miembro: (&Clase::metodo, &instancia, argumentos)
		// std::ref pasa la variable por referencia al hilo
		hilos.push_back(std::thread(&MonitorRed::supervisarDispositivo, &monitor, dev,
									std::ref(transmisionesExitosas)));
	}
	hilos.push_back(std::thread(&MonitorRed::procesarEventos2027, &monitor, std::ref(agenda)));
	
	// join(): espera que cada hilo termine antes de continuar
	for (std::thread& t : hilos) {
		if (t.joinable()) {
			t.join();
		}
	}
	std::cout << "  Transmisiones exitosas: " << transmisionesExitosas
		 << " de " << red.size() << std::endl;
	
	WSADATA datosWinsock;
	// Windows exige iniciar la red (Winsock) antes de usar sockets
	if (WSAStartup(MAKEWORD(2, 2), &datosWinsock) != 0) {
		std::cout << "  No se pudo iniciar Winsock" << std::endl;
	}
	try {
		imprimirTitulo("MODULO 5.1: Servidor Central TCP + Nodos Estacion Base");
		ServidorCentral servidor(PUERTO_TCP);
		servidor.iniciar();
		
		NodoEstacionBase nodoA("Estacion-Popayan", "127.0.0.1", PUERTO_TCP);
		NodoEstacionBase nodoB("Estacion-Timbio", "127.0.0.1", PUERTO_TCP);
		NodoEstacionBase nodoC("Estacion-Piendamo", "127.0.0.1", PUERTO_TCP);
		
		std::thread c1(&NodoEstacionBase::ejecutarSesion, &nodoA, red[0]);
		std::thread c2(&NodoEstacionBase::ejecutarSesion, &nodoB, red[1]);
		std::thread c3(&NodoEstacionBase::ejecutarSesion, &nodoC, red[2]);
		
		// El hilo principal ejecuta accept() en bucle y lanza un hilo por cliente
		servidor.aceptarClientes(3);
		
		c1.join();
		c2.join();
		c3.join();
		
		std::cout << "  Prueba de resiliencia: conectando a un puerto sin servidor..." << std::endl;
		NodoEstacionBase nodoCaido("Estacion-Desconectada", "127.0.0.1", PUERTO_SIN_SERVIDOR);
		nodoCaido.ejecutarSesion(red[0]);
		
		imprimirTitulo("MODULO 5.2: Telemetria UDP con #pragma pack");
		std::cout << "  sizeof(TramaSensor) = " << sizeof(TramaSensor) << " bytes (esperado: 36)" << std::endl;
		
		ServidorUDP servidorUDP(PUERTO_UDP);
		servidorUDP.iniciar();
		std::thread hiloUDP(&ServidorUDP::escuchar, &servidorUDP);
		
		ClienteUDP clienteUDP;
		for (int i = 0; i < 3; i++) {
			TramaSensor trama{};
			trama.idEstacion = 501 + i;
			strncpy(trama.tipoDispositivo, red[i]->getTipo().c_str(), 15);
			trama.temperatura = 24.5f + i;
			trama.humedad = 55.0f + i;
			trama.timestamp = 1700005000;
			clienteUDP.enviarTrama(trama, "127.0.0.1", PUERTO_UDP);
			std::this_thread::sleep_for(std::chrono::milliseconds(200));
		}
		registrarEventoSeguro("Cliente UDP deja de transmitir (simula desconexion)...");
		hiloUDP.join();
	}
	catch (const ExcepcionSocket& e) {
		std::cout << "  [Error de red TCP] " << e.what() << std::endl;
	}
	catch (const ExcepcionRedUDP& e) {
		std::cout << "  [Error de red UDP] " << e.what() << std::endl;
	}
	catch (const std::exception& e) {
		std::cout << "  [Error general] " << e.what() << std::endl;
	}
	WSACleanup();
	
	imprimirTitulo("Liberacion de memoria dinamica");
	// Liberacion de memoria: delete, puntero a nullptr y clear() para no dejar punteros colgantes
	for (size_t i = 0; i < red.size(); i++) {
		delete red[i];
		red[i] = nullptr;
	}
	red.clear();
	std::cout << "  Memoria liberada. Sistema TelcoCauca finalizado correctamente." << std::endl;
	return 0;
}
