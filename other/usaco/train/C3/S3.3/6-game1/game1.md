A Game
IOI'96 - Day 1
Consider the following two-player game played with a sequence of N positive integers (2 <= N <= 100) laid onto a 1 x N game board. Player 1 starts the game. The players move alternately by selecting a number from either the left or the right end of the gameboard.
That number is then deleted from the board, and its value is added to the score of the player who selected it. A player wins if his sum is greater than his opponents.

Write a program that implements the optimal strategy. The optimal strategy yields maximum points when playing against the "best possible" opponent. Your program must further implement an optimal strategy for player 2.

PROGRAM NAME: game1
INPUT FORMAT
Line 1:	N, the size of the board
Line 2-etc:	N integers in the range (1..200) that are the contents of the game board, from left to right
SAMPLE INPUT (file game1.in)
6
4 7 2 9
5 2
OUTPUT FORMAT
Two space-separated integers on a line: the score of Player 1 followed by the score of Player 2.
SAMPLE OUTPUT (file game1.out)
18 11
