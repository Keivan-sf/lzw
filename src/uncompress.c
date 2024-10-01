#include "bits.h"
#include "chars.h"
#include "io.h"
#include "symbol_table.h"
#include "unistd.h"
unsigned int readInput(uint8_t **input);

void uncompress() {
  initiateSymbolTable();
  fillSymbolTableTill256();
  uint8_t *input = NULL;
  uint8_t **input_ptr = &input;
  unsigned int number_of_chars = readInput(input_ptr);
  for (int i = 0; i < number_of_chars; i++) {
    printf("%u -> ", input[i]);
    input[i] = reverseUint8BitOrder(input[i]);
    printf("%u\n", input[i]);
  }
}

unsigned int readInput(uint8_t **input_prt) {
  uint8_t *input = malloc(sizeof(uint8_t) * 2);
  unsigned int occupied_bytes = 0;
  unsigned int available_bytes = 1;
  int number_of_chars = 0;
  int iterations = 0;
  char currentByte[1];
  int bytes_read = 0;

  while ((bytes_read = read(STDIN_FILENO, currentByte, 1)) > 0) {
    iterations++;
    if (iterations < 4)
      continue;
    if (occupied_bytes + 1 >= available_bytes) {
      uint8_t *new_input = malloc(sizeof(uint8_t) * (available_bytes + 10));
      copyUintArrayToAnother(input, new_input, available_bytes);
      available_bytes += 10;
      free(input);
      input = new_input;
    }
    input[number_of_chars] = currentByte[0];
    number_of_chars++;
  }

  *input_prt = input;
  return number_of_chars;
}
