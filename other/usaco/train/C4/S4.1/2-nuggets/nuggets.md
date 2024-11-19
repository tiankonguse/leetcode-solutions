Beef McNuggets
Hubert Chen
Farmer Brown's cows are up in arms, having heard that McDonalds is considering the introduction of a new product: Beef McNuggets. The cows are trying to find any possible way to put such a product in a negative light.

One strategy the cows are pursuing is that of `inferior packaging'. ``Look,'' say the cows, ``if you have Beef McNuggets in boxes of 3, 6, and 10, you can not satisfy a customer who wants 1, 2, 4, 5, 7, 8, 11, 14, or 17 McNuggets. Bad packaging: bad product.''

Help the cows.
Given N (the number of packaging options, 1 <= N <= 10), and a set of N positive integers (1 <= i <= 256) that represent the number of nuggets in the various packages, output the largest number of nuggets that can not be purchased by buying nuggets in the given sizes.
Print 0 if all possible purchases can be made or if there is no bound to the largest number.

The largest impossible number (if it exists) will be no larger than 2,000,000,000.

PROGRAM NAME: nuggets
INPUT FORMAT
Line 1:	N, the number of packaging options
Line 2..N+1:	The number of nuggets in one kind of box
SAMPLE INPUT (file nuggets.in)
3
3
6
10
OUTPUT FORMAT
The output file should contain a single line containing a single integer that represents the largest number of nuggets that can not be represented or 0 if all possible purchases can be made or if there is no bound to the largest number.
SAMPLE OUTPUT (file nuggets.out)
17