Minimax Problems  极小极大问题
Another class of problems that need to be analyzed separately — minimax problems. These are problems in which you need to minimize a value that is the maximum of the other values ​min(max(…))
.
另一类需要单独分析的问题——极小极大问题。在这些问题中，您需要最小化其他值中最大值的值​ min(max(…))
 。
Such problems appear quite often and can be reduced to binary search. Let's give an example of such a problem:
此类问题经常出现，可以简化为二分查找。我们举一个这样的问题的例子：

Let us have a number line on which people live. For each person 𝑖
 we know the coordinate of his house 𝑥𝑖
. We want to collect them at one point. That is, we want to choose some point for all people to leave their homes and go to it.
让我们有一条人们生活的数轴。对于每个人 𝑖
 我们知道他家的坐标 𝑥𝑖
 。我们想在某一时刻收集它们。也就是说，我们要选择一个点让所有的人离开自己的家，去那里。

How long can people get together at this point? Depends on how fast people walk. Let's say that 𝑖
-th person has a speed 𝑣𝑖
. Then each person will come to the point 𝑥
 in time |𝑥𝑖−𝑥|𝑣𝑖
. The time for which all people will come to this point — the maximum of these values. We want to minimize this time. That is, we need to find 𝑥
 from this expression min𝑥(max𝑖(|𝑥𝑖−𝑥|𝑣𝑖))
.
这个时候人们还能聚在一起多久？取决于人走路的速度。这么说吧 𝑖
 -第一个人有速度 𝑣𝑖
 。然后每个人都会进入正题 𝑥
 及时 |𝑥𝑖−𝑥|𝑣𝑖
 。所有人都会达到这一点的时间——这些值的最大值。我们希望尽量减少这个时间。也就是说，我们需要找到 𝑥
 从这个表达式 min𝑥(max𝑖(|𝑥𝑖−𝑥|𝑣𝑖))
 。

How to solve this? Let's limit it instead of minimizing max𝑖(|𝑥𝑖−𝑥|𝑣𝑖)
. That is, we need a function 𝑓(𝑡)
 that checks that max𝑖(|𝑥𝑖−𝑥|𝑣𝑖)≤𝑡
.
如何解决这个问题？让我们限制它而不是最小化它 max𝑖(|𝑥𝑖−𝑥|𝑣𝑖)
 。也就是说，我们需要一个函数 𝑓(𝑡)
 检查 max𝑖(|𝑥𝑖−𝑥|𝑣𝑖)≤𝑡
 。

This function is monotone, if 𝑡
 fits the condition, then for any 𝑦>0 𝑡+𝑦
 also fits. If we find the minimum value at which 𝑓(𝑡)=1
, then this is 𝑡
 will be the answer to the problem. This is already a classic binary search problem.
这个函数是单调的，如果 𝑡
 满足条件，那么对于任意 𝑦>0 𝑡+𝑦
 也适合。如果我们找到最小值 𝑓(𝑡)=1
 ，那么这是 𝑡
 将是问题的答案。这已经是一个经典的二分查找问题了。

Let's figure out how to define the 𝑓
 function. What does it mean that max𝑖(|𝑥𝑖−𝑥|𝑣𝑖)≤𝑡
? This means that for any 𝑖
, |𝑥𝑖−𝑥|𝑣𝑖≤𝑡
 is satisfied.
让我们弄清楚如何定义 𝑓
 功能。这意味着什么 max𝑖(|𝑥𝑖−𝑥|𝑣𝑖)≤𝑡
 ？这意味着对于任何 𝑖
 , |𝑥𝑖−𝑥|𝑣𝑖≤𝑡
 很满意。

Let's rewrite this expression as |𝑥𝑖−𝑥|≤𝑡⋅𝑣𝑖
.
让我们将这个表达式重写为 |𝑥𝑖−𝑥|≤𝑡⋅𝑣𝑖
 。

And it turns, that 𝑥𝑖−𝑡⋅𝑣𝑖≤𝑥≤𝑥𝑖+𝑡⋅𝑣𝑖
, that is, 𝑥
 belongs to the segment [𝑥𝑖−𝑡⋅𝑣𝑖,𝑥𝑖+𝑡⋅𝑣𝑖]
.
事实证明， 𝑥𝑖−𝑡⋅𝑣𝑖≤𝑥≤𝑥𝑖+𝑡⋅𝑣𝑖
 ， 那是， 𝑥
 属于段 [𝑥𝑖−𝑡⋅𝑣𝑖,𝑥𝑖+𝑡⋅𝑣𝑖]
 。

Let's find all such segments. What does it mean that there is a point 𝑥
 matching the condition? This means that it belongs to all segments [𝑥𝑖−𝑡⋅𝑣𝑖,𝑥𝑖+𝑡⋅𝑣𝑖]
, which means that their intersection is non-empty. We have reduced our problem to the problem of checking if the intersection of 𝑛
 segments is empty.
让我们找到所有这样的片段。有一个点是什么意思 𝑥
 符合条件？这意味着它属于所有段 [𝑥𝑖−𝑡⋅𝑣𝑖,𝑥𝑖+𝑡⋅𝑣𝑖]
 ，这意味着它们的交集非空。我们已将问题简化为检查是否存在交集的问题 𝑛
 段为空。

This problem can be solved in linear time, you need to find the maximum from the left boundaries and the minimum from the right ones (this is the intersection segment). If its length is greater than zero, then the intersection is non-empty.
这个问题可以在线性时间内解决，你需要找到左侧边界的最大值和右侧边界的最小值（这是交叉线段）。如果其长度大于零，则交集非空。
This is a general algorithm for solving similar problems. With the help of binary search, they are reduced to checking that the maximum of some values ​​is limited to a certain number.
这是解决类似问题的通用算法。在二分查找的帮助下，它们被简化为检查某些值的最大值是否限制为某个数字。