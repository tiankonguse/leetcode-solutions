Humble Numbers
For a given set of K prime numbers S = {p1, p2, ..., pK}, consider the set of all numbers whose prime factors are a subset of S. This set contains, for example, p1, p1p2, p1p1, and p1p2p3 (among others). This is the set of `humble numbers' for the input set S. Note: The number 1 is explicitly declared not to be a humble number.

Your job is to find the Nth humble number for a given set S. Long integers (signed 32-bit) will be adequate for all solutions.

PROGRAM NAME: humble
INPUT FORMAT
Line 1:	Two space separated integers: K and N, 1 <= K <=100 and 1 <= N <= 100,000.
Line 2:	K space separated positive integers that compose the set S.
SAMPLE INPUT (file humble.in)
4 19
2 3 5 7
OUTPUT FORMAT
The Nth humble number from set S printed alone on a line.
SAMPLE OUTPUT (file humble.out)
27