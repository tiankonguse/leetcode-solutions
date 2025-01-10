Finding the K-th Element  寻找第 K 个元素
Another important class of problems is the search for the 𝑘
-th ascending element in some set.
另一类重要的问题是寻找 𝑘
 -某个集合中的第一个升序元素。
Suppose we have several segments of numbers.
假设我们有几段数字。

[1,2,3,4]
[3,4,5]
[4,5,6,7,8]
[6,7]
Thus, each segment is specified by two numbers — its left boundary 𝑙𝑖
 and right boundary 𝑟𝑖
.
因此，每个段由两个数字指定——其左边界 𝑙𝑖
 和右边界 𝑟𝑖
 。

We want to put all of them into one large multiset and find the 𝑘
-th ascending element in it. In this case, if we merge all the segments, we will get [1,2,3,3,4,4,4,5,5,6,6,7,7,8]
.
我们想将它们全部放入一个大的多重集中并找到 𝑘
 - 其中的第一个升序元素。在这种情况下，如果我们合并所有段，我们将得到 [1,2,3,3,4,4,4,5,5,6,6,7,7,8]
 。

This problem is solved by different methods, but the solution by binary search is the simplest. Let's make a check function 𝑐𝑛𝑡(𝑥)
 that returns the number of elements in the set that less than 𝑥
.
这个问题可以通过不同的方法来解决，但是二分查找的解决方案是最简单的。我们来做一个检查函数 𝑐𝑛𝑡(𝑥)
 返回集合中小于的元素数量 𝑥
 。

Then what is the 𝑘
-th element? This is the maximum element 𝑥
 such that 𝑐𝑛𝑡(𝑥)≤𝑘
. This task can be solved by binary search, if we know how to calculate the function 𝑐𝑛𝑡
.
那么什么是 𝑘
 第-个元素？这是最大元素 𝑥
 这样 𝑐𝑛𝑡(𝑥)≤𝑘
 。如果我们知道如何计算函数，这个任务可以通过二分搜索来解决 𝑐𝑛𝑡
 。

How to define the 𝑐𝑛𝑡
 function? Let's go through all segments and count how many elements less than 𝑥
 are on this segment. The sum of all such values ​​will be the answer. Since each segment contains consecutive numbers, then if 𝑥≤𝑙
, then the answer is 0
, otherwise the answer is min(𝑟𝑖,𝑥)−𝑙𝑖
. This is a general algorithm and can be used for many tasks. If a given set consists of numbers, then usually everything is simple. But with this algorithm, you can also build more complex objects such as bit vectors or permutations.
如何定义 𝑐𝑛𝑡
 功能？让我们遍历所有段并计算有多少个元素小于 𝑥
 都在这个部分。所有这些值的总和就是答案。由于每个段包含连续的数字，那么如果 𝑥≤𝑙
 ，那么答案就是 0
 ，否则答案是 min(𝑟𝑖,𝑥)−𝑙𝑖
 。这是一种通用算法，可用于许多任务。如果给定的集合由数字组成，那么通常一切都很简单。但使用此算法，您还可以构建更复杂的对象，例如位向量或排列。
It is enough to be able to calculate the function 𝑐𝑛𝑡(𝑥)
 from any object. It is important to remember that log𝑛
, where n — the number of bit masks of length 𝑚
 equals log2𝑚=𝑚
, and for permutations log𝑛!≈𝑛log𝑛
, so binary search works longer.
能够计算函数就足够了 𝑐𝑛𝑡(𝑥)
 来自任何物体。重要的是要记住 log𝑛
 ，其中 n — 长度位掩码的数量 𝑚
 等于 log2𝑚=𝑚
 ，并且对于排列 log𝑛!≈𝑛log𝑛
 ，因此二分查找的工作时间更长。