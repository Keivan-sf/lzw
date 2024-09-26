#include "bits.h"
#include "chars.h"
#include "io.h"
#include "symbol_table.h"
#include "unistd.h"

void uncompress() {
  initiateSymbolTable();
  fillSymbolTableTill256();
  uint8_t input[100000];
  int number_of_chars = 0;
  int iterations = 0;
  char currentByte[1];
  int bytes_read = 0;
  while ((bytes_read = read(STDIN_FILENO, currentByte, 1)) > 0) {
    iterations++;
    if (iterations < 4)
      continue;
    input[number_of_chars] = currentByte[0];
    number_of_chars++;
  }

  uint8_t reversed_input[number_of_chars];
  for (int i = 0; i < number_of_chars; i++) {
    reversed_input[i] = 0;
    reversed_input[i] = reverseUint8BitOrder(input[i]);
  }

  unsigned int nbits[number_of_chars];
  unsigned int current_margin = 9;
  unsigned int bit_pos = 0;

  char *workingData = malloc(2 * sizeof(char));
  unsigned int reversed_data =
      readNBit(reversed_input, bit_pos, current_margin);
  unsigned int data = reverseBitOrder(reversed_data, current_margin);
  bit_pos += current_margin;
  char **ch = malloc(sizeof(char *));
  getSymbolValue(data, ch);
  workingData[0] = (*ch)[0];
  workingData[1] = 0;
  printf("%s", *ch);

  while (bit_pos + current_margin < number_of_chars * 8) {
    unsigned int reversed_data =
        readNBit(reversed_input, bit_pos, current_margin);
    unsigned int data = reverseBitOrder(reversed_data, current_margin);
    bit_pos += current_margin;
    char **ch = malloc(sizeof(char *));
    if (getSymbolValue(data, ch) > 0) {
      char *arg;
      for (int idx = 0; idx < strlen(*ch); idx++) {
        arg = concatCharToStr(workingData, (*ch)[idx]);
        if (getSymbolNumber(arg) >= 0) {
          free(workingData);
          workingData = arg;
        } else {
          addSymbol(arg);
          char *currentChar = malloc(2 * sizeof(char));
          currentChar[0] = (*ch)[idx];
          currentChar[1] = 0;
          free(workingData);
          workingData = currentChar;
        }
      }
      printf("%s", *ch);
    } else {
      char *arg;
      arg = concatCharToStr(workingData, workingData[0]);
      addSymbol(arg);
      char *currentChar = malloc(2 * sizeof(char));
      currentChar[0] = workingData[0];
      currentChar[1] = 0;
      workingData = currentChar;
      if (getSymbolValue(data, ch) <= 0) {
        printf("\n\nwe still don't have the symbol bro\n\n");
      } else {
        printf("%s", *ch);
      };
    }
  }
}
