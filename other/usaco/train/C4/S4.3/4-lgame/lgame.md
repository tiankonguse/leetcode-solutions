Letter Game
IOI 1995

Figure 1: Each of the 26 lowercase letters and its value
Letter games are popular at home and on television. In one version of the game, every letter has a value, and you collect letters to form one or more words giving the highest possible score.
Unless you have `a way with words', you will try all the words you know, sometimes looking up the spelling, and then compute the scores. Obviously, this can be done more accurately by computer.

Given the values in Figure 1, a list of words, and the letters collected: find the highest scoring words or pairs of words that can be formed.

PROGRAM NAME: lgame
INPUT FORMAT
One line with a string of lowercase letters (from `a' through `z'). The string consists of at least 3 and at most 7 letters in arbitrary order.
SAMPLE INPUT (file lgame.in)
prmgroa
DICTIONARY FORMAT
At most 40,000 lines, each containing a string of at least 3 and at most 7 lowercase letters. At the end of this file is a line with a single period (`.'). The file is sorted alphabetically and contains no duplicates.
SAMPLE DICTIONARY (file lgame.dict)
profile
program
prom
rag
ram
rom
.
OUTPUT FORMAT
On the first line, your program should write the highest possible score, and on each of the following lines, all the words and/or word pairs from file lgame.dict with this score. Sort the output alphabetically by first word, and if tied, by second word. A letter must not occur more often in an output line than in the input line. Use the letter values given in Figure 1.

When a combination of two words can be formed with the given letters, the words should be printed on the same line separated by a space. The two words should be in alphabetical order; for example, do not write `rag prom', only write `prom rag'. A pair in an output line may consist of two identical words.

SAMPLE OUTPUT (file lgame.out)
This output uses the tiny dictionary above, not the lgame.dict dictionary.

24
program
prom rag