#include "bits.h"
#include "chars.h"
#include "io.h"
#include "symbol_table.h"
#include "unistd.h"

void uncompress() {
  initiateSymbolTable();
  fillSymbolTableTill256();

  uint8_t input[100000];
  int number_of_chars = 0;
  int iterations = 0;
  char currentByte[1];
  int bytes_read = 0;

  while ((bytes_read = read(STDIN_FILENO, currentByte, 1)) > 0) {
    iterations++;
    if (iterations < 4)
      continue;
    input[number_of_chars] = currentByte[0];
    number_of_chars++;
  }

  for (int i = 0; i < number_of_chars; i++) {
    printf("%c", input[i]);
  }
}
