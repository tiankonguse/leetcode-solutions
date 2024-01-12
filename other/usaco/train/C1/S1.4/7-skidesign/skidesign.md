**Ski Course Design 滑雪场设计**  

Farmer John has N hills on his farm (1 <= N <= 1,000), each with an integer elevation in the range 0 .. 100. In the winter, since there is abundant snow on these hills, FJ routinely operates a ski training camp.  
Farmer John 在他的农场里有 N 个山丘 (1 <= N <= 1,000)，每个山丘的海拔都在 0 .. 100 范围内。在冬天，由于这些山丘上积雪丰富，FJ 定期进行滑雪训练营。

Unfortunately, FJ has just found out about a new tax that will be assessed next year on farms used as ski training camps.  
不幸的是，FJ 刚刚发现明年将对用作滑雪训练营的农场征收新税。  
Upon careful reading of the law, however, he discovers that the official definition of a ski camp requires the difference between the highest and lowest hill on his property to be strictly larger than 17. Therefore, if he shortens his tallest hills and adds mass to increase the height of his shorter hills, FJ can avoid paying the tax as long as the new difference between the highest and lowest hill is at most 17.  
然而，仔细阅读法律后，他发现滑雪营地的官方定义要求他的财产上最高和最低的山丘之间的差异严格大于 17。因此，如果他缩短最高的山丘并增加质量增加他的矮山的高度，只要新的最高和最低山之间的差异最多为17，FJ就可以避免缴税。

If it costs x^2 units of money to change the height of a hill by x units, what is the minimum amount of money FJ will need to pay? FJ can change the height of a hill only once, so the total cost for each hill is the square of the difference between its original and final height.  
如果将山的高度改变 x 个单位需要花费 x^2 个单位的钱，那么 FJ 需要支付的最低金额是多少？ FJ 只能改变一座山的高度一次，因此每座山的总成本是其原始高度和最终高度之差的平方。  
FJ is only willing to change the height of each hill by an integer amount.  
FJ 只愿意将每个山丘的高度改变一个整数。

### PROGRAM NAME: skidesign  
程序名称：滑雪设计

### INPUT FORMAT: 输入格式：

Line 1: 1号线：

The integer N. 整数N。

Lines 2..1+N: 第 2..1+N 行：

Each line contains the elevation of a single hill.  
每条线包含一座山的海拔。

### SAMPLE INPUT (file skidesign.in):  
示例输入（文件skidesign.in）：

5
20
4
1
24
21

### INPUT DETAILS: 输入详细信息：

FJ's farm has 5 hills, with elevations 1, 4, 20, 21, and 24.  
FJ 的农场有 5 个山丘，海拔分别为 1、4、20、21 和 24。

### OUTPUT FORMAT:  输出格式：

The minimum amount FJ needs to pay to modify the elevations of his hills so the difference between largest and smallest is at most 17 units.  
FJ 需要支付的最低金额来修改他的山丘的海拔，因此最大和最小之间的差异最多为 17 个单位。

Line 1: 1号线：

### SAMPLE OUTPUT (file skidesign.out):  
示例输出（文件skidesign.out）：

18

### OUTPUT DETAILS: 输出详细信息：

FJ keeps the hills of heights 4, 20, and 21 as they are. He adds mass to the hill of height 1, bringing it to height 4 (cost = 3^2 = 9). He shortens the hill of height 24 to height 21, also at a cost of 3^2 = 9.  
FJ 保持高度 4、20 和 21 的山丘原样。他向高度为 1 的山丘添加质量，使其达到高度 4（成本 = 3^2 = 9）。他将高度 24 的山缩短到高度 21，同样花费了 3^2 = 9。