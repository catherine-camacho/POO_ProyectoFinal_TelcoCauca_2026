\# Proyecto Final TelcoCauca



\*\*Sistema Distribuido Concurrente de Monitoreo de Infraestructura de Telecomunicaciones e IoT\*\*



Universidad del Cauca - Programacion Orientada a Objetos - 2026.2

Docente: Paola Andrea Bedoya Toro



\## Integrantes

\- Catherine Camacho Chantre

\- NOMBRE COMPLETO DE LA COMPAÑERA



\## Descripcion del proyecto

El objetivo de este proyecto integrador es diseñar e implementar desde cero un Sistema Distribuido

Concurrente de Monitoreo de Infraestructura de Telecomunicaciones e IoT (TelcoCauca). La plataforma

permite gestionar estaciones base, supervisar dispositivos heterogeneos de red (Routers, Gateways

LoRaWAN, Switches de Fibra), procesar mediciones de sensores en tiempo real mediante hilos paralelos,

reaccionar de forma resiliente ante errores de ejecucion y transmitir la telemetria a traves de una

red Cliente-Servidor con Sockets TCP/UDP.



\## Modulos

1\. \*\*Modelado de Dominio e Infraestructura Fisica:\*\* Tecnico, Antena, Torre. Asociacion 1:1 y 1:N, declaracion adelantada class Antena;

2\. \*\*Herencia Multiple y Excepciones:\*\* NodoRedInteligente deriva de DispositivoRed y SensorIoT. Operadores + y <<. ExcepcionNodoRed.

3\. \*\*Polimorfismo e Interfaces Puras:\*\* DispositivoComunicacion (abstracta), ITransmisible, RouterWiFi, GatewayLoRa, SwitchFibra, vector polimorfico, override y guarda nullptr.

4\. \*\*Multihilo y Exclusion Mutua:\*\* MonitorRed con std::thread, std::ref, std::mutex y std::lock\_guard. Eventos de ingenieria 2027.

5\. \*\*Red Cliente-Servidor con Sockets:\*\* ServidorCentral (TCP), NodoEstacionBase (cliente), ServidorUDP/ClienteUDP con TramaSensor (#pragma pack(1)) y timeout.



\## Compilacion en Zinjai (Windows)

\- Herramientas de compilacion: mingw64-gcc7

\- Compilacion, parametros extra: -std=c++11 -pthread

\- Enlazado, parametros extra: -pthread -lws2\_32

