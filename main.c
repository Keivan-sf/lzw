#include "chars.h"
#include "io.h"
#include "symbol_table.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
  fillSymbolTableTill256();
  char *workingData = malloc(2 * sizeof(char));
  char ch;

  if ((ch = getchar()) != EOF) {
    char *tempWorking = workingData;
    workingData[0] = ch;
    workingData[1] = 0;
  }

  while ((ch = getchar()) != EOF) {
    char *arg = concatCharToStr(workingData, ch);
    int idx = 0;
    if ((idx = getSymbolNumber(arg)) > 0) {
      free(workingData);
      workingData = arg;
    } else {
      addSymbol(arg);
      writeToOutputArray(getSymbolNumber(workingData), 9);
      char *currentChar = malloc(2 * sizeof(char));
      currentChar[0] = ch;
      currentChar[1] = 0;
      free(workingData);
      workingData = currentChar;
    }
  }

  if (strlen(workingData) > 0) {
    writeToOutputArray(getSymbolNumber(workingData), 9);
  }
  writeLZWPrefixToStdOut();
  writeOutputArrayToStdOut();
}
