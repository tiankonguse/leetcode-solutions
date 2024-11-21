Fence Loops

The fences that surround Farmer Brown's collection of pastures have gotten out of control. These fences comprise a set of straight segments with lengths in the range 1..200 feet that join together only at their endpoints (though sometimes more than two fences join together at a given endpoint).

The result is a sort of web of fences enclosing his pastures. Farmer Brown wants to organize his farm, and in order to do so, he wants to know which of the pastures has the smallest perimeter.

Farmer Brown has numbered his set of N fence segments with an integer from 1 through N. He knows the following about each fence segment:

the segment's ID number
the segment's length
the segment IDs to which it connects at one end
the segment IDs to which it connects at the other end
Every fence connects to at least one other fence. Happily, no fence connects to itself.
Given the list of fence segments that represents a complete set of surrounded pastures along with their lengths, write a program to find the smallest perimeter of any the pastures that are formed.

As an example, consider the pasture arrangement of 10 segments numbered 1..10 depicted below. The fence lengths are shown in the list at the right.

           1                 ID Len
   +---------------+          1 16
   |\             /|          2  3
  2| \7          / |          3  3
   |  \         /  |          4  8
   +---+       /   |6         5  8
   | 8  \     /10  |          6  6
  3|     \9  /     |          7  5
   |      \ /      |          8  4
   +-------+-------+          9  5
       4       5             10 10
[not to scale]
The pasture with the smallest perimeter is the one that is enclosed by fence segments IDs 2, 7, and 8 (respective lengths: 3, 5, and 4; total perimeter 12).

PROGRAM NAME: fence6
INPUT FORMAT
Line 1:	N (1 <= N <= 100)
Line 2..3*N+1:	
N sets of three line records:

The first line of each record contains four integers: s, the segment ID (1 <= s <= N); Ls, the length of the segment (1 <= Ls <= 255); N1s (1 <= N1s <= 8) the count of items on the subsequent line; and N2s the count of items on the line after that (1 <= N2s <= 8).
The second line of the record contains N1 integers, each representing the ID of a connected line segment on one end of the fence.
The third line of the record contains N2 integers, each representing the ID of a connected line segment on the other end of the fence.
SAMPLE INPUT (file fence6.in)
10
1 16 2 2
2 7
10 6
2 3 2 2
1 7
8 3
3 3 2 1
8 2
4
4 8 1 3
3
9 10 5
5 8 3 1
9 10 4
6
6 6 1 2
5
1 10
7 5 2 2
1 2
8 9
8 4 2 2
2 3
7 9
9 5 2 3
7 8
4 5 10
10 10 2 3
1 6
4 9 5
OUTPUT FORMAT
The output file should contain a single line with a single integer that represents the shortest surrounded perimeter.
SAMPLE OUTPUT (file fence6.out)
12