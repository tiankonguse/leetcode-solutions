Home on the Range
Farmer John grazes his cows on a large, square field N (2 <= N <= 250) miles on a side (because, for some reason, his cows will only graze on precisely square land segments). Regrettably, the cows have ravaged some of the land (always in 1 mile square increments).
FJ needs to map the remaining squares (at least 2x2 on a side) on which his cows can graze (in these larger squares, no 1x1 mile segments are ravaged).

Your task is to count up all the various square grazing areas within the supplied dataset and report the number of square grazing areas (of sizes >= 2x2) remaining. Of course, grazing areas may overlap for purposes of this report.

PROGRAM NAME: range
INPUT FORMAT
Line 1:	N, the number of miles on each side of the field.
Line 2..N+1:	N characters with no spaces. 0 represents "ravaged for that block; 1 represents "ready to eat".
SAMPLE INPUT (file range.in)
6
101111
001111
111111
001111
101101
111001
OUTPUT FORMAT
Potentially several lines with the size of the square and the number of such squares that exist. Order them in ascending order from smallest to largest size.

SAMPLE OUTPUT (file range.out)
2 10
3 4
4 1  
