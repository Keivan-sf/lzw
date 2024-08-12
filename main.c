#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int number_of_symbols = 0;
struct symbolEntry {
  unsigned int symbol;
  char* ch;
};

char * symbol_table[1000];

int getSymbolValue(unsigned int symbol , char ** result) {
  if(symbol >= number_of_symbols) {
    return -1;
  } else {
    *result = symbol_table[symbol];
    return 1;
  }
}

int getSymbolNumber(char* ch) {
  for(int i = 0; i< number_of_symbols; i++) {
    if(strcmp(symbol_table[i] , ch) == 0) {
      return i;
    }
  }
  return -1;
}

void addSymbol(char* ch) {
  symbol_table[number_of_symbols] = ch;
  number_of_symbols++;
}

void input() {
  char ch;
  while((ch = getchar()) != EOF) {
    printf("%c" , ch);
  }
}

char* concat(const char* str1, const char* str2) {
  char * result = malloc(strlen(str1) + strlen(str2) + 1);
  strcpy(result , str1);
  strcat(result , str2);
  return result;
}

int main() {
  for(int i = 0; i < 10; i++) {
    char b[2] = "";
    sprintf(b, "%d" , i);
    char* ch = concat("reset , " , b);
    addSymbol(ch) ;
  }

for(unsigned int i = 0; i < 10; i++) {
    // char * ch = symbol_table[i];
    char ** ch = malloc(sizeof(char *));
    int result = 0;
    if((result = getSymbolValue(i , ch)) >= 0) {
      printf("%d: %s\n", i , *ch);
    }
    free(ch);
  }
}


void _testfunction() {
  for(int i = 0; i < 10; i++) {
    char b[2] = "";
    sprintf(b, "%d" , i);
    char* ch = concat("reset , " , b);
    symbol_table[i] = ch;
    number_of_symbols++;
  }

  for(unsigned int i = 0; i < 10; i++) {
    // char * ch = symbol_table[i];
    char ** ch = malloc(sizeof(char *));
    int result = 0;
    if((result = getSymbolValue(i , ch)) >= 0) {
      printf("%d: %s\n", i , *ch);
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
