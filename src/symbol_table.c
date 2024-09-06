#include "symbol_table.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int number_of_symbols = 0;
int symbol_table_size = 2;
unsigned int symbol_table_reallocation_chunk = 100;
char **symbol_table;

void initiateSymbolTable() {
  symbol_table = malloc(symbol_table_size * sizeof(char *));
  if (!symbol_table) {
    perror("Failed to allocate memory");
    exit(EXIT_FAILURE);
  }
}

int getNumberOfSymbols() { return number_of_symbols; }

void copyCharPointerArrayToAnother(char **src, char **dest, int old_len) {
  for (int i = 0; i < old_len; i++) {
    dest[i] = src[i];
  }
}

int getSymbolValue(unsigned int symbol, char **result) {
  if (symbol >= number_of_symbols) {
    return -1;
  } else {
    *result = symbol_table[symbol];
    return 1;
  }
}

int getSymbolNumber(char *ch) {
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
  if (symbol_table_size < number_of_symbols + 1) {
    char **new_symbol_table = malloc(
        (symbol_table_size + symbol_table_reallocation_chunk) * sizeof(char *));
    copyCharPointerArrayToAnother(symbol_table, new_symbol_table,
                                  symbol_table_size);
    symbol_table_size += symbol_table_reallocation_chunk;
    free(symbol_table);
    symbol_table = new_symbol_table;
  }
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
  for (unsigned int j = 257; j < number_of_symbols; j++) {
    char **ch = malloc(sizeof(char *));
    int result = 0;
    if ((result = getSymbolValue(j, ch)) >= 0) {
      printf("%d: %s\n", j, *ch);
    }
    free(ch);
  }
  printf("-- \n");
}
