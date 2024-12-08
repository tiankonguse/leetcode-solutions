Shaping Regions
N opaque rectangles (1 <= N <= 1000) of various colors are placed on a white sheet of paper whose size is A wide by B long. The rectangles are put with their sides parallel to the sheet's borders.
All rectangles fall within the borders of the sheet so that different figures of different colors will be seen.

The coordinate system has its origin (0,0) at the sheet's lower left corner with axes parallel to the sheet's borders.

PROGRAM NAME: rect1
INPUT FORMAT
The order of the input lines dictates the order of laying down the rectangles. The first input line is a rectangle "on the bottom".
Line 1:	A, B, and N, space separated (1 <= A,B <= 10,000)
Lines 2-N+1:	Five integers: llx, lly, urx, ury, color: the lower left coordinates and upper right coordinates of the rectangle whose color is `color' (1 <= color <= 2500) to be placed on the white sheet.
The color 1 is the same color of white as the sheet upon which the rectangles are placed.

SAMPLE INPUT (file rect1.in)
20 20 3
2 2 18 18 2
0 8 19 19 3
8 0 10 19 4
INPUT EXPLANATION
Note that the rectangle delineated by 0,0 and 2,2 is two units wide and two high. Here's a schematic diagram of the input:
11111111111111111111
33333333443333333331
33333333443333333331
33333333443333333331
33333333443333333331
33333333443333333331
33333333443333333331
33333333443333333331
33333333443333333331
33333333443333333331
33333333443333333331
33333333443333333331
11222222442222222211
11222222442222222211
11222222442222222211
11222222442222222211
11222222442222222211
11222222442222222211
11111111441111111111
11111111441111111111
The '4's at 8,0 to 10,19 are only two wide, not three (i.e., the grid contains a 4 at 8,0 and a 4 at 8,1 but NOT a 4 at 8,2 since this diagram can't capture what would be shown on graph paper).
OUTPUT FORMAT
The output file should contain a list of all the colors that can be seen along with the total area of each color that can be seen (even if the regions of color are disjoint), ordered by increasing color. Do not display colors with no area.
SAMPLE OUTPUT (file rect1.out)
1 91
2 84
3 187
4 38
HINTS (use them carefully!)