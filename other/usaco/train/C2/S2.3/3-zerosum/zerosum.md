Zero Sum
Consider the sequence of digits from 1 through N (where N=9) in increasing order: 1 2 3 ... N.

Now insert either a `+' for addition or a `-' for subtraction or a ` ' [blank] to run the digits together between each pair of digits (not in front of the first digit). Calculate the result that of the expression and see if you get zero.

Write a program that will find all sequences of length N that produce a zero sum.

PROGRAM NAME: zerosum
INPUT FORMAT
A single line with the integer N (3 <= N <= 9).
SAMPLE INPUT (file zerosum.in)
7
OUTPUT FORMAT
In ASCII order, show each sequence that can create 0 sum with a `+', `-', or ` ' between each pair of numbers.
SAMPLE OUTPUT (file zerosum.out)
1+2-3+4-5-6+7
1+2-3-4+5+6-7
1-2 3+4+5+6+7
1-2 3-4 5+6 7
1-2+3+4-5+6-7
1-2-3-4-5+6+7