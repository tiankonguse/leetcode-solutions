Segment with maximal sum  总和最大的段

https://codeforces.com/edu/course/2/lesson/5/3

Now we will consider the tasks discussed in previous lesson, but with mass changing operations.
现在我们将考虑上一课中讨论的任务，但具有大量更改操作。
Given an array of length 𝑛
, we need to be able to find a subsegment of the array with the maximum sum, and assign a value on the segment.
给定一个长度的数组 𝑛
 ，我们需要能够找到数组中总和最大的子段，并在该段上赋值。

We will store in each node of the segment tree the maximum sum on the segment, the maximum sum on the prefix, the maximum sum on the suffix, and the sum on the entire segment. Let's denote these four values ​​as (𝑠𝑒𝑔,𝑝𝑟𝑒𝑓,𝑠𝑢𝑓,𝑠𝑢𝑚)
. You need to process the request to assign a value to 𝑥
 to the segment [𝑙,𝑟)
, that is, 𝑎𝑖=𝑥
 (𝑙≤𝑖<𝑟
). When propagating, we push the 𝑥
 value into the children and update the node as follows:
我们在线段树的每个节点中存储线段上的最大和、前缀上的最大和、后缀上的最大和以及整个线段上的和。我们将这四个值表示为 (𝑠𝑒𝑔,𝑝𝑟𝑒𝑓,𝑠𝑢𝑓,𝑠𝑢𝑚)
 。您需要处理请求来为其赋值 𝑥
 到该段 [𝑙,𝑟)
 ， 那是， 𝑎𝑖=𝑥
 （ 𝑙≤𝑖<𝑟
 ）。在传播的时候，我们把 𝑥
 值到子级中并更新节点，如下所示：

The sum on the entire segment becomes equal to (𝑟−𝑙)⋅𝑥
,
整个段的总和等于 (𝑟−𝑙)⋅𝑥
 ,

If 𝑥>0
, then 𝑠𝑒𝑔=𝑝𝑟𝑒𝑓=𝑠𝑢𝑓=𝑠𝑢𝑚
, since each segment element will increase the sum,
如果 𝑥>0
 ， 然后 𝑠𝑒𝑔=𝑝𝑟𝑒𝑓=𝑠𝑢𝑓=𝑠𝑢𝑚
 ，由于每个段元素都会增加总和，
If 𝑥<0
, then 𝑠𝑒𝑔=𝑝𝑟𝑒𝑓=𝑠𝑢𝑓=0
, since each segment element will decrease the sum (so we don't take anything).
如果 𝑥<0
 ， 然后 𝑠𝑒𝑔=𝑝𝑟𝑒𝑓=𝑠𝑢𝑓=0
 ，因为每个段元素都会减少总和（所以我们不采取任何措施）。
The rest of the structure of the algorithm remains the same.
算法的其余结构保持不变。
K-th one  第 K 个
You are given an array of length 𝑛
 consisting of zeros and ones. You must be able to find the position of the 𝑘
-th one and assign a value (zero or one) to the segment.
给你一个长度的数组 𝑛
 由零和一组成。您必须能够找到该位置 𝑘
 -th 1 并为该段分配一个值（零或一）。
At each node of the segment tree, we will store the number of ones in the segment that it covers (let's call it 𝑠𝑢𝑚
). To answer the request find k-th one, you must first propagate the change into children, recalculate the number of ones at the current node depending on the value of 𝑥
 and the length of the segment, and then make a choice: which child to go to. If it is necessary not to assign on the segment, but to invert each value (zero becomes one, and one becomes zero), then the update after pushing will consist in replacing the value of 𝑠𝑢𝑚
 with 𝑙𝑒𝑛−𝑠𝑢𝑚
, where 𝑙𝑒𝑛
 is the length the segment covered by the current node.
在线段树的每个节点上，我们将存储它所覆盖的线段中 1 的数量（我们称之为 𝑠𝑢𝑚
 ）。要回答find k-th one 的请求，您必须首先将更改传播到子节点，根据 的值重新计算当前节点的 1 数量 𝑥
 和片段的长度，然后做出选择：去哪个孩子。如果不需要在段上赋值，而是反转每个值（0 变成 1，1 变成 0），那么推送后的更新将包括替换 𝑠𝑢𝑚
 和 𝑙𝑒𝑛−𝑠𝑢𝑚
 ， 在哪里 𝑙𝑒𝑛
 是当前节点所覆盖的线段的长度。

First element above X  X 上方的第一个元素
An array of length 𝑛
 is given. You need to be able to find a position 𝑖
 (𝑖≥𝑙
) for position 𝑙
 and value 𝑥
 such that 𝑎𝑖≥𝑥
, and add 𝑥
 to the segment [𝑙,𝑟)
.
长度的数组 𝑛
 被给出。你需要能够找到一个位置 𝑖
 （ 𝑖≥𝑙
 ) 对于位置 𝑙
 和价值 𝑥
 这样 𝑎𝑖≥𝑥
 ，并添加 𝑥
 到该段 [𝑙,𝑟)
 。
We will store the maximum on the segment at each node of the segment tree. If the maximum in the left child is greater than or equal to 𝑥
, then we go to the left child, otherwise if the maximum on the right is greater than or equal to 𝑥
 and there is no answer in the left child, then we go to the right child. As you can see, mass operations does not practically change the underlying algorithm.
我们将在线段树的每个节点处存储线段的最大值。如果左孩子的最大值大于或等于 𝑥
 ，然后我们转到左边的孩子，否则如果右边的最大值大于或等于 𝑥
 左边的孩子没有答案，那么我们就去找右边的孩子。正如您所看到的，批量操作实际上并没有改变底层算法。