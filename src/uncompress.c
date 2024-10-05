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
unsigned int readNextSymbol(struct uint8_list *input, unsigned int pos,
                            unsigned int seq_len);

void uncompress() {
  initiateSymbolTable();
  fillSymbolTableTill256();
  struct uint8_list *input = malloc(sizeof(struct uint8_list));
  readInputInReverseBitOrder(input);
  unsigned int symbol_count = 257;
  unsigned int seq_len = 9;

  char *workingData = malloc(1 * sizeof(char));
  workingData[0] = '\0';

  char *last_symbol_value = malloc(1 * sizeof(char));
  last_symbol_value[0] = '\0';
  for (unsigned int pos = 0; pos + seq_len < input->len * 8;) {
    if (symbol_count > pow_int(2, seq_len)) {
      seq_len++;
    }
    unsigned int current_symbol = readNextSymbol(input, pos, seq_len);
    pos += seq_len;
    symbol_count++;

    char **chs = malloc(sizeof(char *));
    if (getSymbolValue(current_symbol, chs) > 0) {
      printf("%s", *chs);
      last_symbol_value = *chs;
      char *arg;
      for (unsigned int i = 0; i < strlen(*chs); i++) {
        arg = concatCharToStr(workingData, (*chs)[i]);
        if (getSymbolNumber(arg) >= 0) {
          free(workingData);
          workingData = arg;
        } else {
          addSymbol(arg);
          char *currentChar = malloc(2 * sizeof(char));
          currentChar[0] = (*chs)[i];
          currentChar[1] = 0;
          free(workingData);
          workingData = currentChar;
        }
      }
    } else {
      char *current_seq = concatCharToStr(last_symbol_value, workingData[0]);
      for (int i = 0; i < strlen(current_seq); i++) {
        char *arg = concatCharToStr(workingData, current_seq[i]);
        if (getSymbolNumber(arg) >= 0) {
          free(workingData);
          workingData = arg;
        } else {
          addSymbol(arg);
          char *currentChar = malloc(2 * sizeof(char));
          currentChar[0] = current_seq[i];
          currentChar[1] = 0;
          free(workingData);
          workingData = currentChar;
        }
      }

      if (getSymbolValue(current_symbol, chs) <= 0) {
        printf("\n\nERROR: we still don't have the symbol after re-processing "
               "the previous one \n\n");
      } else {
        printf("%s", *chs);
      };
    }
  }
}

unsigned int readNextSymbol(struct uint8_list *input, unsigned int pos,
                            unsigned int seq_len) {
  unsigned int current_data_reversed = readNBit(input->data, pos, seq_len);
  return reverseBitOrder(current_data_reversed, seq_len);
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
