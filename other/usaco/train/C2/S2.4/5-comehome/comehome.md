Bessie Come Home
Kolstad & Burch
It's dinner time, and the cows are out in their separate pastures. Farmer John rings the bell so they will start walking to the barn. Your job is to figure out which one cow gets to the barn first (the supplied test data will always have exactly one fastest cow).

Between milkings, each cow is located in her own pasture, though some pastures have no cows in them. Each pasture is connected by a path to one or more other pastures (potentially including itself).
Sometimes, two (potentially self-same) pastures are connected by more than one path. One or more of the pastures has a path to the barn. Thus, all cows have a path to the barn and they always know the shortest path.
Of course, cows can go either direction on a path and they all walk at the same speed.

The pastures are labeled `a'..`z' and `A'..`Y'. One cow is in each pasture labeled with a capital letter. No cow is in a pasture labeled with a lower case letter. The barn's label is `Z'; no cows are in the barn, though.

PROGRAM NAME: comehome
INPUT FORMAT
Line 1:	Integer P (1 <= P <= 10000) the number of paths that interconnect the pastures (and the barn)
Line 2..P+1:	Space separated, two letters and an integer: the names of the interconnected pastures/barn and the distance between them (1 <= distance <= 1000)
SAMPLE INPUT (file comehome.in)
5
A d 6
B d 3
C e 9
d Z 8
e Z 3
OUTPUT FORMAT
A single line containing two items: the capital letter name of the pasture of the cow that arrives first back at the barn, the length of the path followed by that cow.
SAMPLE OUTPUT (file comehome.out)
B 11