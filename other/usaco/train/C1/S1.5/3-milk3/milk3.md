## Mother's Milk

Farmer John has three milking buckets of capacity A, B, and C liters. 
Each of the numbers A, B, and C is an integer from 1 through 20, inclusive. 
Initially, buckets A and B are empty while bucket C is full of milk. 
Sometimes, FJ pours milk from one bucket to another until the second bucket is filled or the first bucket is empty. 
Once begun, a pour must be completed, of course. 
Being thrifty, no milk may be tossed out.


Write a program to help FJ determine what amounts of milk he can leave in bucket C when he begins with three buckets as above, pours milk among the buckets for a while, and then notes that bucket A is empty.

## PROGRAM NAME: milk3


## INPUT FORMAT

A single line with the three integers A, B, and C.

## SAMPLE INPUT (file milk3.in)

```
8 9 10
```


## OUTPUT FORMAT

A single line with a sorted list of all the possible amounts of milk that can be in bucket C when bucket A is empty.

## SAMPLE OUTPUT (file milk3.out)


```
1 2 8 9 10
```


## SAMPLE INPUT (file milk3.in)


```
2 5 10
```

SAMPLE OUTPUT (file milk3.out)

```
5 6 7 8 9 10
```

Here are the test data inputs:

------- test 1 [length 7 bytes] ----
2 5 10
------- test 2 [length 9 bytes] ----
20 20 20
------- test 3 [length 8 bytes] ----
5 11 15
------- test 4 [length 8 bytes] ----
2 12 20
------- test 5 [length 8 bytes] ----
19 4 11
------- test 6 [length 8 bytes] ----
5 11 13
------- test 7 [length 8 bytes] ----
3 20 20
------- test 8 [length 8 bytes] ----
7 16 20
------- test 9 [length 8 bytes] ----
20 10 9
------- test 10 [length 8 bytes] ----
7 12 18