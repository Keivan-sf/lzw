#include "bits.h"
#include "chars.h"
#include "io.h"
#include "symbol_table.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void compress();
void parseInput();

int main(int argc, char *argv[]) {
  char parse_flag[3] = "-p";
  for (int i = 0; i < argc; i++) {
    if (strcmp(argv[i], parse_flag) == 0) {
      parseInput();
      return 0;
    }
  }
  compress();
  return 0;
}

void parseInput() {
  uint8_t input[100000];
  int number_of_chars = 0;
  int iterations = 0;
  char chs[1];
  int bytes_read = 0;
  while ((bytes_read = read(STDIN_FILENO, chs, 1)) > 0) {
    iterations++;
    if (iterations < 4)
      continue;
    input[number_of_chars] = chs[0];
    number_of_chars++;
  }

  uint8_t reversed_input[number_of_chars];
  for (int i = 0; i < number_of_chars; i++) {
    reversed_input[i] = 0;
    reversed_input[i] = reverseUint8BitOrder(input[i]);
  }

  unsigned int n = 9;
  unsigned int number_of_9_bits = 0;
  unsigned int separated_nbits[number_of_chars];
  for (unsigned int pos = 0; pos < number_of_chars * 8; pos++) {
    unsigned int number = reversed_input[pos / 8];
    unsigned int pos_in_8bit = pos % 8;
    unsigned int pos_in_nbit = pos % n;
    unsigned int index_in_nbit = pos / n;
    if (pos_in_nbit == 0) {
      separated_nbits[index_in_nbit] = 0;
      number_of_9_bits++;
    }
    uint8_t indicator = 128 >> pos_in_8bit;
    unsigned int is_bit_enabled = (indicator & number) > 0;
    separated_nbits[index_in_nbit] += pow_int(2, pos_in_nbit) * is_bit_enabled;
  }

  for (int i = 0; i < number_of_9_bits; i++) {
    // printf(" %d ", i);
    printf("%u\n", separated_nbits[i]);
  }
}

void compress() {
  initOutput();
  initiateSymbolTable();
  fillSymbolTableTill256();
  char *workingData = malloc(2 * sizeof(char));
  char ch;

  if ((ch = getchar()) != EOF) {
    workingData[0] = ch;
    workingData[1] = 0;
  }

  while ((ch = getchar()) != EOF) {
    char *arg = concatCharToStr(workingData, ch);
    if (getSymbolNumber(arg) >= 0) {
      free(workingData);
      workingData = arg;
    } else {
      addSymbol(arg);
      writeToOutputArray(getSymbolNumber(workingData), 9);
      // printf("%d ", getSymbolNumber(workingData));
      char *currentChar = malloc(2 * sizeof(char));
      currentChar[0] = ch;
      currentChar[1] = 0;
      free(workingData);
      workingData = currentChar;
    }
  }

  if (strlen(workingData) > 0) {
    writeToOutputArray(getSymbolNumber(workingData), 9);
    // printf("%d ", getSymbolNumber(workingData));
  }
  // printSymbolsTill256();
  // printSymbolsAfter256();
  writeLZWPrefixToStdOut();
  writeOutputArrayToStdOut();
}
