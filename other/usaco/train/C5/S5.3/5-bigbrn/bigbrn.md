Big Barn
A Special Treat
Farmer John wants to place a big square barn on his square farm. He hates to cut down trees on his farm and wants to find a location for his barn that enables him to build it only on land that is already clear of trees. For our purposes, his land is divided into N x N parcels. The input contains a list of parcels that contain trees. Your job is to determine and report the largest possible square barn that can be placed on his land without having to clear away trees. The barn sides must be parallel to the horizontal or vertical axis.

EXAMPLE
Consider the following grid of Farmer John's land where `.' represents a parcel with no trees and `#' represents a parcel with trees:


          1 2 3 4 5 6 7 8
        1 . . . . . . . .
        2 . # . . . # . .
        3 . . . . . . . .
        4 . . . . . . . .
        5 . . . . . . . .
        6 . . # . . . . .
        7 . . . . . . . .
        8 . . . . . . . .
The largest barn is 5 x 5 and can be placed in either of two locations in the lower right part of the grid.

PROGRAM NAME: bigbrn
INPUT FORMAT
Line 1:	Two integers: N (1 <= N <= 1000), the number of parcels on a side, and T (1 <= T <= 10,000) the number of parcels with trees
Lines 2..T+1:	Two integers (1 <= each integer <= N), the row and column of a tree parcel
SAMPLE INPUT (file bigbrn.in)
8 3
2 2
2 6
6 3
OUTPUT FORMAT
The output file should consist of exactly one line, the maximum side length of John's barn.

SAMPLE OUTPUT (file bigbrn.out)
5