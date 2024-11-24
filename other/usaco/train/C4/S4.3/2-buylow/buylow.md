Buy Low, Buy Lower
The advice to "buy low" is half the formula to success in the stock market. But to be considered a great investor you must also follow this problems' advice:

"Buy low, buy lower"
That is, each time you buy a stock, you must purchase more at a lower price than the previous time you bought it. The more times you buy at a lower price than before, the better! Your goal is to see how many times you can continue purchasing at ever lower prices.

You will be given the daily selling prices of a stock over a period of time. You can choose to buy stock on any of the days. Each time you choose to buy, the price must be lower than the previous time you bought stock.
Write a program which identifies which days you should buy stock in order to maximize the number of times you buy.

By way of example, suppose on successive days stock is selling like this:

 Day   1  2  3  4  5  6  7  8  9 10 11 12
Price 68 69 54 64 68 64 70 67 78 62 98 87
In the example above, the best investor (by this problem, anyway) can buy at most four times if they purchase at a lower price each time. One four day sequence (there might be others) of acceptable buys is:

Day    2  5  6 10
Price 69 68 64 62
PROGRAM NAME: buylow
INPUT FORMAT
Line 1:	N (1 <= N <= 5000), the number of days for which stock prices are available.
Line 2..etc:	A series of N positive space-separated integers (which may require more than one line of data) that tell the price for that day. The integers will fit into 32 bits quite nicely.
SAMPLE INPUT (file buylow.in)
12
68 69 54 64 68 64 70 67
78 62 98 87
OUTPUT FORMAT
Two integers on a single line:

the length of the longest sequence of decreasing prices
the number of sequences that have this length
In counting the number of solutions, two potential solutions are considered the same (and would only count as one solution) if they repeat the same string of decreasing prices, that is, if they "look the same" when the successive prices are compared.
Thus, two different sequence of "buy" days could produce the same string of decreasing prices and be counted as only a single solution.

SAMPLE OUTPUT (file buylow.out)
4 2