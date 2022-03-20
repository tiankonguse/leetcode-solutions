# Friday the Thirteenth

Is Friday the 13th really an unusual event?

That is, does the 13th of the month land on a Friday less often than on any other day of the week? To answer this question, write a program that will compute the frequency that the 13th of each month lands on Saturday, Sunday, Monday, Tuesday, Wednesday, Thursday, and Friday over a given period of N years. The time period to test will be from January 1, 1900 to December 31, 1900+N-1 for a given number of years, N. N is positive and will not exceed 400.

**Note that the start year is NINETEEN HUNDRED, not NINETEEN NINETY.**

There are few facts you need to know before you can solve this problem:

January 1, 1900 was on a Monday.
Thirty days has September, April, June, and November, all the rest have 31 except for February which has 28 except in leap years when it has 29.
Every year evenly divisible by 4 is a leap year (1992 = 4*498 so 1992 will be a leap year, but the year 1990 is not a leap year)
The rule above does not hold for century years. Century years divisible by 400 are leap years, all others are not. Thus, the century years 1700, 1800, 1900 and 2100 are not leap years, but 2000 is a leap year.
Do not use any built-in date functions in your computer language.

Don't just precompute the answers, either, please.