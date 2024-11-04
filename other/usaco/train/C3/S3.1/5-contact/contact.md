Contact
IOI'98
The cows have developed a new interest in scanning the universe outside their farm with radiotelescopes. Recently, they noticed a very curious microwave pulsing emission sent right from the centre of the galaxy. They wish to know if the emission is transmitted by some extraterrestrial form of intelligent life or if it is nothing but the usual heartbeat of the stars.

Help the cows to find the Truth by providing a tool to analyze bit patterns in the files they record. They are seeking bit patterns of length A through B inclusive (1 <= A <= B <= 12) that repeat themselves most often in each day's data file. They are looking for the patterns that repeat themselves most often. An input limit tells how many of the most frequent patterns to output.

Pattern occurrences may overlap, and only patterns that occur at least once are taken into account.

PROGRAM NAME: contact
INPUT FORMAT
Line 1:	Three space-separated integers: A, B, N; (1 <= N ≤ 50)
Lines 2 and beyond:	A sequence of as many as 200,000 characters, all 0 or 1; the characters are presented 80 per line, except potentially the last line.
SAMPLE INPUT (file contact.in)
2 4 10
01010010010001000111101100001010011001111000010010011110010000000

In this example, pattern 100 occurs 12 times, and pattern 1000 occurs 5 times. The most frequent pattern is 00, with 23 occurrences.

OUTPUT FORMAT
Lines that list the N highest frequencies (in descending order of frequency) along with the patterns that occur in those frequencies. Order those patterns by shortest-to-longest and increasing binary number for those of the same frequency. If fewer than N highest frequencies are available, print only those that are.

Print the frequency alone by itself on a line. Then print the actual patterns space separated, six to a line (unless fewer than six remain).

SAMPLE OUTPUT (file contact.out)
23
00
15
01 10
12
100
11
11 000 001
10
010
8
0100
7
0010 1001
6
111 0000
5
011 110 1000
4
0001 0011 1100