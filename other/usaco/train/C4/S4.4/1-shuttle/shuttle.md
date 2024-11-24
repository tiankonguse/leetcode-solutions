Shuttle Puzzle
Traditional
The Shuttle Puzzle of size 3 consists of 3 white marbles, 3 black marbles, and a strip of wood with 7 holes. The marbles of the same color are placed in the holes at the opposite ends of the strip, leaving the center hole empty.

INITIAL STATE: WWW_BBB 
GOAL STATE: BBB_WWW
To solve the shuttle puzzle, use only two types of moves. Move 1 marble 1 space (into the empty hole) or jump 1 marble over 1 marble of the opposite color (into the empty hole). You may not back up, and you may not jump over 2 marbles.

A Shuttle Puzzle of size N consists of N white marbles and N black marbles and 2N+1 holes.

Here's one solution for the problem of size 3 showing the initial, intermediate, and end states:

WWW BBB
WW WBBB
WWBW BB
WWBWB B
WWB BWB
W BWBWB
 WBWBWB
BW WBWB
BWBW WB
BWBWBW 
BWBWB W
BWB BWW
B BWBWW
BB WBWW
BBBW WW
BBB WWW
Write a program that will solve the SHUTTLE PUZZLE for any size N (1 <= N <= 12) in the minimum number of moves and display the successive moves, 20 per line.

PROGRAM NAME: shuttle
INPUT FORMAT
A single line with the integer N.
SAMPLE INPUT (file shuttle.in)
3
OUTPUT FORMAT
The list of moves expressed as space-separated integers, 20 per line (except possibly the last line). Number the marbles/holes from the left, starting with one.

Output the solution that would appear first among the set of minimal solutions sorted numerically (first by the first number, using the second number for ties, and so on).

SAMPLE OUTPUT (file shuttle.out)
3 5 6 4 2 1 3 5 7 6 4 2 3 5 4