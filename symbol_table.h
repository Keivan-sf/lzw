#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int getSymbolValue(unsigned int symbol, char **result);
int getNumberOfSymbols();

int getSymbolNumber(char *ch);

void addSymbol(char *ch);

void fillSymbolTableTill256();

void printSymbolsTill256();

void printSymbolsAfter256();

void initiateSymbolTable();
