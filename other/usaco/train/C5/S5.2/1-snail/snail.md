Snail Trails
All Ireland Contest
Sally Snail likes to stroll on a N x N square grid (1 <n <= 120). She always starts in the upper left corner of the grid. The grid has empty squares (denoted below by `.') and a number (B) of barriers (denoted below by `#'). Here is a depiction of a grid including a demonstration of the grid labelling algorithm:


          A B C D E F G H
        1 S . . . . . # .
        2 . . . . # . . .
        3 . . . . . . . .
        4 . . . . . . . .
        5 . . . . . # . .
        6 # . . . . . . .
        7 . . . . . . . .
        8 . . . . . . . .

Sally travels vertically (up or down) or horizontally (left or right). Sally can travel either down or right from her starting location, which is always A1.
Sally travels as long as she can in her chosen direction. She stops and turns 90 degrees whenever she encounters the edge of the board or one of the barriers. She can not leave the grid or enter a space with a barrier. Additionally, Sally can not re-cross any square she has already traversed. She stops her traversal altogether any time she can no longer make a move.

Here is one sample traversal on the sample grid above:

          A B C D E F G H
        1 S---------+ # .
        2 . . . . # | . .
        3 . . . . . | . .
        4 . . . . . +---+
        5 . . . . . # . |
        6 # . . . . . . |
        7 +-----------+ |
        8 +-------------+
Sally traversed right, down, right, down, left, up, and right. She could not continue since she encountered a square already visited. Things might have gone differently if she had chosen to turn back toward our left when she encountered the barrier at F5.

Your task is to determine and print the largest possible number of squares that Sally can visit if she chooses her turns wisely. Be sure to count square A1 as one of the visited squares.

PROGRAM NAME: snail
INPUT FORMAT
The first line of the input has N, the dimension of the square, and B, the number of barriers (1 <= B <= 200). The subsequent B lines contain the locations of the barriers. The sample input file below describes the sample grid above. The sample output file below is supposed to describe the traversal shown above. Note that when N > 26 then the input file can not specify barriers to the right of column Z.

SAMPLE INPUT (file snail.in)
8 4
E2
A6
G1
F5
OUTPUT FORMAT
The output file should consist of exactly one line, the largest possible number of squares that Sally can visit.

SAMPLE OUTPUT (file snail.out)
33
Using this traversal:
          A B C D E F G H
        1 S . . . . . # .
        2 | . . . # . . .
        3 | . . . +-----+
        4 | . . . | . . |
        5 +-------+ # . |
        6 # . . . . . . |
        7 +------------ |
        8 +-------------+