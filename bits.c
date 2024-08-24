#include <stdint.h>
#include <stdio.h>

int writeBitsToUint8Array(unsigned int n, unsigned int bit_len,
                          unsigned int currentPos, uint8_t *output);
void testWriteBitsToUint8Array();
void testReverseBitOrder();
int pow_int(int a, int b);
int reverseBitOrder(unsigned int n, unsigned int bit_len);

void testReverseBitOrder() {
  unsigned int n = 0b110100101;
  unsigned int bit_len = 9;
  unsigned int reversed = reverseBitOrder(n, bit_len);
  printf("intput: %d\n", n);
  printf("reversed bit order: %d\n", reversed);
}

int reverseBitOrder(unsigned int n, unsigned int bit_len) {
  int n_bit = pow_int(2, bit_len);
  int reversed_bit = 1;
  int reversed = 0;
  for (int i = 0; i < bit_len; i++) {
    if (n == 0) {
      break;
    }
    n_bit = pow_int(2, bit_len - 1 - i);
    reversed_bit = pow_int(2, i);
    int is_bit_enabled = n >= n_bit;
    reversed += is_bit_enabled * reversed_bit;
    n -= is_bit_enabled * n_bit;
  }
  return reversed;
}

int pow_int(int a, int b) {
  int answer = 1;
  for (int i = 0; i < b; i++) {
    answer *= a;
  }
  return answer;
}

void testWriteBitsToUint8Array() {
  uint8_t output[1000];
  for (int i = 0; i < 1000; i++) {
    output[i] = 0;
  }
  output[0] = output[0] | 0b11000000;

  unsigned int currentPos = 2;
  unsigned int n = 0b11101110010001010110;
  unsigned int bit_len = 20;
  writeBitsToUint8Array(n, bit_len, currentPos, output);
  printf("\noutput[0]: %d", output[0]);
  printf("\noutput[1]: %d", output[1]);
  printf("\noutput[2]: %d", output[2]);
  printf("\noutput[3]: %d", output[3]);
}

int writeBitsToUint8Array(unsigned int n, unsigned int bit_len,
                          unsigned int currentPos, uint8_t *output) {
  unsigned int index = currentPos / 8;
  unsigned int pos = currentPos % 8;
  unsigned int processed_bits = 0;
  unsigned int remaining_bits = bit_len - processed_bits;
  while (1) {
    int availableBits = 8 - pos;
    int shift_number = (remaining_bits - availableBits);
    if (remaining_bits == 0)
      break;
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
      unsigned int a = 0;
      a = (~a) << remaining_bits;
      a = ~a;
      int n1 = n & a;
      n1 = n1 << (shift_number * -1);
      output[index] = output[index] | n1;
      currentPos += remaining_bits;
      remaining_bits = 0;
    }
  }
  return currentPos;
}
