Twofive
IOI 2001
In order to teach her young calves the order of the letters in the alphabet, Bessie has come up with a game to play with them. The calves are given a 5 x 5 grid on which they can put the letters 'A'-'Y', but the one rule is that all the letters going across the columns and down the rows must be in the order they appear in the alphabet.

There are a huge number of possible grids, so Bessie decides that they will be named by the string of letters that is given by reading across each row, going down the rows. For example, the grid:

 
     A B C D E
     F G H I J
     K L M N O
     P Q R S T 
     U V W X Y

would have the name ABCDEFGHIJKLMNOPQRSTUVWXY, which is coincidentally the first possible grid when the entire set of grids is ordered alphabetically. The second grid that meets this requirement is ABCDEFGHIJKLMNOPQRSUTVWXY, which is formed by switching the 'T' and 'U' in the above grid.
Help the calves gain bragging rights. Given a number, M, find which string is Mth in the list of all possible grids when they are sorted alphabetically, and, given a string of letters, find out what number the corresponding grid is in the list of all possible grids.

PROGRAM NAME: twofive
INPUT FORMAT
The first input line contains one of two letters, either an 'N' or a 'W'.

If the first input line contains an 'N', the second line will contain an integer, M, that corresponds to the number of a valid grid. If the first line contains a 'W', the second line will contain a string of 25 letters, which represents a valid grid.

OUTPUT FORMAT
If the input contained the number of a valid grid (first line 'N'), the output should contain a string of 25 letters on a line, which corresponds to the Mth grid in the sorted list of all possible grids.

If the input contained a string of letters indicating a grid (first line 'W'), the output should contain a single integer on a line, which corresponds to the number of the given grid in the list of all possible grids.

SAMPLE INPUT #1 (file twofive.in)
N
2
SAMPLE OUTPUT #1 (file twofive.out)
ABCDEFGHIJKLMNOPQRSUTVWXY
SAMPLE INPUT #2 (file twofive.in)
W
ABCDEFGHIJKLMNOPQRSUTVWXY
SAMPLE OUTPUT #2 (file twofive.out)
2