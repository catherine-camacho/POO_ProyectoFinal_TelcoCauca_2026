#ifndef SERVIDORCENTRAL_H
#define SERVIDORCENTRAL_H

#include "Red.h"

class ServidorCentral {
private:
	int puerto;
	SOCKET server_fd;   
public:
	ServidorCentral(int _puerto);
	~ServidorCentral();
	
	void iniciar();                                       
	void aceptarClientes(int cantidad);                  
	void atenderCliente(SOCKET client_fd, int idCliente); 
};

#endif
