The Primes
IOI'94
In the square below, each row, each column and the two diagonals can be read as a five digit prime number. The rows are read from left to right. The columns are read from top to bottom. Both diagonals are read from left to right.

+---+---+---+---+---+
| 1 | 1 | 3 | 5 | 1 |
+---+---+---+---+---+
| 3 | 3 | 2 | 0 | 3 |
+---+---+---+---+---+
| 3 | 0 | 3 | 2 | 3 |
+---+---+---+---+---+
| 1 | 4 | 0 | 3 | 3 |
+---+---+---+---+---+
| 3 | 3 | 3 | 1 | 1 |
+---+---+---+---+---+ 
The prime numbers' digits must sum to the same number.
The digit in the top left-hand corner of the square is pre-determined (1 in the example).
A prime number may be used more than once in the same square.
If there are several solutions, all must be presented (sorted in numerical order as if the 25 digits were all one long number).
A five digit prime number cannot begin with a zero (e.g., 00003 is NOT a five digit prime number).
PROGRAM NAME: prime3
INPUT FORMAT
A single line with two space-separated integers: the sum of the digits and the digit in the upper left hand corner of the square.

SAMPLE INPUT (file prime3.in)
11 1
OUTPUT FORMAT
Five lines of five characters each for each solution found, where each line in turn consists of a five digit prime number. Print a blank line between solutions. If there are no prime squares for the input data, output a single line containing "NONE".

SAMPLE OUTPUT (file prime3.out)
The above example has 3 solutions.

11351
14033
30323
53201
13313

11351
33203
30323
14033
33311

13313
13043
32303
50231
13331