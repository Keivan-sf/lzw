#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
  printf("Hello there guys\n");
  unsigned int n = 98;
  unsigned int bit_len = 9;
  uint8_t output[1000];
  for (int i = 0; i < 1000; i++) {
    output[i] = 0;
  }
  output[0] = output[0] | 0b11000000;
  int currentPos = 2;

  unsigned int index = 2 / 8;
  unsigned int pos = 2 % 8;

  int availableBits = 8 - pos;
  if (availableBits > 0) {
    int n1 = n >> (bit_len - availableBits);
    output[index] = output[index] | n1;
    index++;
  }
  printf("output[0]: %d", output[0]);
  return 0;
}
