Checker Challenge
Examine the 6x6 checkerboard below and note that the six checkers are arranged on the board so that one and only one is placed in each row and each column, and there is never more than one in any diagonal. (Diagonals run from southeast to northwest and southwest to northeast and include all diagonals, not just the major two.)


          Column
    1   2   3   4   5   6
  -------------------------
1 |   | O |   |   |   |   |
  -------------------------
2 |   |   |   | O |   |   |
  -------------------------
3 |   |   |   |   |   | O |
  -------------------------
4 | O |   |   |   |   |   |
  -------------------------
5 |   |   | O |   |   |   |
  -------------------------
6 |   |   |   |   | O |   |
  -------------------------
The solution shown above is described by the sequence 2 4 6 1 3 5, which gives the column positions of the checkers for each row from 1 to 6:

ROW	1	2	3	4	5	6
COLUMN	2	4	6	1	3	5
This is one solution to the checker challenge. Write a program that finds all unique solution sequences to the Checker Challenge (with ever growing values of N). Print the solutions using the column notation described above. Print the first three solutions in numerical order, as if the checker positions form the digits of a large number, and then a line with the total number of solutions.

Special note: the larger values of N require your program to be especially efficient. Do not precalculate the value and print it (or even find a formula for it); that's cheating. Work on your program until it can solve the problem properly. If you insist on cheating, your login to the USACO training pages will be removed and you will be disqualified from all USACO competitions. YOU HAVE BEEN WARNED.

TIME LIMIT: 1 CPU second
PROGRAM NAME: checker
INPUT FORMAT
A single line that contains a single integer N (6 <= N <= 13) that is the dimension of the N x N checkerboard.
SAMPLE INPUT (file checker.in)
6
OUTPUT FORMAT
The first three lines show the first three solutions found, presented as N numbers with a single space between them. The fourth line shows the total number of solutions found.
SAMPLE OUTPUT (file checker.out)
2 4 6 1 3 5
3 6 2 5 1 4
4 1 5 2 6 3
4