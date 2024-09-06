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

  done_testing();
  return 0;
}
