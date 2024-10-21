## Preface Numbering

A certain book's prefaces are numbered in upper case Roman numerals. Traditional Roman numeral values use a single letter to represent a certain subset of decimal numbers. Here is the standard set:

```
        I   1     L   50    M  1000
        V   5     C  100
        X  10     D  500
```


As many as three of the same marks that represent 10n may be placed consecutively to form other numbers:

III is 3
CCC is 300

Any mark that has the value 5x10n can not be used consecutively.

Generally (with the exception of the next rule), marks are connected together and written in descending order to form even more numbers:

CCLXVIII = 100+100+50+10+5+1+1+1 = 268
Sometimes, a mark that represents 10^n is placed before a mark of one of the two next higher values (I before V or X; X before L or C; etc.). In this case, the value of the smaller mark is SUBTRACTED from the mark it precedes:

IV = 4
IX = 9
XL = 40

This compound mark forms a unit and may not be combined to make another compound mark (e.g., IXL is wrong for 39; XXXIX is correct).
Compound marks like XD, IC, and XM are not legal, since the smaller mark is too much smaller than the larger one. For XD (wrong for 490), one would use CDXC; for IC (wrong for 99), one would use XCIX; for XM (wrong for 990), one would use CMXC. 90 is expressed XC and not LXL, since L followed by X connotes that successive marks are X or smaller (probably, anyway). Only the next power of ten below a mark can be placed before that mark.

Given N (1 <= N < 3,500), the number of pages in the preface of a book, calculate and print the number of I's, V's, etc. (in order from lowest to highest) required to typeset all the page numbers (in Roman numerals) from 1 through N. Do not print letters that do not appear in the page numbers specified.

If N = 5, then the page numbers are: I, II, III, IV, V. The total number of I's is 7 and the total number of V's is 2.

## PROGRAM NAME: preface

## INPUT FORMAT

A single line containing the integer N.

## SAMPLE INPUT (file preface.in)

5

## OUTPUT FORMAT

The output lines specify, in ascending order of Roman numeral letters, the letter, a single space, and the number of times that letter appears on preface page numbers. Stop printing letter totals after printing the highest value letter used to form preface numbers in the specified set.

## SAMPLE OUTPUT (file preface.out)

```
I 7
V 2
```