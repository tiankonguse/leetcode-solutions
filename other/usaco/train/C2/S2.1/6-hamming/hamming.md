# Hamming Codes

Rob Kolstad

Given N, B, and D: Find a set of N codewords (1 <= N <= 64), each of length B bits (1 <= B <= 8), such that each of the codewords is at least Hamming distance of D (1 <= D <= 7) away from each of the other codewords.

The Hamming distance between a pair of codewords is the number of binary bits that differ in their binary notation. 
Consider the two codewords 0x554 and 0x234 and their differences (0x554 means the hexadecimal number with hex digits 5, 5, and 4)(a hex digit requires four bits):

```
           0x554 = 0101 0101 0100
           0x234 = 0010 0011 0100
Bit differences:   -XXX -XX- ----
```

Since five bits were different, the Hamming distance is 5.

## PROGRAM NAME: hamming

## INPUT FORMAT

N, B, D on a single line

## SAMPLE INPUT (file hamming.in)

```
16 7 3
```

## OUTPUT FORMAT

N codewords, sorted, in decimal, ten per line. 
In the case of multiple solutions, your program should output the solution which, if interpreted as a base 2^B integer, would have the least value.

## SAMPLE OUTPUT (file hamming.out)

```
0 7 25 30 42 45 51 52 75 76
82 85 97 102 120 127
```