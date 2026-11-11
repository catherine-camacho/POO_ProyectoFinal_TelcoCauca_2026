#ifndef TRAMASENSOR_H
#define TRAMASENSOR_H

#include <cstdint>

// #pragma pack(1): sin relleno (padding), la estructura mide exactamente 36 bytes
#pragma pack(push, 1)
struct TramaSensor {
	uint32_t idEstacion;
	char tipoDispositivo[16];
	float temperatura;
	float humedad;
	uint64_t timestamp;
};
#pragma pack(pop)

#endif
