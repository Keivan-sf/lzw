#include "bits.h"
#include "chars.h"
#include "io.h"
#include "symbol_table.h"
#include "unistd.h"

struct uint8_list {
  uint8_t *data;
  unsigned long len, cap;
};

int readInput(struct uint8_list *input);

void uncompress() {
  initiateSymbolTable();
  fillSymbolTableTill256();
  struct uint8_list *input = malloc(sizeof(struct uint8_list));
  unsigned int number_of_chars = readInput(input);
  for (int i = 0; i < input->len; i++) {
    printf("%u %c -> ", input->data[i], input->data[i]);
    input->data[i] = reverseUint8BitOrder(input->data[i]);
    printf("%u\n", input->data[i]);
  }
}

int readInput(struct uint8_list *input) {
  input->data = malloc(sizeof(uint8_t) * 5);
  input->cap = 4;
  input->len = 0;
  int number_of_chars = 0;
  int iterations = 0;
  char currentByte[1];
  int bytes_read = 0;

  while ((bytes_read = read(STDIN_FILENO, currentByte, 1)) > 0) {
    iterations++;
    if (iterations < 4)
      continue;
    // printf("len: %u, cap %u\n", input->len, input->cap);
    if (input->len + 1 >= input->cap) {
      uint8_t *new_input_data = malloc(sizeof(uint8_t) * (input->cap + 10));
      copyUintArrayToAnother(input->data, new_input_data, input->cap);
      input->cap += 10;
      free(input->data);
      input->data = new_input_data;
    }
    input->data[input->len] = currentByte[0];
    input->len++;
  }

  return number_of_chars;
}
