#include "bits.h"
#include "chars.h"
#include "io.h"
#include "symbol_table.h"
#include "unistd.h"

struct uint8_list {
  uint8_t *data;
  unsigned long len, cap;
};

void readInput(struct uint8_list *input);
void readInputInReverseBitOrder(struct uint8_list *input);

void uncompress() {
  initiateSymbolTable();
  fillSymbolTableTill256();
  struct uint8_list *input = malloc(sizeof(struct uint8_list));
  readInputInReverseBitOrder(input);
}

void readInputInReverseBitOrder(struct uint8_list *input) {
  readInput(input);
  for (int i = 0; i < input->len; i++) {
    input->data[i] = reverseUint8BitOrder(input->data[i]);
  }
}

void readInput(struct uint8_list *input) {
  input->data = malloc(sizeof(uint8_t) * 5);
  input->cap = 4;
  input->len = 0;
  int iterations = 0;
  char currentByte[1];

  while (read(STDIN_FILENO, currentByte, 1) > 0) {
    iterations++;
    if (iterations < 4)
      continue;
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
}
