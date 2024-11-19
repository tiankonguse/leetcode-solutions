Raucous Rockers
You just inherited the rights to N (1 <= N <= 20) previously unreleased songs recorded by the popular group Raucous Rockers. You plan to release a set of M (1 <= M <= 20) compact disks with a selection of these songs.
Each disk can hold a maximum of T (1 <= T <= 20) minutes of music, and a song can not overlap from one disk to another.

Since you are a classical music fan and have no way to judge the artistic merits of these songs, you decide on the following criteria for making the selection:

The songs on the set of disks must appear in the order of the dates that they were written.
The total number of songs included will be maximized.
PROGRAM NAME: rockers
INPUT FORMAT
Line 1:	Three integers: N, T, and M.
Line 2:	N integers that are the lengths of the songs ordered by the date they were written.
SAMPLE INPUT (file rockers.in)
4 5 2
4 3 4 2
OUTPUT FORMAT
A single line with an integer that is the number of songs that will fit on M disks.
SAMPLE OUTPUT (file rockers.out)
3