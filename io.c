#include "io.h"
#include "bits.h"
#include <stdint.h>

uint8_t output[10000];
unsigned int pos = 0;
void reverseOutputArrayBits();

void testIO() {
  writeToOutputArray(98, 9);
  writeToOutputArray(97, 9);
  writeToOutputArray(110, 9);
  writeToOutputArray(258, 9);
  writeToOutputArray(97, 9);
  writeOutputArrayToStdOut();
}

int gI = 0;
void writeToOutputArray(unsigned int data, unsigned int bits_len) {
  int reversed = reverseBitOrder(data, bits_len);
  pos = writeBitsToUint8Array(reversed, bits_len, pos, output);
  gI++;
}

void writeOutputArrayToStdOut() {
  int len = pos / 8 + (pos % 8 > 0);
  reverseOutputArrayBits();
  for (int i = 0; i < len; i++) {
    printf("%c", output[i]);
  }
}

void reverseOutputArrayBits() {
  int len = pos / 8 + (pos % 8 > 0);
  for (int i = 0; i < len; i++) {
    output[i] = reverseBitOrder(output[i], 8);
  }
}
