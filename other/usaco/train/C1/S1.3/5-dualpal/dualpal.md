# Dual Palindromes

Mario Cruz (Colombia) & Hugo Rickeboer (Argentina)


A number that reads the same from right to left as when read from left to right is called a palindrome. The number 12321 is a palindrome; the number 77778 is not. Of course, palindromes have neither leading nor trailing zeroes, so 0220 is not a palindrome.

The number 21 (base 10) is not palindrome in base 10, but the number 21 (base 10) is, in fact, a palindrome in base 2 (10101).

Write a program that reads two numbers (expressed in base 10):

N (1 <= N <= 15)
S (0 < S < 10000)

and then finds and prints (in base 10) the first N numbers strictly greater than S that are palindromic when written in two or more number bases (2 <= base <= 10).
Solutions to this problem do not require manipulating integers larger than the standard 32 bits.

## PROGRAM NAME: dualpal


## INPUT FORMAT

A single line with space separated integers N and S.

## SAMPLE INPUT (file dualpal.in)

```
3 25
```


## OUTPUT FORMAT


N lines, each with a base 10 number that is palindromic when expressed in at least two of the bases 2..10. The numbers should be listed in order from smallest to largest.


## SAMPLE OUTPUT (file dualpal.out)


```
26
27
28
```


## ANALYSIS

Dual palindromes are actually very common, a fact we can test by writing a program such as this one.

Since they are very common, we can just use a brute force search to test all numbers bigger than s until we find enough dual palindromes.

How do we know they are common enough? Write the brute force program (which is very simple and thus not much effort) and check.

This reasoning is a little circular, but if we had been wrong and ended up needing a more clever and more efficient algorithm, we would have this brute force version to test against.