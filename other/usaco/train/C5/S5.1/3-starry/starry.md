Starry Night
IOI 98
High up in the night sky, the shining stars appear in clusters of various shapes. A cluster is a non-empty group of neighbouring stars, adjacent in horizontal, vertical or diagonal direction. A cluster cannot be a part of a larger cluster.

Clusters may be similar. Two clusters are similar if they have the same shape and number of stars, irrespective of their orientation. In general, the number of possible orientations for a cluster is eight, as Figure 1 exemplifies.

Figure 1. Eight similar clusters
Figure 1. Eight similar clusters

The night sky is represented by a sky map, which is a two-dimensional matrix of 0's and 1's. A cell contains the digit 1 if it has a star, and the digit 0 otherwise.

Given a sky map, mark all the clusters with lower case letters. Similar clusters must be marked with the same letter; non-similar clusters must be marked with different letters.

You mark a cluster with a lower case letter by replacing every 1 in the cluster by that lower case letter.

PROGRAM NAME: starry
INPUT FORMAT
The first two lines contain, respectively, the width W and the height H of a sky map. The sky map is given in the following H lines, of W characters each.

SAMPLE INPUT (file starry.in)
23
15
10001000000000010000000
01111100011111000101101
01000000010001000111111
00000000010101000101111
00000111010001000000000
00001001011111000000000
10000001000000000000000
00101000000111110010000
00001000000100010011111
00000001110101010100010
00000100110100010000000
00010001110111110000000
00100001110000000100000
00001000100001000100101
00000001110001000111000
In this case, the sky map has width 23 and height 15. Just to make it clearer, notice that this input file corresponds to the following picture of the sky.
Figure 2. Picture of the
sky
Figure 2. Picture of the sky


OUTPUT FORMAT
The output file contains the same map as the input file, except that the clusters are marked as described in Task.

There will generally be more than one way to label the clusters with letters. Your program should choose the labeling such that if the entire output file is read as a string, this string will be minimal in the lexicographical ordering.

SAMPLE OUTPUT (file starry.out)
a000a0000000000b0000000
0aaaaa000ccccc000d0dd0d
0a0000000c000c000dddddd
000000000c0b0c000d0dddd
00000eee0c000c000000000
0000e00e0ccccc000000000
b000000e000000000000000
00b0f000000ccccc00a0000
0000f000000c000c00aaaaa
0000000ddd0c0b0c0a000a0
00000b00dd0c000c0000000
000g000ddd0ccccc0000000
00g0000ddd0000000e00000
0000b000d0000f000e00e0b
0000000ddd000f000eee000
This is one possible result for the sample input above. Notice that this output file corresponds to the following picture.

Figure 3. Picture with the clusters marked


Constraints
0 <= W (width of the sky map) <= 100
0 <= H (height of the sky map) <= 100
0 <= Number of clusters <= 500
0 <= Number of non-similar clusters <= 26 (a..z)
1 <= Number of stars per cluster <= 160