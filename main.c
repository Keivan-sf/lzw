#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int number_of_symbols = 0;
struct symbolEntry {
  unsigned int symbol;
  char* ch;
};

struct symbolEntry symbol[1000];

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
    s1.symbol = 256;
    char b[2] = "";
    sprintf(b, "%d" , i);
    s1.ch = concat("reset , " , b);
    symbol[i] = s1;
  }

  for(int i = 0; i < 10; i++) {
    struct symbolEntry s1= symbol[i];
    printf("%d: %s\n", s1.symbol , s1.ch);
  }
}
