#include "chars.h"
#include "io.h"
#include "symbol_table.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void compress();
void decompress();

int main(int argc, char *argv[]) {
  char d_flag[3] = "-d";
  for (int i = 0; i < argc; i++) {
    if (strcmp(argv[i], d_flag) == 0) {
      printf("The arg is: %s", argv[i]);
    }
  }
  return 0;
}

void decompress() { printf("in the decompress method"); }

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
