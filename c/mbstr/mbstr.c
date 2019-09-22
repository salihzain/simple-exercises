#include <stdint.h>
#include <stdio.h>

/*
   Multibyte encodings.

   In ASCII, a standard for encoding mostly English text data, each
   character (e.g. A to Z) occupies one byte. However, using one byte
   per character does not work for languages which may have a large
   number of characters.

   Such languages use a multibyte encoding where one character can
   occupy more than one byte. Many such multibyte encodings exist. One
   such encoding for a hypothetical language is described below:

   Assume that there are 1114112 characters of this language, so we
   can use 21 bits (so characters range from 0 to 1114111).

   Then,

   For values from 0 to 127 (which take 7 bits), the encoding is:

   0xxx xxxx - where the xxx xxxx bit indicate the character.

   e.g. 65 (0100 0001) => 0100 0001

   Thus, values from 0 to 127 consume only one byte.


   For values from 128 to 2047 (which take 11 bits), use two bytes:

   110x xxxx  10xx xxxx

   e.g. 128 (000 1000 0000) => 1100 0010 1000 0000
                                      ^^   ^^ ^^^^

   For values from 2048 to 65535 (which take 16 bits), use three bytes

   1110 xxxx  10xx xxxx  10xx xxxx


   For values from 65535 to 1114111 (which take 21 bits), use four bytes

   1111 0xxx  10xx xxxx  10xx xxxx  10xx xxxx

   This is a variable-length multibyte encoding, where each character
   can occupy 1 to 4 bytes.  In such encodings, a one-to-one relation
   between a character and a byte does not exist. Functions that
   operate on multibyte strings have to be rewritten.

   In this assignment, you will write functions to encode, decode, and
   find the length of strings.
*/

// printB helper function that prints binary representation of uint32_t
// written by me
void printB(uint32_t a) {
  int bits[32];

  for (int i = 0; i < 32; i++) {
    bits[i] = a & 0x1;
    a = a >> 1;
  }

  for (int i = 31; i >= 0; i--) {
    printf("%d ", bits[i]);
    if (i % 4 == 0) {
      printf(" ");
    }
  }

  printf("\n");
}

/*
   Input mbstr is an array containing bytes, its length (in bytes) is nbytes.

   Compute and return the number of characters of the multibyte string.
 */
size_t mbstr_length(uint8_t mbstr[], size_t nbytes) {

  /*
         Note that in the encoding above, a character starts when the byte
         contains a 0 bit in the 8th position (counting from 1), or if the
         byte contains two or more high bits that are 1 followed by a 0.

         Bytes that have one high bit that is one followed by a zero
         (i.e. 10xx xxxx) are actually "inside" a multibyte character.
  */

  /* One strategy is to look at each byte, identify if it is the start of
         a character, and increase the length if so. */

  /* WRITE YOUR CODE HERE */
  int len = 0;

  for (int i = 0; i < nbytes; i++) {
    int starts_w_zero = ((mbstr[i] >> 7) & 0x1) ^ 0x1;
    int starts_w_double_ones = ((mbstr[i] >> 6) & 0x3);

    if (starts_w_zero || starts_w_double_ones == 0x3) {
      len++;
    }
  }

  return len; /* change this to return the actual length*/
}

/*

  Encode characters from 0 to 1114111 (decimal) in mbstr. Assume mbstr
  is an array at least 4 bytes long.

  Return the number of bytes in the encoded value (1 to 4).

  Return 0 if c is outside the valid range of characters.

 */

int encode(uint32_t c, uint8_t mbstr[]) {
  // we will treat each case case separetely

  // case 1 byte
  if (c < 128) {
    mbstr[0] = c;
    return 1;
  }

  // otherwise, we will need to encode into multiple bytes
  int startByte;
  int subByte = 0x80; // 10xx xxxx

  // case 2 bytes
  if (c < 2048) {
    // append the first 6 bits to subByte
    for (int i = 0; i < 6; i++) {
      int bit = c & 0x1;
      subByte |= (bit << i);
      c >>= 1;
    }
    mbstr[1] = subByte;

    startByte = 0xC0; // 110x xxxx
    // append the rest 5 bits to startByte
    for (int i = 0; i < 5; i++) {
      int bit = c & 0x1;
      startByte |= (bit << i);
      c >>= 1;
    }
    mbstr[0] = startByte;

    return 2;
  }

  // case 3 bytes
  if (c < 65536) {
    // append the first 12 bits into two subBytes
    for (int i = 2; i >= 1; i--) {
      for (int j = 0; j < 6; j++) {
        int bit = c & 0x1;
        subByte |= (bit << j);
        c >>= 1;
      }
      mbstr[i] = subByte;
      subByte = 0x80;
    }

    startByte = 0xE0; // 1110 xxxx
    // append the rest 4 bits to startByte
    for (int i = 0; i < 4; i++) {
      int bit = c & 0x1;
      startByte |= (bit << i);
      c >>= 1;
    }
    mbstr[0] = startByte;

    return 3;
  }

  // case 4 bytes
  if (c < 1114112) {
    // append the first 12 bits into three subBytes
    for (int i = 3; i >= 1; i--) {
      for (int j = 0; j < 6; j++) {
        int bit = c & 0x1;
        subByte |= (bit << j);
        c >>= 1;
      }
      mbstr[i] = subByte;
      subByte = 0x80;
    }

    startByte = 0xF0; // 1111 0xxx
    // append the rest 3 bits to startByte
    for (int i = 0; i < 3; i++) {
      int bit = c & 0x1;
      startByte |= (bit << i);
      c >>= 1;
    }
    mbstr[0] = startByte;

    return 4;
  }

  return 0;
}

/*

  Decode the character in mbstr, which is an array of 4 bytes
  (always).

  Return a 32-bit unsigned integer such that:

  bits 0--21 are the decoded character (0--1114111)

  bits 22--24 are the number of bytes decoded (0--4)

  Set bits 0--24 to zero if you encounter an incorrectly encoded
  character.

  Examples:

  #1:

  mbstr = {0x41, 0x42, 0x43, 0x44}

  return value should be (binary)
      0000 0000 0100 0000 0000 0000 0100 0001

      (i.e. 0x400041)

  (the only value decoded was 0x41 which occupies one byte)

  #2:

  mbstr = {0xc1, 0x80, 0x41, 0x42}

  return value should be (binary):
      0000 0000 1000 0000 0000 0000 1000 0000

      (i.e. 0x80080)

  (the value decoded was 0x80 which occupies two bytes)


  #3:

  mbstr = {0xf8, ?, ?, ?}  // ? indicates values are unimportant

  Note: 0xf8 is 1111 1000 which is not a valid encoding.

  Return 0


  #4:

  mbstr = {0xc1, 0xc0, 0x41, 0x42}

  Note: 0xc0 (1100 0000) cannot follow 0xc1 (1100 0001), so this is an
  invalid encoding.

  Return 0.

  #5:

  mbstr = {0xc0, 0x41, 0x41, 0x42}

  Note: 0xc0 (1100 0000) cannot start a character, so this is an also
  an invalid encoding.

*/

uint32_t decode(uint8_t mbstr[]) {
  // 0xc0 cannot start a character
  if (mbstr[0] == 0xc0) {
    return 0x0;
  }

  // Goal: read mbstr[0] and determine how many bytes to decode based on
  // count(1's) in first four bits of mbstr[0]
  uint32_t numBytes = mbstr[0] & 0xF0;

  // case 1 byte
  if (numBytes == 0x40) {
    uint32_t code = mbstr[0];
    code |= 0x400000;
    return code;
  }

  // case 2 bytes
  if (numBytes == 0xC0) {
    uint32_t code = 0;

    // get the last 5 bits from startByte
    int bits = mbstr[0] ^ 0xC0; // removes the leading ones
    code |= bits;

    // check if the subByte has valid encoding
    bits = mbstr[1] & 0xC0; // checks if there are two leading one bits
    if (bits == 0xC0 || bits >> 7 != 1) {
      return 0;
    }

    // get the right 6 bits from subByte
    bits = mbstr[1] ^ 0x80; // removes the leading one bit

    // then shift left by 6 to make room for 6 bits from the subByte
    code <<= 6;

    // append those 6 bits
    code |= bits;

    // finally, encode that we have read two bytes
    code |= 0x800000;
    return code;
  }

  // case 3 bytes
  if (numBytes == 0xE0) {
    uint32_t code = 0;

    // get the last 4 bits from startByte
    int bits = mbstr[0] ^ 0xE0; // removes the leading ones
    code |= bits;

    // check if the subByte has valid encoding
    for (int i = 1; i <= 2; i++) {
      bits = mbstr[i] & 0xC0;

      // two leading 11 bits or leading 0
      if (bits == 0xC0 || bits >> 7 != 1) {
        return 0;
      }

      // get the right 6 bits from subByte
      bits = mbstr[i] ^ 0x80; // removes the leading one bit

      // then shift left by 6 to make room for 6 bits from the subByte
      code <<= 6;

      // append those 6 bits
      code |= bits;
    }

    // finally, encode that we have read three bytes
    code |= 0xC00000;

    return code;
  }

  // case 4 bytes
  if (numBytes == 0xF0) {
    uint32_t code = 0;

    // get the last 3 bits from startByte
    int bits = mbstr[0] ^ 0xF0; // removes the leading ones
    code |= bits;

    // check if the subBytes has valid encoding
    for (int i = 1; i <= 3; i++) {
      bits = mbstr[i] & 0xC0;

      // two leading 11 bits or leading 0
      if (bits == 0xC0 || bits >> 7 != 1) {
        return 0;
      }

      // get the right 6 bits from subByte
      bits = mbstr[i] ^ 0x80; // removes the leading one bit

      // then shift left by 6 to make room for 6 bits from the subByte
      code <<= 6;

      // append those 6 bits
      code |= bits;
    }

    // finally, encode that we have read four bytes
    code |= 0x1000000;

    return code;
  }

  // otherwise, invalid encoding
  return 0;
}
