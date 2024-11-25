Frame Up
Consider the following five picture frames shown on an 9 x 8 array:

........   ........   ........   ........   .CCC....
EEEEEE..   ........   ........   ..BBBB..   .C.C....
E....E..   DDDDDD..   ........   ..B..B..   .C.C....
E....E..   D....D..   ........   ..B..B..   .CCC....
E....E..   D....D..   ....AAAA   ..B..B..   ........
E....E..   D....D..   ....A..A   ..BBBB..   ........
E....E..   DDDDDD..   ....A..A   ........   ........
E....E..   ........   ....AAAA   ........   ........
EEEEEE..   ........   ........   ........   ........

   1          2           3          4          5
Now place all five picture frames on top of one another starting with 1 at the bottom and ending up with 5 on top. If any part of a frame covers another frame, it hides that part of the frame below. Viewing the stack of five frames we see the following.

           .CCC...
           ECBCBB..
           DCBCDB..
           DCCC.B..
           D.B.ABAA
           D.BBBB.A
           DDDDAD.A
           E...AAAA
           EEEEEE..
Given a picture like this, determine the order of the frames stacked from bottom to top.

Here are the rules for this challenge:

The width of the frame is always exactly 1 character and the sides are never shorter than 3 characters.
It is possible to see at least one part of each of the four sides of a frame. A corner is part of two sides.
The frames will be lettered with capital letters, and no two frames will be assigned the same letter.
PROGRAM NAME: frameup
INPUT FORMAT
Line 1:	Two space-separated integers: the height H (3 <= H <=30) and the width W (3 <= W <= 30).
Line 2..H+1:	H lines, each with a string W characters wide.
SAMPLE INPUT (file frameup.in)
9 8
.CCC....
ECBCBB..
DCBCDB..
DCCC.B..
D.B.ABAA
D.BBBB.A
DDDDAD.A
E...AAAA
EEEEEE..
OUTPUT FORMAT
Print the letters of the frames in the order they were stacked from bottom to top. If there are multiple possibilities for an ordering, list all such possibilities -- in alphabetical order -- on successive lines. There will always be at least one legal ordering.

SAMPLE OUTPUT (file frameup.out)
EDABC