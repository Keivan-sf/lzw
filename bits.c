#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
  printf("Hello there guys\n");
  unsigned int n = 98;
  unsigned int bits = 9;
  uint8_t output[1000];
  for (int i = 0; i < 1000; i++) {
    output[i] = 0;
  }
  return 0;
}
