#include "io.h"
#include "bits.h"
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>

unsigned int outputSize = 0;
unsigned int ouput_reallocation_chunk_size = 100;
uint8_t *output;
unsigned int pos = 0;
void reverseOutputArrayBits();

unsigned int getLen() { return pos / 8 + (pos % 8 > 0); }

void copyUintArrayToAnother(uint8_t *src, uint8_t *dest, int old_len) {
  for (int i = 0; i < old_len; i++) {
    dest[i] = src[i];
  }
}

void initOutput() {
  output = malloc(1 * sizeof(uint8_t));
  output[0] = 0;
  outputSize = 1;
}

void initializeWithZeros(int start, int end, uint8_t *output) {
  for (; start < end; start++) {
    output[start] = 0;
  }
}

void writeToOutputArray(unsigned int data, unsigned int bits_len) {
  int neededSize = getLen() + bits_len / 8 + 2;
  if (outputSize < neededSize) {
    output = realloc(output, outputSize + ouput_reallocation_chunk_size);
    initializeWithZeros(outputSize, outputSize + ouput_reallocation_chunk_size,
                        output);
    outputSize += 100;
  }

  int reversed = reverseBitOrder(data, bits_len);
  pos = writeBitsToUint8Array(reversed, bits_len, pos, output);
}

void writeOutputArrayToStdOut() {
  reverseOutputArrayBits();
  int len = getLen();
  for (int i = 0; i < len; i++) {
    printf("%c", output[i]);
  }
}

void reverseOutputArrayBits() {
  int len = getLen();
  for (int i = 0; i < len; i++) {
    output[i] = reverseUint8BitOrder(output[i]);
  }
}

void writeLZWPrefixToStdOut() {
  uint8_t prefix[3] = {0x1f, 0x9d, 0x90};
  for (int i = 0; i < 3; i++) {
    putchar(prefix[i]);
  }
}
