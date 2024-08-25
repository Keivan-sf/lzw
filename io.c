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

void writeToOutputArray(unsigned int data, unsigned int bits_len) {
  int reversed = reverseBitOrder(data, bits_len);
  pos = writeBitsToUint8Array(reversed, bits_len, pos, output);
}

void writeOutputArrayToStdOut() {
  reverseOutputArrayBits();
  int len = pos / 8 + (pos % 8 > 0);
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

void writeLZWPrefixToStdOut() {
  uint8_t prefix[3] = {0x1f, 0x9d, 0x90};
  for (int i = 0; i < 3; i++) {
    putchar(prefix[i]);
  }
}
