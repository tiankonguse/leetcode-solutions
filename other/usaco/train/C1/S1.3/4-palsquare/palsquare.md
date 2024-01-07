# Palindromic Squares
Rob Kolstad


Palindromes are numbers that read the same forwards as backwards. The number 12321 is a typical palindrome.

Given a number base B (2 <= B <= 20 base 10), print all the integers N (1 <= N <= 300 base 10) such that the square of N is palindromic when expressed in base B; also print the value of that palindromic square. Use the letters 'A', 'B', and so on to represent the digits 10, 11, and so on.

Print both the number and its square in base B.

## PROGRAM NAME: palsquare


## INPUT FORMAT

A single line with B, the base (specified in base 10).


## SAMPLE INPUT (file palsquare.in)

```
10
```

## OUTPUT FORMAT


Lines with two integers represented in base B. The first integer is the number whose square is palindromic; the second integer is the square itself. NOTE WELL THAT BOTH INTEGERS ARE IN BASE B!


## SAMPLE OUTPUT (file palsquare.out)


```
1 1
2 4
3 9
11 121
22 484
26 676
101 10201
111 12321
121 14641
202 40804
212 44944
264 69696
```