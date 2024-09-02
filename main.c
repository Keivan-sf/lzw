#include "bits.h"
#include "chars.h"
#include "io.h"
#include "symbol_table.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
  uint8_t input[10000];
  int number_of_chars = 0;
  int iterations = 0;
  char ch;
  while ((ch = getchar()) != EOF) {
    iterations++;
    if (iterations < 4)
      continue;
    input[number_of_chars] = ch;
    number_of_chars++;
  }

  uint8_t reversed_input[number_of_chars];
  for (int i = 0; i < number_of_chars; i++) {
    reversed_input[i] = 0;
    reversed_input[i] = reverseUint8BitOrder(input[i]);
  }
  printf("%s", reversed_input);
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
