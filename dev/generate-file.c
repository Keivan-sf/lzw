#include <stdio.h>
#include <string.h>

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
  fclose(f);
  printf("hello there\n");
}
