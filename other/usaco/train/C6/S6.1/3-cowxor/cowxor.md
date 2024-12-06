
Cow XOR
Adrian Vladu -- 2005
Farmer John is stuck with another problem while feeding his cows. All of his N (1 ≤ N ≤ 100,000) cows (numbered 1..N) are lined up in front of the barn, sorted by their rank in their social hierarchy. Cow #1 has the highest rank; cow #N has the least rank.
Every cow had additionally been assigned a non-unique integer number in the range 0..(221 - 1).

Help FJ choose which cows will be fed first by selecting a sequence of consecutive cows in the line such that the bitwise "xor" between their assigned numbers has the maximum value.
If there are several such sequences, choose the sequence for which its last cow has the highest rank. If there still is a tie, choose the shortest sequence.

TIME LIMIT: 0.5 sec
PROGRAM NAME: cowxor
INPUT FORMAT
Line 1: A single integer N
Lines 2..N+1: N integers ranging from 0 to 221 - 1, representing the cows' assigned numbers. Line j describes cow of social hierarchy j-1.
SAMPLE INPUT (file cowxor.in)
5
1
0
5
4
2
INPUT DETAILS:
There are 5 cows. Cow #1 had been assigned with 1; cow #2 with 0; cow #3 with 5; cow #4 with 4; cow #5 with 2.
OUTPUT FORMAT
Line 1: Three space-separated integers, respectively: the maximum requested value, the position where the sequence begins, the position where the sequence ends.
SAMPLE OUTPUT (file cowxor.out)
6 4 5
OUTPUT DETAILS:
4 xor 2 = 6 (001) xor (010) = (011)