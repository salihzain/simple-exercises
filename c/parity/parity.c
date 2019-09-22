#include "parity.h"
#include <stdint.h>
#include <stdio.h>

/* do not change function signatures */

/* Note this file uses binary notation 1001 1010 to indicate numbers
   in the comments. This notation is NOT supported by C, so don't type
   them in. Convert them to hexadecimal first, e.g. 0x9a */

/* count the number of 1 bits in x */
/* e.g. count_bits(0101) = 2 */
int count_bits(uint8_t x) {
  int count = 0;

  for (int i = 0; i < 8; i++) {
    count += x & 0x1;
    x = x >> 1;
  }

  return count;
}

/* return the value x if the number of 1 bits in x is even */
/* return the value x setting the 8th bit (counting from 1) to 1 if
   the number of 1 bits is odd */
/* e.g. #1:  x = (in binary) 0100 1000, then return value is 0100 1000 */
/*      #2:  x = (in binary) 0100 1001, then return value is 1100 1001 */

/* input x will always be a value 0 to 127 */
/* output value should always contain an even number of 1 bits */
uint8_t even_parity(uint8_t x) {
  if (count_bits(x) % 2 == 0) {
    return x;
  }

  return x ^ 0x80;
}

/* similar to even_parity, except that the number of 1 bits will always be odd
 */
/* e.g. #1:  x = (in binary) 0100 1000, then return value is 1100 1000 */
/*      #2:  x = (in binary) 0100 1001, then return value is 0100 1001 */
/* input x will always be a value 0 to 127 */
/* output value should always contain an odd number of 1 bits */
uint8_t odd_parity(uint8_t x) {
  if (count_bits(x) % 2 != 0) {
    return x;
  }

  return x ^ 0x80;
}

/* calculate the number of bit positions by which x and y differ */
/* e.g. x = (in binary) 1001 1001 */
/*      y = (in binary) 1101 0011 */
/* x and y differ in    SDSS DSDS  = 3 positions */
uint8_t hamming_distance(uint8_t x, uint8_t y) {
  uint8_t same = x ^ y;
  return count_bits(same);
}
