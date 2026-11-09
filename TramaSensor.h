#ifndef TRAMASENSOR_H
#define TRAMASENSOR_H

#include <cstdint>

#pragma pack(push, 1)   
struct TramaSensor {
	uint32_t idEstacion;          
	char tipoDispositivo[16];     
	float temperatura;            
	float humedad;                
	uint64_t timestamp;          
};
#pragma pack(pop)       

// Total esperado: 4 + 16 + 4 + 4 + 8 = 36 bytes

#endif
