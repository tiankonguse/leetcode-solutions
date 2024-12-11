Betsy's Tour
Don Piele
A square township has been divided up into N2 square plots (1 <= N <= 7). The Farm is located in the upper left plot and the Market is located in the lower left plot. Betsy takes her tour of the township going from Farm to Market by walking through every plot exactly once. Shown below is one possible tour for Betsy when N=3.

----------------
|    |    |    |
| F**********  |
|    |    | *  |
------------*---
|    |    | *  |
|  *****  | *  |
|  * | *  | *  |
---*---*----*---
|  * | *  | *  |
|  M | ******  |
|    |    |    |
----------------
Write a program that will count how many unique tours Betsy can take in going from Farm to Market for any value of N.
PROGRAM NAME: betsy
INPUT FORMAT
Line 1: A single integer N (1 <= N <= 7)

SAMPLE INPUT (file betsy.in)
3
OUTPUT FORMAT
A single line with a single integer, the number of unique tours.
SAMPLE OUTPUT (file betsy.out)
2