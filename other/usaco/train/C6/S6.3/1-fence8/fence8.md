Fence Rails
Burch, Kolstad, and Schrijvers
Farmer John is trying to erect a fence around part of his field. He has decided on the shape of the fence and has even already installed the posts, but he's having a problem with the rails.
The local lumber store has dropped off boards of varying lengths; Farmer John must create as many of the rails he needs from the supplied boards.

Of course, Farmer John can cut the boards, so a 9 foot board can be cut into a 5 foot rail and a 4 foot rail (or three 3 foot rails, etc.). Farmer John has an `ideal saw', so ignore the `kerf' (distance lost during sawing); presume that perfect cuts can be made.

The lengths required for the rails might or might not include duplicates (e.g., a three foot rail and also another three foot rail might both be required). There is no need to manufacture more rails (or more of any kind of rail) than called for the list of required rails.

PROGRAM NAME: fence8
INPUT FORMAT
Line 1:	N (1 <= N <= 50), the number of boards
Line 2..N+1:	N lines, each containing a single integer that represents the length of one supplied board
Line N+2:	R (1 <= R <= 1023), the number of rails
Line N+3..N+R+1:	R lines, each containing a single integer (1 <= ri <= 128) that represents the length of a single required fence rail
SAMPLE INPUT (file fence8.in)
4
30
40
50
25
10
15
16
17
18
19
20
21
25
24
30
OUTPUT FORMAT
A single integer on a line that is the total number of fence rails that can be cut from the supplied boards. Of course, it might not be possible to cut all the possible rails from the given boards.
SAMPLE OUTPUT (file fence8.out)
7
HINTS (use them carefully!)