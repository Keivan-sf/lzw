#include <stdint.h>
#include <stdio.h>

int writeBitsToUint8Array(unsigned int n, unsigned int bit_len,
                          unsigned int currentPos, uint8_t *output);
unsigned reverseBitOrder(unsigned int n, unsigned int bit_len);

int pow_int(int a, int b);
void testWriteBitsToUint8Array2();
void testReverseBitOrder2();
uint8_t reverseUint8BitOrder(uint8_t);
