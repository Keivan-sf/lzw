#include "chars.h"
#include "io.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int number_of_symbols = 0;
struct symbolEntry {
  unsigned int symbol;
  char *ch;
};

char *symbol_table[1000];

int getSymbolValue(unsigned int symbol, char **result) {
  if (symbol >= number_of_symbols) {
    return -1;
  } else {
    *result = symbol_table[symbol];
    return 1;
  }
}

unsigned int getSymbolNumber(char *ch) {
  for (int i = 0; i < number_of_symbols; i++) {
    if (i == 256)
      continue;
    if (strcmp(symbol_table[i], ch) == 0) {
      return i;
    }
  }
  return -1;
}

void addSymbol(char *ch) {
  symbol_table[number_of_symbols] = ch;
  number_of_symbols++;
}

void fillSymbolTableTill256() {
  uint8_t i = 0;
  for (int j = 0; j < 256; j++) {
    char *b = malloc(2 * sizeof(char));
    b[0] = i;
    addSymbol(b);
    i++;
  }
  // reserved for reset character
  number_of_symbols++;
}

void printSymbolsTill256() {
  for (unsigned int j = 0; j < 256; j++) {
    char **ch = malloc(sizeof(char *));
    int result = 0;
    if ((result = getSymbolValue(j, ch)) >= 0) {
      printf("%c", *(*ch + 0));
    }
    free(ch);
  }
}

void printSymbolsAfter256() {
  printf("-- | ");
  for (unsigned int j = 257; j < number_of_symbols; j++) {
    char **ch = malloc(sizeof(char *));
    int result = 0;
    if ((result = getSymbolValue(j, ch)) >= 0) {
      printf("%s | ", *ch);
    }
    free(ch);
  }
  printf("--\n");
}

int main() {
  fillSymbolTableTill256();
  char *workingData = malloc(2 * sizeof(char));
  char ch;

  if ((ch = getchar()) != EOF) {
    // printf("curr: %c %d\n", ch, ch);
    char *tempWorking = workingData;
    workingData[0] = ch;
    workingData[1] = 0;
  }

  // printf("working: %s\n", workingData);

  while ((ch = getchar()) != EOF) {
    // printf("curr: %c %d\n", ch, ch);
    char *arg = concatCharToStr(workingData, ch);
    // printf("arg: %s\n", arg);
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
    // printf("\n\nworking: %s\n", workingData);
    // printSymbolsAfter256();
  }

  if (strlen(workingData) > 0) {
    // printf("\n> last output: %s %d\n", workingData,
    // getSymbolNumber(workingData));
    writeToOutputArray(getSymbolNumber(workingData), 9);
  }
  writeOutputArrayToStdOut();
}

int _main() { testIO(); }

void _testfunction() {
  for (int i = 0; i < 10; i++) {
    char b[2] = "";
    sprintf(b, "%d", i);
    char *ch = concat("reset , ", b);
    symbol_table[i] = ch;
    number_of_symbols++;
  }

  for (unsigned int i = 0; i < 10; i++) {
    // char * ch = symbol_table[i];
    char **ch = malloc(sizeof(char *));
    int result = 0;
    if ((result = getSymbolValue(i, ch)) >= 0) {
      printf("%d: %s\n", i, *ch);
    }
    free(ch);
  }

  //
  // for(unsigned int i = 0; i < 10; i++) {
  //   int result = 0;
  //
  //   char b[2] = "";
  //   sprintf(b, "%d" , i);
  //   char* ch = concat("reset , " , b);
  //
  //   if((result = getSymbolNumber(ch)) > -1) {
  //     printf("%d: %s\n", result , ch);
  //   }
  //   free(ch);
  // }
}
