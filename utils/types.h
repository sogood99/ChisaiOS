#ifndef TYPES_H
#define TYPES_H

typedef unsigned int uint32_t;
typedef int int32_t;
typedef unsigned short uint16_t;
typedef short int16_t;
typedef unsigned char uint8_t;
typedef char int8_t;

#define LO_16(address) (uint16_t)((address)&0xFFFF)
#define HI_16(address) (uint16_t)(((address) >> 16) & 0xFFFF)
#define LO_8(address) (uint8_t)((address)&0xFF)
#define HI_8(address) (uint8_t)(((address) >> 8) & 0xFF)

#endif
