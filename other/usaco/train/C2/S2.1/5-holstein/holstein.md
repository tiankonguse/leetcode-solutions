## Healthy Holsteins

Burch & Kolstad
Farmer John prides himself on having the healthiest dairy cows in the world. He knows the vitamin content for one scoop of each feed type and the minimum daily vitamin requirement for his cows.
Help Farmer John feed the cows so they stay healthy while minimizing the number of scoops that a cow is fed.

Given the daily requirements of each kind of vitamin that a cow needs, identify the smallest combination of scoops of feed a cow can be fed in order to meet at least the minimum vitamin requirements.

Vitamins are measured in integer units. Cows can be fed at most one scoop of any feed type. It is guaranteed that a solution exists for all contest input data.

## PROGRAM NAME: holstein

## INPUT FORMAT

Line 1:	integer V (1 <= V <= 25), the number of types of vitamins
Line 2:	V integers (1 <= each one <= 1000), the minimum requirement for each of the V vitamins that a cow requires each day
Line 3:	integer G (1 <= G <= 15), the number of types of feeds available
Lines 4..G+3:	V integers (0 <= each one <= 1000), the amount of each vitamin that one scoop of this feed contains. The first line of these G lines describes feed #1; the second line describes feed #2; and so on.

## SAMPLE INPUT (file holstein.in)

```
4
100 200 300 400
3
50   50  50  50
200 300 200 300
900 150 389 399
```


## OUTPUT FORMAT

The output is a single line of output that contains:

the minimum number of scoops a cow must eat, followed by:
a SORTED list (from smallest to largest) of the feed types the cow is given
If more than one set of feedtypes yield a minimum of scoops, choose the set with the smallest feedtype numbers.


## SAMPLE OUTPUT (file holstein.out)

```
2 1 3
```