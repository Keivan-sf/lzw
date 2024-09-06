#include "../src/bits.h"
#include "./libtap/tap.h"

int main() {
  printf("in the unit test file\n");
  ok(1 , "test 1");
  ok(0 , "test 2");
  ok(1 , "test 3");
  done_testing();
  return 0;
}
