#include <stdint.h>
#include <stdio.h>

int writeBitsToUint8Array(unsigned int n, unsigned int bit_len,
                          unsigned int currentPos, uint8_t *output);
void testWriteBitsToUint8Array();
void testReverseBitOrder();
int pow_int(int a, int b);
unsigned reverseBitOrder(unsigned int n, unsigned int bit_len);

uint8_t reverseUint8BitOrder(uint8_t n) {
  n = (n & 0xF0) >> 4 | (n & 0x0F) << 4;
  n = (n & 0xCC) >> 2 | (n & 0x33) << 2;
  n = (n & 0xAA) >> 1 | (n & 0x55) << 1;
  return n;
}

void testReverseBitOrder2() {
  unsigned int n9[] = {0b110100101, 0b011100101, 0b110110101, 0b100100001};
  unsigned int n9r[] = {0b101001011, 0b10100111, 0b101011011, 0b100001001};

  unsigned int n10[] = {0b1101010101, 0b0110100101, 0b1101010100, 0b0001000000};
  unsigned int n10r[] = {0b1010101011, 0b1010010110, 0b0010101011,
                         0b0000001000};

  for (int j = 0; j < 4; j++) {
    unsigned int reversed = reverseBitOrder(n9[j], 9);
    printf("reversed %u , expected: %u\n", reversed, n9r[j]);
  }

  for (int j = 0; j < 4; j++) {
    unsigned int reversed = reverseBitOrder(n10[j], 10);
    printf("reversed %u , expected: %u\n", reversed, n10r[j]);
  }
}

void testReverseBitOrder() {
  unsigned int n = 0b110100101;
  unsigned int bit_len = 9;
  unsigned int reversed = reverseBitOrder(n, bit_len);
  printf("intput: %d\n", n);
  printf("reversed bit order: %d\n", reversed);
}

unsigned reverseBitOrder(unsigned int n, unsigned int bit_len) {
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

void testWriteBitsToUint8Array2() {
  uint8_t output[1000];
  for (int i = 0; i < 1000; i++) {
    output[i] = 0;
  }
  int pos = 0;
  pos = writeBitsToUint8Array(0b000110101, 9, pos, output);
  pos = writeBitsToUint8Array(0b010010100, 9, pos, output);
  pos = writeBitsToUint8Array(0b110000100, 9, pos, output);
  pos = writeBitsToUint8Array(0b0100001010, 10, pos, output);
  pos = writeBitsToUint8Array(0b0101101010, 10, pos, output);
  pos = writeBitsToUint8Array(0b1101101010, 10, pos, output);
  pos = writeBitsToUint8Array(0b01000010101, 11, pos, output);

  uint8_t expected_output[] = {0b00011010, 0b10100101, 0b00110000,
                               0b10001000, 0b01010010, 0b11010101,
                               0b10110101, 0b00100001, 0b01010000};
  for (int i = 0; i < 9; i++) {
    printf("output: %d , expected: %d, equeal? %d\n", output[i],
           expected_output[i], output[i] == expected_output[i]);
  }
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
