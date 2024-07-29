#include <stdio.h>
int main() {
int number_of_symbols = 0;
struct symbolEntry {
  unsigned int symbol;
  char* ch;
};
  char ch;
  while((ch = getchar()) != EOF) {
    printf("%c" , ch);
  }
}
