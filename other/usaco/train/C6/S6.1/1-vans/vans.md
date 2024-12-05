Postal Vans
ACM South Pacific Region -- 2003
Tiring of their idyllic fields, the cows have moved to a new suburb. The suburb is a rectangular grid of streets with a post office at its Northwest corner. It has four avenues running East-West and N (1 <= N <= 1000) streets running North-South.

For example, the following diagram shows such a suburb with N=5 streets, with the avenues depicted as horizontal lines, and the post office as a dark blob at the top-left corner:


Each day the postal van leaves the post office, drives around the suburb and returns to the post office, passing exactly once through every intersection (including those on borders or corners). The executives from the post company want to know how many distinct routes can be established for the postal van (of course, the route direction is significant in this count).

For example, the following diagrams show two such routes for the above suburb:


As another example, the following diagrams show all the four possible routes for a suburb with N=3 streets:


Write a program that will determine the number of such distinct routes given the number of streets.

PROGRAM NAME: vans
INPUT FORMAT
Line 1: A single integer, N
SAMPLE INPUT (file vans.in)
4

OUTPUT FORMAT
Line 1: A single integer that tells how many possible distinct routes corresponding to the number of streets given in the input.
SAMPLE OUTPUT (file vans.out)
12