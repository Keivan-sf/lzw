#include "../src/bits.h"
#include "../src/io.h"
#include "./libtap/tap.h"

int main() {
  unsigned int n9[] = {0b110100101, 0b011100101, 0b110110101, 0b100100001};
  unsigned int n9r[] = {0b101001011, 0b101001110, 0b101011011, 0b100001001};

  unsigned int n10[] = {0b1101010101, 0b0110100101, 0b1101010100, 0b0001000000};
  unsigned int n10r[] = {0b1010101011, 0b1010010110, 0b0010101011,
                         0b0000001000};

  for (int j = 0; j < 4; j++) {
    unsigned int reversed = reverseBitOrder(n9[j], 9);
    ok(reversed == n9r[j], "Should correctly reverse bit order for %u to %u",
       n9[j], n9r[j]);
  }

  for (int j = 0; j < 4; j++) {
    unsigned int reversed = reverseBitOrder(n10[j], 10);
    ok(reversed == n10r[j], "Should correctly reverse bit order for %u to %u",
       n10[j], n10r[j]);
  }

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
  int is_output_array_ok = 1;
  for (int i = 0; i < 9; i++) {
    if (output[i] != expected_output[i]) {
      is_output_array_ok = 0;
      break;
    }
  }
  ok(is_output_array_ok, "Should write variable bit chunks to uint8 array");

  done_testing();
  return 0;
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
