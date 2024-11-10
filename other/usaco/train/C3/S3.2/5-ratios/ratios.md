Feed Ratios
1998 ACM Finals, Dan Adkins
Farmer John feeds his cows only the finest mixture of cow food, which has three components: Barley, Oats, and Wheat. While he knows the precise mixture of these easily mixable grains, he can not buy that mixture!
He buys three other mixtures of the three grains and then combines them to form the perfect mixture.

Given a set of integer ratios barley:oats:wheat, find a way to combine them IN INTEGER MULTIPLES to form a mix with some goal ratio x:y:z.

For example, given the goal 3:4:5 and the ratios of three mixtures:

        1:2:3
        3:7:1
        2:1:2
your program should find some minimum number of integer units (the `mixture') of the first, second, and third mixture that should be mixed together to achieve the goal ratio or print `NONE'.
`Minimum number' means the sum of the three non-negative mixture integers is minimized.
For this example, you can combine eight units of mixture 1, one unit of mixture 2, and five units of mixture 3 to get seven units of the goal ratio:

    8*(1:2:3) + 1*(3:7:1) + 5*(2:1:2) = (21:28:35) = 7*(3:4:5)
Integers in the goal ratio and mixture ratios are all non-negative and smaller than 100 in magnitude. The number of units of each type of feed in the mixture must be less than 100. The mixture ratios are not linear combinations of each other.

PROGRAM NAME: ratios
INPUT FORMAT
Line 1:	Three space separated integers that represent the goal ratios
Line 2..4:	Each contain three space separated integers that represent the ratios of the three mixtures purchased.
SAMPLE INPUT (file ratios.in)
3 4 5
1 2 3
3 7 1
2 1 2
OUTPUT FORMAT
The output file should contain one line containing four integers or the word `NONE'. The first three integers should represent the number of units of each mixture to use to obtain the goal ratio.
The fourth number should be the multiple of the goal ratio obtained by mixing the initial feed using the first three integers as mixing ratios.

SAMPLE OUTPUT (file ratios.out)
8 1 5 7