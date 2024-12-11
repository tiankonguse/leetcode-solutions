The Clocks
IOI'94 - Day 2
Consider nine clocks arranged in a 3x3 array thusly:
|-------|    |-------|    |-------|    
|       |    |       |    |   |   |    
|---O   |    |---O   |    |   O   |          
|       |    |       |    |       |           
|-------|    |-------|    |-------|    
    A            B            C

|-------|    |-------|    |-------|
|       |    |       |    |       |
|   O   |    |   O   |    |   O   |
|   |   |    |   |   |    |   |   |
|-------|    |-------|    |-------|
    D            E            F

|-------|    |-------|    |-------|
|       |    |       |    |       |
|   O   |    |   O---|    |   O   |
|   |   |    |       |    |   |   |
|-------|    |-------|    |-------|
    G            H            I
The goal is to find a minimal sequence of moves to return all the dials to 12 o'clock. Nine different ways to turn the dials on the clocks are supplied via a table below; each way is called a move.
Select for each move a number 1 through 9 which will cause the dials of the affected clocks (see next table) to be turned 90 degrees clockwise.
Move	Affected clocks
1	ABDE
2	ABC
3	BCEF
4	ADG
5	BDEFH
6	CFI
7	DEGH
8	GHI
9	EFHI

Example
Each number represents a time according to following table:
9 9 12       9 12 12       9 12 12        12 12 12      12 12 12 
6 6 6  5 ->  9  9  9  8->  9  9  9  4 ->  12  9  9  9-> 12 12 12 
6 3 6        6  6  6       9  9  9        12  9  9      12 12 12 
[But this might or might not be the `correct' answer; see below.]

PROGRAM NAME: clocks
INPUT FORMAT
Lines 1-3:	Three lines of three space-separated numbers; each number represents the start time of one clock, 3, 6, 9, or 12. The ordering of the numbers corresponds to the first example above.
SAMPLE INPUT (file clocks.in)
9 9 12
6 6 6
6 3 6
OUTPUT FORMAT
A single line that contains a space separated list of the shortest sequence of moves (designated by numbers) which returns all the clocks to 12:00.
If there is more than one solution, print the one which gives the lowest number when the moves are concatenated (e.g., 5 2 4 6 < 9 3 1 1).

SAMPLE OUTPUT (file clocks.out)
4 5 8 9