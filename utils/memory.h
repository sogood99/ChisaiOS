#ifndef MEM_H
#define MEM_H

#include "types.h"

void memcpy(char *src, char *dst, int nbytes);
void memset(uint8_t *dst, uint8_t val, uint32_t len);

#endif
