The Tamworth Two
BIO '98 - Richard Forster
A pair of cows is loose somewhere in the forest. Farmer John is lending his expertise to their capture. Your task is to model their behavior.

The chase takes place on a 10 by 10 planar grid. Squares can be empty or they can contain:

an obstacle,
the cows (who always travel together), or
Farmer John.
The cows and Farmer John can occupy the same square (when they `meet') but neither the cows nor Farmer John can share a square with an obstacle.
Each square is
represented
as follows:

. Empty square
* Obstacle
C Cows
F Farmer
Here is a sample grid:
*...*.....
......*...
...*...*..
..........
...*.F....
*.....*...
...*......
..C......*
...*.*....
.*.*......

The cows wander around the grid in a fixed way. Each minute, they either move forward or rotate. Normally, they move one square in the direction they are facing. If there is an obstacle in the way or they would leave the board by walking `forward', then they spend the entire minute rotating 90 degrees clockwise.

Farmer John, wise in the ways of cows, moves in exactly the same way.

The farmer and the cows can be considered to move simultaneously during each minute. If the farmer and the cows pass each other while moving, they are not considered to have met. The chase ends when Farmer John and the cows occupy the same square at the end of a minute.

Read a ten-line grid that represents the initial state of the cows, Farmer John, and obstacles. Each of the ten lines contains exactly ten characters using the coding above. There is guaranteed to be only one farmer and one pair of cows. The cows and Farmer John will not initially be on the same square.

Calculate the number of minutes until the cows and Farmer John meet. Assume both the cows and farmer begin the simulation facing in the `north' direction. Print 0 if they will never meet.

PROGRAM NAME: ttwo
INPUT FORMAT
Lines 1-10:	Ten lines of ten characters each, as explained above
SAMPLE INPUT (file ttwo.in)
*...*.....
......*...
...*...*..
..........
...*.F....
*.....*...
...*......
..C......*
...*.*....
.*.*......
OUTPUT FORMAT
A single line with the integer number of minutes until Farmer John and the cows meet. Print 0 if they will never meet.
SAMPLE OUTPUT (file ttwo.out)
49
