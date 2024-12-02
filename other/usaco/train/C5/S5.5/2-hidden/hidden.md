Hidden Password
ACM South Eastern Europe -- 2003
Sometimes the programmers have very strange ways of hiding their passwords. Billy "Hacker" Geits chooses a string S composed of L (5 <= L <= 100,000) lowercase letters ('a'..'z') with length L. Then he makes all the L-1 one-letter left cyclic shifts of the string and sorts them along with the original string. He then takes as a password one prefix of the lexicographically first of the obtained strings (including S).

For example consider the string "alabala". Here is the initial string and all of its one-letter left cyclic shifts:
alabala, labalaa, abalaal, balaala, alaalab, laalaba, aalabal. The sorted cyclic one-letter left shifts (including the initial string) are:


aalabal
abalaal
alaalab
alabala
balaala
laalaba
labalaa

Lexicographically, first string is 'aalabal'. The first letter of this string ('a') is the 'a' that was in position 6 in the initial string (counting the first letter in the string as position 0).

Write a program that, for given string S, finds the start position of the first letter of the sorted list of cyclic shifts of the string. If the first element appears more than once in the sorted list, then the program should output the smallest possible initial position.

PROGRAM NAME: hidden
INPUT FORMAT
Line 1: A single integer: L
Line 2..?: All L characters of the string S, broken across lines such that each line has 72 characters except the last one, which might have fewer.
SAMPLE INPUT (file hidden.in)
7
alabala

OUTPUT FORMAT
Line 1: A single integer that is the start position of the first letter, as described above.
SAMPLE OUTPUT (file hidden.out)
6