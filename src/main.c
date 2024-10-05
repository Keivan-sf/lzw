#include "bits.h"
#include "chars.h"
#include "io.h"
#include "symbol_table.h"
#include "uncompress.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void compress(unsigned int info_flag);
void parseInput();

int main(int argc, char *argv[]) {
  unsigned int info_flag_enabled = 0;
  unsigned int uncompress_flag_enabled = 0;
  char parse_flag[3] = "-p";
  char uncompress_flag[3] = "-d";
  char info_flag[3] = "-i";
  for (int i = 0; i < argc; i++) {
    if (strcmp(argv[i], parse_flag) == 0) {
      parseInput();
      return 0;
    }
    if (strcmp(argv[i], info_flag) == 0) {
      info_flag_enabled = 1;
    }
    if (strcmp(argv[i], uncompress_flag) == 0) {
      uncompress_flag_enabled = 1;
    }
  }
  if (uncompress_flag_enabled) {
    uncompress();
  } else {
    compress(info_flag_enabled);
  }
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

  // TODO: to uncompress its crucial to read from the reversed in 9bit (n_bint)

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
    if (pos_in_nbit == 8) {
      printf("writing %d\n", separated_nbits[index_in_nbit]);
    }
  }

  for (int i = 0; i < number_of_9_bits; i++) {
    printf("%u\n", separated_nbits[i]);
  }
}

void compress(unsigned int info_flag) {
  initOutput();
  initiateSymbolTable();
  fillSymbolTableTill256();
  char *workingData = malloc(2 * sizeof(char));
  char chs[1];
  int bytes_read = 0;
  int output_bits = 9;
  if ((bytes_read = read(STDIN_FILENO, chs, 1)) > 0) {
    workingData[0] = chs[0];
    workingData[1] = 0;
  }

  int seq = 257;
  while ((bytes_read = read(STDIN_FILENO, chs, 1)) > 0) {
    char *arg = concatCharToStr(workingData, chs[0]);
    if (getSymbolNumber(arg) >= 0) {
      free(workingData);
      workingData = arg;
    } else {
      if (info_flag) {
        printf("adding arg %s\n", arg);
      }
      addSymbol(arg);
      int symbolNumber = getSymbolNumber(workingData);
      if (getNumberOfSymbols() > pow_int(2, output_bits) + 1) {
        output_bits++;
      }
      writeToOutputArray(symbolNumber, output_bits);
      if (info_flag) {
        printf("%d: %d ", seq++, symbolNumber);
      }
      char *currentChar = malloc(2 * sizeof(char));
      currentChar[0] = chs[0];
      currentChar[1] = 0;
      free(workingData);
      workingData = currentChar;
    }
  }

  if (strlen(workingData) > 0) {
    writeToOutputArray(getSymbolNumber(workingData), output_bits);
    if (info_flag) {
      printf("%d ", getSymbolNumber(workingData));
    }
  }

  if (!info_flag) {
    writeLZWPrefixToStdOut();
    writeOutputArrayToStdOut();
  }
}
