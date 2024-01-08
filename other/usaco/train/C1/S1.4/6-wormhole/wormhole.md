# Wormholes 虫洞

Farmer John's hobby of conducting high-energy physics experiments on weekends has backfired, causing N wormholes (2 <= N <= 12, N even) to materialize on his farm, each located at a distinct point on the 2D map of his farm (the x,y coordinates are both integers).
农夫约翰周末进行高能物理实验的爱好却适得其反，导致他的农场出现了 N 个虫洞（2 <= N <= 12，甚至 N 个），每个虫洞都位于他农场的 2D 地图上的不同点（ x、y 坐标均为整数）。

According to his calculations, Farmer John knows that his wormholes will form N/2 connected pairs.
根据农夫约翰的计算，他知道他的虫洞将形成 N/2 个相连的对。
For example, if wormholes A and B are connected as a pair, then any object entering wormhole A will exit wormhole B moving in the same direction, and any object entering wormhole B will similarly exit from wormhole A moving in the same direction.
例如，如果虫洞A和B是一对连接的，那么任何进入虫洞A的物体都会以相同的方向移动离开虫洞B，任何进入虫洞B的物体也会以相同的方向移动从虫洞A退出。
This can have rather unpleasant consequences.
这可能会产生相当不愉快的后果。

For example, suppose there are two paired wormholes A at (1,1) and B at (3,1), and that Bessie the cow starts from position (2,1) moving in the +x direction.
例如，假设有两个成对的虫洞 A 在 (1,1) 处，B 在 (3,1) 处，而 Bessie 牛从位置 (2,1) 开始沿 +x 方向移动。
Bessie will enter wormhole B [at (3,1)], exit from A [at (1,1)], then enter B again, and so on, getting trapped in an infinite cycle!
Bessie将进入虫洞B[在(3,1)]，从A退出[在(1,1)]，然后再次进入B，依此类推，陷入无限循环！

   | . . . .
   | A > B .      Bessie will travel to B then
   + . . . .      A then across to B again

   | 。 。 。 。
   | A>B。贝西随后将前往 B
   + . 。 。 。 A然后再次穿越到B
Farmer John knows the exact location of each wormhole on his farm. He knows that Bessie the cow always walks in the +x direction, although he does not remember where Bessie is currently located.
农夫约翰知道他农场中每个虫洞的确切位置。他知道牛贝西总是朝+x方向行走，尽管他不记得贝西当前所在的位置。

Please help Farmer John count the number of distinct pairings of the wormholes such that Bessie could possibly get trapped in an infinite cycle if she starts from an unlucky position.
请帮助农夫约翰数一下虫洞的不同配对的数量，这样如果贝西从一个不幸的位置开始，她可能会陷入无限循环。
FJ doesn't know which wormhole pairs with any other wormhole, so \fBfind all the possibilities (i.e., all the different ways that N wormholes could be paired such that Bessie can, in some way, get in a cycle\fP).
FJ 不知道哪个虫洞与任何其他虫洞配对，因此 \fB 找到所有可能性（即 N 个虫洞可以配对的所有不同方式，以便 Bessie 可以以某种方式进入一个循环 \fP）。
Note that a loop with a smaller number of wormholes might contribute a number of different sets of pairings to the total count as those wormholes that are not in the loop are paired in many different ways.
请注意，虫洞数量较少的循环可能会为总计数贡献许多不同的配对组，因为那些不在循环中的虫洞以多种不同的方式进行配对。

PROGRAM NAME: wormhole
程序名称：虫洞
INPUT FORMAT: 输入格式：
Line 1: 1号线：	The number of wormholes, N.
虫洞数量，N。
Lines 2..1+N: 第 2..1+N 行：	Each line contains two space-separated integers describing the (x,y) coordinates of a single wormhole. Each coordinate is in the range 0..1,000,000,000.
每行包含两个空格分隔的整数，描述单个虫洞的 (x,y) 坐标。每个坐标的范围为 0..1,000,000,000。
SAMPLE INPUT (file wormhole.in):
输入样本（文件 wormhole.in）：
4
0 0
1 0
1 1
0 1
INPUT DETAILS:  输入详细信息：
There are 4 wormholes, forming the corners of a square.
有4个虫洞，形成一个正方形的角。

OUTPUT FORMAT:  输出格式：
Line 1: 1号线：	The number of distinct pairings of wormholes such that Bessie could conceivably get stuck in a cycle walking from some starting point in the +x direction.
虫洞的不同配对数量使得贝西可能会陷入从某个起点沿+x方向行走的循环中。
SAMPLE OUTPUT (file wormhole.out):
示例输出（文件 wormhole.out）：
2
OUTPUT DETAILS: 输出详细信息：
If we number the wormholes 1..4 as we read them from the input, then if wormhole 1 pairs with wormhole 2 and wormhole 3 pairs with wormhole 4, Bessie can get stuck if she starts anywhere between (0,0) and (1,0) or between (0,1) and (1,1).
如果我们在从输入中读取虫洞时将其编号为 1..4，那么如果虫洞 1 与虫洞 2 配对，虫洞 3 与虫洞 4 配对，那么如果 Bessie 从 (0,0) 和 (1) 之间的任何位置开始，她可能会被卡住,0) 或 (0,1) 和 (1,1) 之间。

   | . . 
   d c . 
   a b . 

   | 。 。
   直流。
   乙。
Here is a list of all the pairings, annotated with their wormhole results:
以下是所有配对的列表，并附有虫洞结果注释：
(a b) (c d) -- Bessie loops (a b) if she is on that line
(a b) (c d) -- Bessie 循环 (a b) 如果她在那条线上
(a c) (b d) -- Bessie loops b->d->c->a->b ... if she gets caught
(a c) (b d) -- Bessie 循环 b->d->c->a->b ...如果她被抓住
(a d) (b c)
Only the pairings a-d and b-c allow Bessie to walk in the +x direction from any point in the 2D plane with no danger of cycling.
只有 a-d 和 b-c 配对允许 Bessie 从 2D 平面中的任何点沿 +x 方向行走，而不会产生骑自行车的危险。