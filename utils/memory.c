#include "memory.h"

void memcpy(char *src, char *dst, int nbytes) {
  for (int i = 0; i < nbytes; i++) {
    src[i] = dst[i];
  }
}
void memset(uint8_t *dst, uint8_t val, uint32_t len) {
  for (int i = 0; i < len; i++) {
    dst[i] = val;
  }
}
