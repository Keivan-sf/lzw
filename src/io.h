#include <stdint.h>
void writeToOutputArray(unsigned int data, unsigned int bits_len);
void writeOutputArrayToStdOut();
void writeLZWPrefixToStdOut();
void initOutput();
void testIO();
void copyUintArrayToAnother(uint8_t *src, uint8_t *dest, int old_len);
