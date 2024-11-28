Milk Measuring
Hal Burch
Farmer John must measure Q (1 <= Q <= 20,000) quarts of his finest milk and deliver it in one big bottle to a customer. He fills that bottle with exactly the number of quarts that the customer orders.

Farmer John has always been frugal. He is at the cow hardware store where he must purchase a set of pails with which to measure out Q quarts of milk from his giant milk tank.
Since the pails each cost the same amount, your task is to figure out a minimal set of pails Farmer John can purchase in order to fill a bottle with exactly Q quarts of milk.
Additionally, since Farmer John has to carry the pails home, given two minimal sets of pails he should choose the "smaller" one as follows: Sort the sets in ascending order. Compare the first pail in each set and choose the set with the smallest pail.
If the first pails match, compare the second pails and choose from among those, else continue until the two sets differ. Thus the set {3, 5, 7, 100} should be chosen over {3, 6, 7, 8}.

To measure out milk, FJ may completely fill a pail from the tank and pour it into the bottle. He can never remove milk from the bottle or pour milk anywhere except into the bottle. With a one-quart pail, FJ would need only one pail to create any number of quarts in a bottle.
Other pail combinations are not so convenient.

Determine the optimally small number of pails to purchase, given the guarantee that at least one solution is possible for all contest input data.

PROGRAM NAME: milk4
INPUT FORMAT
Line 1:	The single integer Q
Line 2:	A single integer P (1 <= P <= 100) which is the number of pails in the store
Lines 3..P+2:	Each line contains a single integer pail_value (1 <= pail_value <= 10000), the number of quarts a pail holds
SAMPLE INPUT (file milk4.in)
16
3
3
5
7
OUTPUT FORMAT
The output is a single line of space separated integers that contains:

the minimum number of pails required to measure out the desired number of quarts, followed by:
a sorted list (from smallest to largest) of the capacity of each of the required pails
SAMPLE OUTPUT (file milk4.out)
2 3 5