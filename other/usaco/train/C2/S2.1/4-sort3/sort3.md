## Sorting a Three-Valued Sequence
IOI'96 - Day 2

Sorting is one of the most frequently performed computational tasks. 
Consider the special sorting problem in which the records to be sorted have at most three different key values. 
This happens for instance when we sort medalists of a competition according to medal value, that is, gold medalists come first, followed by silver, and bronze medalists come last.

In this task the possible key values are the integers 1, 2 and 3. 
The required sorting order is non-decreasing. 
However, sorting has to be accomplished by a sequence of exchange operations. 
An exchange operation, defined by two position numbers p and q, exchanges the elements in positions p and q.

You are given a sequence of key values. 
Write a program that computes the minimal number of exchange operations that are necessary to make the sequence sorted.

## PROGRAM NAME: sort3

## INPUT FORMAT

Line 1:	N (1 <= N <= 1000), the number of records to be sorted
Lines 2-N+1:	A single integer from the set {1, 2, 3}

## SAMPLE INPUT (file sort3.in)

```
9
2
2
1
3
3
3
2
3
1
```

## OUTPUT FORMAT

A single line containing the number of exchanges required

## SAMPLE OUTPUT (file sort3.out)

```
4
```

## EXPLANATION

Here's one set that will sort the list in four exchanges:

```
2 2 1 3 3 3 2 3 1 -> 1 2 2 3 3 3 2 3 1
^   ^             

1 2 2 3 3 3 2 3 1 -> 1 2 2 1 3 3 2 3 3
      ^         ^ 

1 2 2 1 3 3 2 3 3 -> 1 1 2 2 3 3 2 3 3
  ^   ^           

1 1 2 2 3 3 2 3 3 -> 1 1 2 2 2 3 3 3 3

```