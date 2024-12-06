A Rectangular Barn
Mircea Pasoi -- 2003
Ever the capitalist, Farmer John wants to extend his milking business by purchasing more cows. He needs space to build a new barn for the cows.

FJ purchased a rectangular field with R (1 ≤ R ≤ 3,000) rows numbered 1..R and C (1 ≤ C ≤ 3,000) columns numbered 1..C. Unfortunately, he realized too late that some 1x1 areas in the field are damaged, so he cannot build the barn on the entire RxC field.

FJ has counted P (0 ≤ P ≤ 30,000) damaged 1x1 pieces and has asked for your help to find the biggest rectangular barn (i.e., the largest area) that he can build on his land without building on the damaged pieces.

PROGRAM NAME: rectbarn
INPUT FORMAT
Line 1: Three space-separated integers: R, C, and P.
Lines 2..P+1: Each line contains two space-separated integers, r and c, that give the row and column numbers of a damaged area of the field
SAMPLE INPUT (file rectbarn.in)
3 4 2
1 3
2 1
OUTPUT FORMAT
Line 1: The largest possible area of the new barn
SAMPLE OUTPUT (file rectbarn.out)
6
OUTPUT DETAILS
  1 2 3 4
 +-+-+-+-+
1| | |X| |
 +-+-+-+-+
2|X|#|#|#|
 +-+-+-+-+
3| |#|#|#|
 +-+-+-+-+
Pieces marked with 'X' are damaged and pieces marked with '#' are part of the new barn.