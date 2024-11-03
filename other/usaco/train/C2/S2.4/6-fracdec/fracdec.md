Fractions to Decimals
Write a program that will accept a fraction of the form N/D, where N is the numerator and D is the denominator and print the decimal representation. If the decimal representation has a repeating sequence of digits, indicate the sequence by enclosing it in brackets.
For example, 1/3 = .33333333...is denoted as 0.(3), and 41/333 = 0.123123123...is denoted as 0.(123). Use xxx.0 to denote an integer. Typical conversions are:

1/3     =  0.(3)
22/5    =  4.4
1/7     =  0.(142857)
2/2     =  1.0
3/8     =  0.375
45/56   =  0.803(571428)
PROGRAM NAME: fracdec
INPUT FORMAT
A single line with two space separated integers, N and D, 1 <= N,D <= 100000.
SAMPLE INPUT (file fracdec.in)
45 56
OUTPUT FORMAT
The decimal expansion, as detailed above. If the expansion exceeds 76 characters in length, print it on multiple lines with 76 characters per line.
SAMPLE OUTPUT (file fracdec.out)
0.803(571428)