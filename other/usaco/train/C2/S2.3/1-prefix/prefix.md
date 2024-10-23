Longest Prefix
IOI'96
The structure of some biological objects is represented by the sequence of their constituents, where each part is denoted by an uppercase letter. Biologists are interested in decomposing a long sequence into shorter sequences called primitives.

We say that a sequence S can be composed from a given set of primitives P if there is a some sequence of (possibly repeated) primitives from the set whose concatenation equals S. Not necessarily all primitives need be present. For instance the sequence ABABACABAABcan be composed from the set of primitives

	   {A, AB, BA, CA, BBC}
The first K characters of S are the prefix of S with length K. Write a program which accepts as input a set of primitives and a sequence of constituents and then computes the length of the longest prefix that can be composed from primitives.

PROGRAM NAME: prefix
INPUT FORMAT
First, the input file contains the list (length 1..200) of primitives (length 1..10) expressed as a series of space-separated strings of upper-case characters on one or more lines.
The list of primitives is terminated by a line that contains nothing more than a period (`.'). No primitive appears twice in the list. Then, the input file contains a sequence S (length 1..200,000) expressed as one or more lines, none of which exceeds 76 letters in length.
The "newlines" (line terminators) are not part of the string S.
SAMPLE INPUT (file prefix.in)
A AB BA CA BBC
.
ABABACABAABC
OUTPUT FORMAT
A single line containing an integer that is the length of the longest prefix that can be composed from the set P.
SAMPLE OUTPUT (file prefix.out)
11