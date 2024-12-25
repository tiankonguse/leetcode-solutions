Other Problems  其他问题

https://codeforces.com/edu/course/2/lesson/4/2

We learned how to build the segment tree. Let's figure out how to solve the following problems.
我们学习了如何构建线段树。让我们弄清楚如何解决以下问题。
The segment with the maximum sum
总和最大的段

Now we consider the problem of finding a segment with a maximum sum. Our data structure must support two operations on the array:
现在我们考虑寻找具有最大总和的线段的问题。我们的数据结构必须支持数组上的两种操作：

set(i, v): set the element with index 𝑖
 to 𝑣
.
set(i, v) ：设置具有索引的元素 𝑖
 到 𝑣
 。
max_segment(): find the segment of the array with the maximum sum.
max_segment() ：找到数组中总和最大的段。
Let's try to build a segment tree that calculates the required function.
让我们尝试构建一个线段树来计算所需的函数。

Consider the segment 𝑥
, which is divided into two halves. We want for the segment 𝑥
 to find the value 𝑠𝑒𝑔
: the sum on the subsegment with the maximum sum. Note that knowing only 𝑠𝑒𝑔1
 and 𝑠𝑒𝑔2
 (answers for halves) we cannot get 𝑠𝑒𝑔
, because the answer for 𝑥
 can intersect both segments. But in case of intersection, the optimal segment consists of the suffix of the left half and the prefix of the right half. Let’s record for each segment two more values: ​𝑝𝑟𝑒𝑓
 and 𝑠𝑢𝑓
: prefix and suffix with the maximum sum. Then you can calculate 𝑠𝑒𝑔
 as follows: 𝑠𝑒𝑔=max(𝑠𝑒𝑔1,𝑠𝑒𝑔2,𝑠𝑢𝑓1+𝑝𝑟𝑒𝑓2)
.
考虑细分市场 𝑥
 ，分为两半。我们想要这个细分市场 𝑥
 找到价值 𝑠𝑒𝑔
 ：具有最大总和的子段上的总和。注意，只知道 𝑠𝑒𝑔1
 和 𝑠𝑒𝑔2
 （一半的答案）我们无法得到 𝑠𝑒𝑔
 ，因为答案为 𝑥
 可以与两个线段相交。但在相交的情况下，最优线段由左半部分的后缀和右半部分的前缀组成。让我们为每个段记录另外两个值：​ 𝑝𝑟𝑒𝑓
 和 𝑠𝑢𝑓
 ：前缀和后缀的最大总和。然后你可以计算 𝑠𝑒𝑔
 如下： 𝑠𝑒𝑔=max(𝑠𝑒𝑔1,𝑠𝑒𝑔2,𝑠𝑢𝑓1+𝑝𝑟𝑒𝑓2)
 。


How we need to recalculate 𝑝𝑟𝑒𝑓
 and 𝑠𝑢𝑓
. Consider 𝑝𝑟𝑒𝑓
, 𝑠𝑢𝑓
 will be considered similarly. The maximum prefix is ​​either the maximum prefix of the left half, or consists of the entire left half and the maximum prefix of the right half. Add to each node another value 𝑠𝑢𝑚
, equal to the sum on the segment. Then 𝑝𝑟𝑒𝑓=max(𝑝𝑟𝑒𝑓1,𝑠𝑢𝑚1+𝑝𝑟𝑒𝑓2)
, similarly 𝑠𝑢𝑓=max(𝑠𝑢𝑓2,𝑠𝑢𝑚2+𝑠𝑢𝑓1)
. Finally, the sum can be calculated using the formula 𝑠𝑢𝑚=𝑠𝑢𝑚1+𝑠𝑢𝑚2
.
我们需要如何重新计算 𝑝𝑟𝑒𝑓
 和 𝑠𝑢𝑓
 。考虑 𝑝𝑟𝑒𝑓
 , 𝑠𝑢𝑓
 将被类似地考虑。最大前缀要么是左半部的最大前缀，要么是整个左半部和右半部的最大前缀组成。向每个节点添加另一个值 𝑠𝑢𝑚
 ，等于线段上的总和。然后 𝑝𝑟𝑒𝑓=max(𝑝𝑟𝑒𝑓1,𝑠𝑢𝑚1+𝑝𝑟𝑒𝑓2)
 ， 相似地 𝑠𝑢𝑓=max(𝑠𝑢𝑓2,𝑠𝑢𝑚2+𝑠𝑢𝑓1)
 。最后，可以使用以下公式计算总和 𝑠𝑢𝑚=𝑠𝑢𝑚1+𝑠𝑢𝑚2
 。

Similarly, we can construct a data structure with the additional operation max_subsegment(l, r): find the subsegment of the segment from 𝑙
 to 𝑟
 with the maximum sum. To do this, you need to learn how to merge answers for segments, and this is what we just learned to do.
类似地，我们可以通过附加操作max_subsegment(l, r)构建一个数据结构：从 𝑙
 到 𝑟
 与最大总和。为此，您需要学习如何合并片段的答案，这就是我们刚刚学到的。

𝐾
-th one
𝐾
 第一个

Consider the problem of finding the 𝑘
-th one. Our data structure must support two operations on the array:
考虑寻找问题 𝑘
 -第一个。我们的数据结构必须支持数组上的两种操作：

set(i, v): set element 𝑖
 to 𝑣∈{0,1}
.
set(i, v) ：设置元素 𝑖
 到 𝑣∈{0,1}
 。
find(k): find the index of the 𝑘
-th one.
find(k) ：查找索引 𝑘
 -第一个。
The main idea: we maintain a segment tree with the operation 𝑠𝑢𝑚
. Changing an element is done in a standard way. Finding the 𝑘
-th one is equivalent to finding the leftmost prefix with the sum 𝑘+1
. The algorithm is quite simple. Suppose we need to find the 𝑘
-th one on the segment [𝑙,𝑟)
. If 𝑟=𝑙+1
, then we found the desired one. Otherwise, we look at the sum 𝑠
 on the left subsegment. If 𝑘<𝑠
, then the 𝑘
-th one is in the left subtree, otherwise, we need to start the search for the one with index 𝑘−𝑠
 in the right subtree.
主要思想：我们用操作维护一个线段树 𝑠𝑢𝑚
 。更改元素是以标准方式完成的。寻找 𝑘
 -th 1 相当于用总和查找最左边的前缀 𝑘+1
 。该算法非常简单。假设我们需要找到 𝑘
 该段上的第一个 [𝑙,𝑟)
 。如果 𝑟=𝑙+1
 ，然后我们就找到了想要的。否则，我们看总和 𝑠
 在左侧子段上。如果 𝑘<𝑠
 ，那么 𝑘
 -第一个在左子树中，否则，我们需要开始搜索有索引的那个 𝑘−𝑠
 在右子树中。

Obviously, the time of find is 𝑂( 𝑙𝑜𝑔𝑛)
.
显然，查找时间为 𝑂( 𝑙𝑜𝑔𝑛)
 。

Consider a small example. We construct a segment tree with the operation 𝑠𝑢𝑚
. And let's get find(3
) query. We start at the root, the segment [0,8)
, and search of the third one. We look at the left subsegment [0,4)
 and see that it has a sum of 2
, which is less than 𝑘+1=4
. Therefore, we go down to the right subsegment [4,8)
 and look for 𝑘−2=3−2=1
-th one on it. In the left subsegment [4,6)
, the sum is 2
, which is less than or equal to 𝑘+1=1+1=2
, so our unit lies in the subsegment [4,6)
. And finally, in the left subsegment [4,5)
, the sum is 1
, which is less than 2
, which means our one is in the right subsegment [5,6)
 .
考虑一个小例子。我们用以下操作构造一棵线段树 𝑠𝑢𝑚
 。让我们找到( 3
 ）询问。我们从根部开始，即段 [0,8)
 ，并搜索第三个。我们看一下左边的子段 [0,4)
 并看到它的总和为 2
 ，小于 𝑘+1=4
 。因此，我们进入正确的子段 [4,8)
 并寻找 𝑘−2=3−2=1
 - 第一个。在左边的子段中 [4,6)
 ，总和是 2
 ，小于或等于 𝑘+1=1+1=2
 ，所以我们的单位位于子段 [4,6)
 。最后，在左边的子段中 [4,5)
 ，总和是 1
 ，小于 2
 ，这意味着我们位于正确的子段中 [5,6)
 。


The first element greater than or equal to 𝑥
 Consider the task of finding the first element greater than or equal to 𝑥
. Our structure should support two operations on the array:
第一个元素大于或等于 𝑥
 考虑查找第一个大于或等于的元素的任务 𝑥
 。我们的结构应该支持数组上的两种操作：

set(i, v): set element 𝑖
 to 𝑣
.
set(i, v) ：设置元素 𝑖
 到 𝑣
 。
first_above(x): find the first item greater than or equal to 𝑥
.
first_above(x) ：查找第一项大于或等于 𝑥
 。
Let's do the same as the previous task: we construct a tree of segments with the operation 𝑚𝑎𝑥
. To search for an element in a segment, we go down to the left subtree, if there is a maximum of at least 𝑥
, otherwise, we go down to the right subtree.
让我们做与上一个任务相同的事情：我们使用以下操作构造一个段树 𝑚𝑎𝑥
 。要搜索段中的元素，我们向下查找左子树，如果最大至少为 𝑥
 ，否则，我们向下到右子树。

Now let's complicate the task: we need to respond to requests first_above(𝑥
, 𝑙
): find the first element to the right of 𝑙
 greater than or equal to 𝑥
. To process this request, we will act recursively as follows. Suppose we want to find such an element on the segment. If the maximum on the left subsegment is greater than or equal to 𝑥
 and the segment intersects with [𝑙,𝑛)
, then we recursively start from the left subsegment, if we did not find an element in the left subsegment, then we start from the right subsegment. The request will be processed int 𝑂(log𝑛)
 time. The proof is similar to the proof of the statement about finding the sum on a segment: the number of "bad" segments, i.e. the segments for which we went down to the left and to the right do not exceed the number of segments containing the position 𝑙
, which is log𝑛
.
现在让我们把任务复杂化：我们需要先响应请求_above( 𝑥
 , 𝑙
 ) : 找到右侧的第一个元素 𝑙
 大于或等于 𝑥
 。为了处理这个请求，我们将按如下方式递归操作。假设我们想在段上找到这样的元素。如果左侧子段的最大值大于或等于 𝑥
 该线段与 [𝑙,𝑛)
 ，那么我们从左子段开始递归，如果左子段没有找到元素，那么就从右子段开始。该请求将被处理 int 𝑂(log𝑛)
 时间。这个证明类似于求一个段上的总和的陈述的证明：“坏”段的数量，即我们向左和向右向下移动的段不超过包含位置 𝑙
 ，即 log𝑛
 。