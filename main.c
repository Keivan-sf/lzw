#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int number_of_symbols = 0;
struct symbolEntry {
  unsigned int symbol;
  char* ch;
};

struct symbolEntry symbol_table[1000];

int getSymbolViaNumber(unsigned int symbol , struct symbolEntry* result) {
  for(int i = 0; i< number_of_symbols; i++) {
    if(symbol_table[i].symbol == symbol) {
      *result = symbol_table[i];
      return 1;
    }
  }  
  return -1;
}

int getSymbolViaChar(char* ch , struct symbolEntry* result) {
  for(int i = 0; i< number_of_symbols; i++) {
    if(strcmp(symbol_table[i].ch , ch) == 0) {
      *result = symbol_table[i];
      return 1;
    }
  }  
  return -1;
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
    struct symbolEntry s1;
    s1.symbol = 256 + i;
    char b[2] = "";
    sprintf(b, "%d" , i);
    s1.ch = concat("reset , " , b);
    symbol_table[i] = s1;
    number_of_symbols++;
  }
  //
  // for(unsigned int i = 0; i < 10; i++) {
  //   struct symbolEntry * se = malloc(sizeof(struct symbolEntry));
  //   int result = 0;
  //   if((result = getSymbolViaNumber(i + 256 , se)) > 0) {
  //     printf("%d: %s\n", se->symbol , se->ch);
  //   }
  //   free(se);
  // }


  for(unsigned int i = 0; i < 10; i++) {
    struct symbolEntry * se = malloc(sizeof(struct symbolEntry));
    int result = 0;
    
    char b[2] = "";
    sprintf(b, "%d" , i);
    char* ch = concat("reset , " , b);

    if((result = getSymbolViaChar(ch , se)) > 0) {
      printf("%d: %s\n", se->symbol , se->ch);
    }
    free(se);
  }
}
