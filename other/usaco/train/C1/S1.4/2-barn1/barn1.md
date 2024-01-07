# Barn Repair


It was a dark and stormy night that ripped the roof and gates off the stalls that hold Farmer John's cows. Happily, many of the cows were on vacation, so the barn was not completely full.

The cows spend the night in stalls that are arranged adjacent to each other in a long line. Some stalls have cows in them; some do not. All stalls are the same width.

Farmer John must quickly erect new boards in front of the stalls, since the doors were lost. His new lumber supplier will supply him boards of any length he wishes, but the supplier can only deliver a small number of total boards. Farmer John wishes to minimize the total length of the boards he must purchase.

Given M (1 <= M <= 50), the maximum number of boards that can be purchased; S (1 <= S <= 200), the total number of stalls; C (1 <= C <= S) the number of cows in the stalls, and the C occupied stall numbers (1 <= stall_number <= S), calculate the minimum number of stalls that must be blocked in order to block all the stalls that have cows in them.

Print your answer as the total number of stalls blocked.

## PROGRAM NAME: barn1


## INPUT FORMAT

Line 1:	M, S, and C (space separated)
Lines 2-C+1:	Each line contains one integer, the number of an occupied stall.


## SAMPLE INPUT (file barn1.in)

```
4 50 18
3
4
6
8
14
15
16
17
21
25
26
27
30
31
40
41
42
43
```

## OUTPUT FORMAT


A single line with one integer that represents the total number of stalls blocked.


## SAMPLE OUTPUT (file barn1.out)

25

[One minimum arrangement is one board covering stalls 3-8, one covering 14-21, one covering 25-31, and one covering 40-43.]

## ANALYSIS

If we can purchase M boards, then we can leave unblocked M-1 runs of stalls without cows in them, in addition to any stalls on the leftmost side that don't have cows and any stalls on the rightmost side that don't have cows.

We input the list of cows in stalls, storing into an array whether or not there is a cow in a particular stall. Then we walk the array counting sizes of runs of cowless stalls. We sort the list of sizes and pick the M-1 largest ones as the stalls that will remain uncovered.