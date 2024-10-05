#include <stdint.h>
#include <stdio.h>

int writeBitsToUint8Array(unsigned int n, unsigned int bit_len,
                          unsigned int currentPos, uint8_t *output);
int pow_int(int a, int b);
unsigned reverseBitOrder(unsigned int n, unsigned int bit_len);

uint8_t reverseUint8BitOrder(uint8_t n) {
  n = (n & 0xF0) >> 4 | (n & 0x0F) << 4;
  n = (n & 0xCC) >> 2 | (n & 0x33) << 2;
  n = (n & 0xAA) >> 1 | (n & 0x55) << 1;
  return n;
}

unsigned int reverseBitOrder(unsigned int n, unsigned int bit_len) {
  unsigned int n_bit = pow_int(2, bit_len);
  unsigned int reversed_bit = 1;
  unsigned int reversed = 0;
  for (int i = 0; i < bit_len; i++) {
    if (n == 0) {
      break;
    }
    n_bit = n_bit >> 1;
    reversed_bit = 1 << i;
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

unsigned int readNBit(uint8_t *input, unsigned int pos, unsigned int n) {
  unsigned int current_index = pos / 8;
  unsigned int current_pos = pos % 8;
  unsigned int output = 0;
  for (unsigned int i = 0; i < n; i++) {
    current_pos = (pos + i) % 8;
    current_index = (pos + i) / 8;
    uint8_t the_bit = input[current_index] << (current_pos);
    the_bit = the_bit >> 7;
    output += the_bit * (the_bit << (n - 1 - i));
  }
  return output;
}

