#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
  printf("Hello there guys\n");
  uint8_t output[1000];
  for (int i = 0; i < 1000; i++) {
    output[i] = 0;
  }
  output[0] = output[0] | 0b11000000;
  int iterations = 0;

  unsigned int currentPos = 2;
  unsigned int n = 98;
  unsigned int bit_len = 9;
  unsigned int index = currentPos / 8;
  unsigned int pos = currentPos % 8;
  unsigned int processed_bits = 0;
  unsigned int remaining_bits = bit_len - processed_bits;
  while (1) {
    int availableBits = 8 - pos;
    int shift_number = (remaining_bits - availableBits);
    if (remaining_bits == 0)
      break;
    printf("iteration %d\n", iterations++);
    printf("currentPos %d\n", currentPos);
    printf("index %d\n", index);
    printf("pos %d\n", pos);
    printf("processed_bits %d\n", processed_bits);
    printf("remaining_bits %d\n", remaining_bits);
    printf("availableBits %d\n", availableBits);
    printf("shift_number %d\n", shift_number);
    if (shift_number >= 0) {
      int n1 = n >> shift_number;
      output[index] = output[index] | n1;
      index++;
      currentPos += availableBits;
      processed_bits += availableBits;
      remaining_bits = bit_len - processed_bits;
      index = currentPos / 8;
      pos = currentPos % 8;
    } else {
      printf("else statement\n");
      unsigned int a = 0;
      a = (~a) << remaining_bits;
      a = ~a;
      int n1 = n & a;
      printf("else-> a mask is: %d\n", a);
      printf("else-> n1 with a mask is: %d\n", n1);
      printf("else-> shifting : %d times\n", (shift_number * -1));
      n1 = n1 << (shift_number * -1);
      output[index] = output[index] | n1;
      printf("else-> n1 after shifting: %d\n", n1);
      remaining_bits = 0;
    }
    printf("\n\n");
  }
  printf("\noutput[0]: %d", output[0]);
  printf("\noutput[1]: %d", output[1]);
  unsigned int a = 12;
  a = (~a) << 3;
  a = ~a;
  printf("\na is %d", a);
  return 0;
}
