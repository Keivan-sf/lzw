#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main(int argc, char *argv[]) {
  int size = -1;
  char sizeflag[3] = "-s";
  for (int i = 0; i < argc; i++) {
    if (strcmp(sizeflag, argv[i]) == 0 && i < argc - 1) {
      if (sscanf(argv[i + 1], "%d", &size) < 0 || size < 0) {
        printf("Wrong input\n");
        return -1;
      }
    }
  }
  FILE *f = fopen("generated-test-file", "w");
  srand(time(NULL));
  for (int i = 0; i < size; i++) {
    uint8_t random_byte = rand() % 255;
    fprintf(f, "%c", random_byte);
  }
  fclose(f);
  printf("hello there\n");
}
