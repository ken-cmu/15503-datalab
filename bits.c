/*
 * CS:APP Data Lab
 *
 * <Please put your name and userid here>
 *
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 */

/* Instructions to Students:

You will provide your solution to the Data Lab by
editing the collection of functions in this source file.

INTEGER CODING RULES:

  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code
  must conform to the following style:

  long Funct(long arg1, long arg2, ...) {
      // brief description of how your implementation works
      long var1 = Expr1;
      ...
      long varM = ExprM;

      varJ = ExprJ;
      ...
      varN = ExprN;
      return ExprR;
  }

  Each "Expr" is an expression using ONLY the following:
  1. (Long) integer constants 0 through 255 (0xFFL), inclusive. You are
      not allowed to use big constants such as 0xffffffffL.
  2. Function arguments and local variables (no global variables).
  3. Local variables of type int and long
  4. Unary integer operations ! ~
     - Their arguments can have types int or long
     - Note that ! always returns int, even if the argument is long
  5. Binary integer operations & ^ | + << >>
     - Their arguments can have types int or long
  6. Casting from int to long and from long to int

  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.

  You are expressly forbidden to:
  1. Use any control constructs such as if, do, while, for, switch, etc.
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions.
  5. Use any other operations, such as &&, ||, -, or ?:
  6. Use any form of casting other than between int and long.
  7. Use any data type other than int or long.  This implies that you
     cannot use arrays, structs, or unions.

  You may assume that your machine:
  1. Uses 2s complement representations for int and long.
  2. Data type int is 32 bits, long is 64.
  3. Performs right shifts arithmetically.
  4. Has unpredictable behavior when shifting if the shift amount
     is less than 0 or greater than 31 (int) or 63 (long)

EXAMPLES OF ACCEPTABLE CODING STYLE:
  //
  // pow2plus1 - returns 2^x + 1, where 0 <= x <= 63
  //
  long pow2plus1(long x) {
     // exploit ability of shifts to compute powers of 2
     // Note that the 'L' indicates a long constant
     return (1L << x) + 1L;
  }

  //
  // pow2plus4 - returns 2^x + 4, where 0 <= x <= 63
  //
  long pow2plus4(long x) {
     // exploit ability of shifts to compute powers of 2
     long result = (1L << x);
     result += 4L;
     return result;
  }

NOTES:
  1. Use the dlc (data lab checker) compiler (described in the handout) to
     check the legality of your solutions.
  2. Each function has a maximum number of operations (integer, logical,
     or comparison) that you are allowed to use for your implementation
     of the function.  The max operator count is checked by dlc.
     Note that assignment ('=') is not counted; you may use as many of
     these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. Use the BDD checker to formally verify your functions
  5. The maximum number of ops for each function is given in the
     header comment for each function. If there are any inconsistencies
     between the maximum ops in the writeup and in this file, consider
     this file the authoritative source.

CAUTION:
  Do not add an #include of <stdio.h> (or any other C library header)
  to this file.  C library headers almost always contain constructs
  that dlc does not understand.  For debugging, you can use printf,
  which is declared for you just below.  It is normally bad practice
  to declare C library functions by hand, but in this case it's less
  trouble than any alternative.

  dlc will consider each call to printf to be a violation of the
  coding style (function calls, after all, are not allowed) so you
  must remove all your debugging printf's again before submitting your
  code or testing it with dlc or the BDD checker.  */

extern int printf(const char *, ...);

/* Edit the functions below.  Good luck!  */
/*
 * bitMatch - Create mask indicating which bits in x match those in y
 *            using only ~ and &
 *   Example: bitMatch(0x7L, 0xEL) = 0xFFFFFFFFFFFFFFF6L
 *   Legal ops: ~ &
 *   Max ops: 14
 *   Rating: 1
 */
long bitMatch(long x, long y) {
    // x & y | ~x & ~ y
    // ~ (~(x & y) & ~(~x & ~y))
    return ~(~(x & y) & ~(~x & ~y));
}
/*
 * implication - given input x and y, which are binary
 * (taking  the values 0 or 1), return x -> y in propositional logic -
 * 0 for false, 1 for true
 *
 * Below is a truth table for x -> y where A is the result
 *
 * |-----------|-----|
 * |  x  |  y  |  A  |
 * |-----------|-----|
 * |  1  |  1  |  1  |
 * |-----------|-----|
 * |  1  |  0  |  0  |
 * |-----------|-----|
 * |  0  |  1  |  1  |
 * |-----------|-----|
 * |  0  |  0  |  1  |
 * |-----------|-----|
 *
 *
 *   Example: implication(1L,1L) = 1L
 *            implication(1L,0L) = 0L
 *   Legal ops: ! ~ ^ |
 *   Max ops: 5
 *   Rating: 2
 */
long implication(long x, long y) {
    // !(x ^ y) | !x & y
    // !(x ^ y) | !x
    return !(x ^ y) | !x;
}
/*
 * leastBitPos - return a mask that marks the position of the
 *               least significant 1 bit. If x == 0, return 0
 *   Example: leastBitPos(96L) = 0x20L
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 2
 */
long leastBitPos(long x) {
    // x & -x (2's complement)
    return x & (~x + 1);
}
/*
 * oddBits - return word with all odd-numbered bits set to 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 2
 */
long oddBits(void) {
    // byte = 0x10101010
    // word = 0x1010101010101010
    long byte = 0xAAL;
    long word = (byte << 8) | byte;
    word = (word << 16) | word;
    word = (word << 32) | word;
    return word;
}
/*
 * replaceByte(x,n,c) - Replace byte n in x with c
 *   Bytes numbered from 0 (LSB) to 7 (MSB)
 *   Examples: replaceByte(0x12345678,1,0xab) = 0x1234ab78
 *   You can assume 0 <= n <= 7 and 0 <= c <= 255
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 10
 *   Rating: 3
 */
long replaceByte(long x, long n, long c) {
    long shift_bits = n << 3;
    long mask = 0xFFL << shift_bits;
    long shifted_c = c << shift_bits;
    return (x & ~mask) | shifted_c;
}
/*
 * conditional - same as x ? y : z
 *   Example: conditional(2,4L,5L) = 4L
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 3
 */
long conditional(long x, long y, long z) {
    // x == 0 -> mask = 0xFFFFFFFFFFFFFFFFL
    // x != 0 -> mask = 0x0000000000000000L
    long mask = ~(!x) + 1;
    return (~mask & y) | (mask & z);
}
/*
 * logicalShift - shift x to the right by n, using a logical shift
 *   Can assume that 0 <= n <= 63
 *   Examples: logicalShift(0x8765432100000000L,4L) = 0x0876543210000000L
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3
 */
long logicalShift(long x, long n) {
    long ans = x >> n;
    long shift = 64 + (~n + 1L);  // 64 - n
    long mask = (1L << shift) + (~0L);
    return conditional(n, ans & mask, x);
}
/*
 * leftBitCount - returns count of number of consective 1's in
 *     left-hand (most significant) end of word.
 *   Examples: leftBitCount(-1L) = 64L, leftBitCount(0xFFF0F0F000000000L) = 12L
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 60
 *   Rating: 4
 */
long leftBitCount(long x) {
    // Count number of leading 1's from the most significant bit
    long cnt = 0;
    long mask = ~0L;

    mask = mask << 32;
    long temp = x & mask;
    long shift = !(temp ^ mask) << 5;
    cnt += shift;
    x = x << shift;

    mask = mask << 16;
    temp = x & mask;
    shift = !(temp ^ mask) << 4;
    cnt += shift;
    x = x << shift;

    mask = mask << 8;
    temp = x & mask;
    shift = !(temp ^ mask) << 3;
    cnt += shift;
    x = x << shift;

    mask = mask << 4;
    temp = x & mask;
    shift = !(temp ^ mask) << 2;
    cnt += shift;
    x = x << shift;

    mask = mask << 2;
    temp = x & mask;
    shift = !(temp ^ mask) << 1;
    cnt += shift;
    x = x << shift;

    mask = mask << 1;
    temp = x & mask;
    shift = !(temp ^ mask);
    cnt += shift;
    x = x << shift;

    return cnt + ((x >> 63) & 1);
}
/*
 * bitParity - returns 1 if x contains an odd number of 0's
 *   Examples: bitParity(5L) = 0L, bitParity(7L) = 1L
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 22
 *   Rating: 4
 */
long bitParity(long x) {
    // use xor to count if number of 0s are odd
    
    x = x ^ logicalShift(x, 32L);
    x = x ^ logicalShift(x, 16L);
    x = x ^ logicalShift(x, 8L);
    x = x ^ logicalShift(x, 4L);
    x = x ^ logicalShift(x, 2L);
    x = x ^ logicalShift(x, 1L);

    return x & 1L;
}
/*
 * dividePower2 - Compute x/(2^n), for 0 <= n <= 62
 *  Round toward zero
 *   Examples: dividePower2(15L,1L) = 7L, dividePower2(-33L,4L) = -2L
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 */
long dividePower2(long x, long n) {
    // if (remainder && negative) x >> n + 1
    // else x >> n
    // =======> return x >> n + (remainder && negative)
    long remainder_mask = (1L << n) + ~0L;
    long signed_bit_mask = 1L << 63;
    return (x >> n) + (!!(x & remainder_mask) & !!(x & signed_bit_mask));
}
/*
 * isGreater - if x > y  then return 1, else return 0
 *   Example: isGreater(4L,5L) = 0L, isGreater(5L,4L) = 1L
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
long isGreater(long x, long y) {
    // x - y > 0 ---> return 1
    // z = x + (-y) > 0 ---> return 1
    // z == 0 ---> return 0
    // or z's signed bit is 0 ---> return 1
    // otherwise ---> return 0;

    // to handle x - y overflow
    // x is negative && y is positive -> return 0
    // x is positive && y is negative -> return 1

    long sign_mask = (1L << 63);
    long x_sign = x & sign_mask;
    long y_sign = y & sign_mask;
    long x_neg_and_y_pos = (!!x_sign) & (!y_sign);
    long x_pos_and_y_neg = (!x_sign) & (!!y_sign);
    long result = x + (~y + 1L);
    return conditional(x_neg_and_y_pos, 0, 
            conditional(x_pos_and_y_neg, 1,
                conditional(result, !(result & (1L << 63)), 0)
            ));
}
/*
 * trueFiveEighths - multiplies by 5/8 rounding toward 0,
 *  avoiding errors due to overflow
 *  Examples:
 *    trueFiveEighths(11L) = 6L
 *    trueFiveEighths(-9L) = -5L
 *    trueFiveEighths(0x3000000000000000L) = 0x1E00000000000000L (no overflow)
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 20
 *  Rating: 4
 */
long trueFiveEighths(long x) {
    // process negative x with its two's complement
    // however, the when x equals to -2^63, its two's complement is still negative. Use logical shift in second step.
    long positive_x = conditional(isGreater(x, 0L), x, ((~x) + 1L));
    long one_out_of_eight_of_x = logicalShift(positive_x, 3);
    long remainder_divide_by_eight = positive_x & 0x7L;
    long remainder_times_five = (remainder_divide_by_eight << 2) + remainder_divide_by_eight;
    long positive_answer = (remainder_times_five >> 3) + (one_out_of_eight_of_x << 2) + one_out_of_eight_of_x;
    return conditional(isGreater(x, 0L), positive_answer, ~positive_answer + 1L);
}
