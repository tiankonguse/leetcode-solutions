Musical Themes
Brian Dean
A musical melody is represented as a sequence of N (1 <= N <= 5000) notes that are integers in the range 1..88, each representing a key on the piano.
It is unfortunate but true that this representation of melodies ignores the notion of musical timing; but, this programming task is about notes and not timings.

Many composers structure their music around a repeating "theme", which, being a subsequence of an entire melody, is a sequence of integers in our representation. A subsequence of a melody is contiguous series of consecutive notes from the melody.
A subsequence of a melody is a theme if it:

is at least five notes long
appears (potentially transposed -- see below) again somewhere else in the piece of music
is fully disjoint from (i.e., non-overlapping with) at least one of its other appearance(s)
Transposed means that a constant positive or negative value is added to every note value in the theme subsequence.
Given a melody, compute the length (number of notes) of the longest theme.

One second time limit for this problem's solutions!

PROGRAM NAME: theme
INPUT FORMAT
The first line of the input file contains the integer N. Each subsequent line (except potentially the last) contains 20 integers representing the sequence of notes. The last line contains the remainder of the notes, potentially fewer than 20.

SAMPLE INPUT (file theme.in)
30
25 27 30 34 39 45 52 60 69 79 69 60 52 45 39 34 30 26 22 18
82 78 74 70 66 67 64 60 65 80
OUTPUT FORMAT
The output file should contain a single line with a single integer that represents the length of the longest theme. If there are no themes, output 0.

SAMPLE OUTPUT (file theme.out)
5
[The five-long theme is the last five notes of the first line and the first five notes of the second]