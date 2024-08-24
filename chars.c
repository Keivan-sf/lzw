#include <stdlib.h>
#include <string.h>

char *concat(const char *str1, const char *str2) {
  char *result = malloc(strlen(str1) + strlen(str2) + 1);
  strcpy(result, str1);
  strcat(result, str2);
  return result;
}

char *concatCharToStr(const char *str, const char c) {
  int current_str_len = strlen(str);
  char *result = malloc((current_str_len + 2) * sizeof(char));
  for (int i = 0; i < current_str_len; i++) {
    result[i] = str[i];
  }
  result[current_str_len] = c;
  result[current_str_len + 1] = 0;
  return result;
}
