#include <stdint.h>
#include <stdio.h>

int writeBitsToUint8Array(unsigned int n, unsigned int bit_len,
                          unsigned int currentPos, uint8_t *output);
int reverseBitOrder(unsigned int n, unsigned int bit_len);
