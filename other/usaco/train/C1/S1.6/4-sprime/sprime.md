## Superprime Rib

Butchering Farmer John's cows always yields the best prime rib. 
You can tell prime ribs by looking at the digits lovingly stamped across them, one by one, by FJ and the USDA. 
Farmer John ensures that a purchaser of his prime ribs gets really prime ribs because when sliced from the right, the numbers on the ribs continue to stay prime right down to the last rib, e.g.:

     7  3  3  1

The set of ribs denoted by 7331 is prime; 
the three ribs 733 are prime; 
the two ribs 73 are prime, and, of course, the last rib, 7, is prime. 
The number 7331 is called a superprime of length 4.

Write a program that accepts a number N 1 <=N<=8 of ribs and prints all the superprimes of that length.

The number 1 (by itself) is not a prime number.

## PROGRAM NAME: sprime

## INPUT FORMAT

A single line with the number N.

## SAMPLE INPUT (file sprime.in)

```
4
```

## OUTPUT FORMAT

The superprime ribs of length N, printed in ascending order one per line.

## SAMPLE OUTPUT (file sprime.out)

```
2333
2339
2393
2399
2939
3119
3137
3733
3739
3793
3797
5939
7193
7331
7333
7393
```
