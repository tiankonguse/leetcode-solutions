Electric Fence
Don Piele
In this problem, `lattice points' in the plane are points with integer coordinates.

In order to contain his cows, Farmer John constructs a triangular electric fence by stringing a "hot" wire from the origin (0,0) to a lattice point [n,m] (0<=;n<32,000, 0<m<32,000), then to a lattice point on the positive x axis [p,0] (0<p<32,000), and then back to the origin (0,0).

A cow can be placed at each lattice point within the fence without touching the fence (very thin cows). Cows can not be placed on lattice points that the fence touches. How many cows can a given fence hold?

PROGRAM NAME: fence9
INPUT FORMAT
The single input line contains three space-separated integers that denote n, m, and p.

SAMPLE INPUT (file fence9.in)
7 5 10
OUTPUT FORMAT
A single line with a single integer that represents the number of cows the specified fence can hold.

SAMPLE OUTPUT (file fence9.out)
20
