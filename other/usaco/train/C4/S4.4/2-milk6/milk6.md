Pollutant Control
Hal Burch
It's your first day in Quality Control at Merry Milk Makers, and already there's been a catastrophe: a shipment of bad milk has been sent out. Unfortunately, you didn't discover this until the milk was already into your delivery system on its way to stores.
You know which grocer that milk was destined for, but there may be multiple ways for the milk to get to that store.

The delivery system is made up of a several warehouses, with trucks running from warehouse to warehouse moving milk.
While the milk will be found quickly, it is important that it does not make it to the grocer, so you must shut down enough trucks to ensure that it is impossible for the milk to get to the grocer in question. Every route costs a certain amount to shut down.
Find the minimum amount that must be spent to ensure the milk does not reach its destination, along with a set of trucks to shut down that achieves this goal at that cost.

PROGRAM NAME: milk6
INPUT FORMAT
Line 1:	Two space separated integers, N and M. N (2 <= N <= 32) is the number of warehouses that Merry Milk Makers has, and M (0 <= M <= 1000) is the number of trucks routes run.
Warehouse 1 is actually the productional facility, while warehouse N is the grocer to which which the bad milk was destined.
Line 2..M+1:	Truck routes: three space-separated integers, Si, Ei, and Ci. Si and Ei (1 <= Si,Ei <= N) correspond to the pickup warehouse and dropoff warehouse for the truck route. Ci (0 <= Ci <= 2,000,000) is the cost of shutting down the truck route.
SAMPLE INPUT (file milk6.in)
4 5
1 3 100
3 2 50
2 4 60
1 2 40
2 3 80
OUTPUT FORMAT
The first line of the output should be two integers, C and T. C is the minimum amount which must be spent in order to ensure the our milk never reaches its destination. T is the minimum number of truck routes that you plan to shut down in order to achieve this goal.
The next T lines sould contain a sorted list of the indexes of the truck routes that you suggest shutting down. If there are multiple sets of truck routes that achieve the goal at minimum cost, choose one that shuts down the minimum number of routes.
If there are still multiple sets, choose the one whose initial routes have the smallest index.

SAMPLE OUTPUT (file milk6.out)
60 1
3
