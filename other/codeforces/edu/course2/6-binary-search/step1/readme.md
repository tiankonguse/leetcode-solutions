Binary Search  二分查找
Today we will learn one of the most popular techniques in competitive programming — binary search.
今天我们将学习竞争性编程中最流行的技术之一——二分搜索。
Searching an item in an array
搜索数组中的项目

Suppose we have an array 𝑎=[𝑎1,𝑎2,…,𝑎𝑛]
, sorted in non-decreasing order. That is, the inequality 𝑎𝑖≤𝑎𝑖+1
 is satisfied for the neighboring elements of the array. We need to quickly search for the position of the element 𝑥
 in the array, that is, we need to find such 𝑖
, then 𝑎𝑖=𝑥
.
假设我们有一个数组 𝑎=[𝑎1,𝑎2,…,𝑎𝑛]
 ，按非降序排列。也就是说，不等式 𝑎𝑖≤𝑎𝑖+1
 数组的相邻元素都满足。我们需要快速查找元素的位置 𝑥
 在数组中，也就是说，我们需要找到这样的 𝑖
 ， 然后 𝑎𝑖=𝑥
 。

How would we search for the position of 𝑥
? If you go from left to right through the array 𝑎
, then this will work in (𝑛)
 time, which is inefficient for a large array.
我们将如何搜索位置 𝑥
 ？如果从左到右遍历数组 𝑎
 ，那么这将适用于 (𝑛)
 时间，这对于大型数组来说效率很低。

How to make it faster? Let's take advantage of the fact that the 𝑎
 array is sorted. If we found out that for some 𝑗
 it is true that 𝑎𝑗>𝑥
, then the inequality will hold for all 𝑘>𝑗
. Until the array consists of one element, we will proceed as follows:
如何让它更快？让我们利用以下事实： 𝑎
 数组已排序。如果我们发现对于某些人来说 𝑗
 确实如此 𝑎𝑗>𝑥
 ，那么不等式对于所有人都成立 𝑘>𝑗
 。直到数组包含一个元素为止，我们将继续如下操作：

let's look at the element that is in the middle of the array,
让我们看看数组中间的元素，
if it is greater than 𝑥
, then we cut off all elements to the right of it, otherwise, we cut off all elements to the left of it.
如果它大于 𝑥
 ，那么我们就剪掉它右边的所有元素，否则，我们剪掉它左边的所有元素。
At the end of this procedure, we will have exactly one element in the array, which will either be equal to 𝑥
 or not equal to 𝑥
.
在此过程结束时，数组中将只有一个元素，该元素要么等于 𝑥
 或不等于 𝑥
 。

For example, for the array 𝑎=[3,5,8,13,18,19,21,27,32]
 and 𝑥=13
, the algorithm will be executed as follows:
例如，对于数组 𝑎=[3,5,8,13,18,19,21,27,32]
 和 𝑥=13
 ，算法将执行如下：


We consider the segment [𝑙,𝑟]=[1,9]
, the middle element is at the position 𝑙+𝑟2=5
.
我们考虑该细分市场 [𝑙,𝑟]=[1,9]
 ，中间元素位于位置 𝑙+𝑟2=5
 。



We consider the segment [𝑙,𝑟]=[1,4]
, the middle element is at the position 𝑙+𝑟2=3
.
我们考虑该细分市场 [𝑙,𝑟]=[1,4]
 ，中间元素位于位置 𝑙+𝑟2=3
 。



We consider the segment [𝑙,𝑟]=[3,4]
, the middle element is at the position 𝑙+𝑟2=4
.
我们考虑该细分市场 [𝑙,𝑟]=[3,4]
 ，中间元素位于位置 𝑙+𝑟2=4
 。

Why do we find the position of the element 𝑥
 using this method (if it occurs in the array)? This follows from the sorted array. At each step, we remove from consideration the part of the array containing elements greater or less than 𝑥
.
为什么我们要找到元素的位置 𝑥
 使用此方法（如果它出现在数组中）？这是从排序数组得出的。在每一步中，我们都会从考虑中删除数组中包含大于或小于的元素的部分 𝑥
 。

Why is it faster than a linear search? At each step of the algorithm, we reduce the length of the segment under consideration by 2
 times, therefore, the steps of the algorithm will be done no more than log2𝑛
. Thus, we got an algorithm that runs in (log𝑛)
 time.
为什么它比线性搜索更快？在算法的每一步，我们都会通过以下方式减少所考虑的段的长度： 2
 次，因此，算法的步骤将不超过 log2𝑛
 。因此，我们得到了一个运行在 (log𝑛)
 时间。

Find closest in array  查找数组中最接近的

Let's learn how to solve the following problem — in a sorted array, you need to quickly find the element closest to the number 𝑥
 (𝑥
 changes from query to query).
让我们学习如何解决以下问题——在排序数组中，您需要快速找到最接近数字的元素 𝑥
 （ 𝑥
 查询之间的变化）。

If we needed to find an element exactly equal to 𝑥
, then we could use a hash table. But if there is no 𝑥
 element in the array, then the hash table will simply indicate this. In this case, we need to solve the following two tasks:
如果我们需要找到一个完全等于的元素 𝑥
 ，那么我们可以使用哈希表。但如果没有 𝑥
 数组中的元素，那么哈希表将简单地指示这一点。在这种情况下，我们需要解决以下两个任务：

Find the maximum element not greater than 𝑥
 (closest to 𝑥
 on the left)
找出不大于的最大元素 𝑥
 （最接近 𝑥
 在左侧）
Find the minimum element not less than 𝑥
 (closest to 𝑥
 on the right)
求不小于的最小元素 𝑥
 （最接近 𝑥
 在右侧）
Choosing from these two options the one that is closer to the number 𝑥
, we will solve the problem (since all the elements to the left and to the right will only be further from 𝑥
).
从这两个选项中选择最接近数字的一个 𝑥
 ，我们将解决这个问题（因为左边和右边的所有元素只会距离更远 𝑥
 ）。

Consider a binary search algorithm for solving the first problem (maximum element not greater than 𝑥
).
考虑使用二分搜索算法来解决第一个问题（最大元素不大于 𝑥
 ）。

We are given an array 𝑎=[𝑎0,𝑎1,…,𝑎𝑛−1]
. Let's create two pointers 𝑙
 and 𝑟
. They will be responsible for the boundaries of the segment under consideration. We will maintain the invariant that 𝑎𝑙≤𝑥
 and 𝑎𝑟>𝑥
. We put 𝑙
 and 𝑟
 so that the invariant holds. To do this, add −∞
 to the beginning of the array (the index of this infinity will be −1
), and to the end of the array +∞
 (the index of this infinity will be 𝑛
). Then set 𝑙
 to −1
 and 𝑟
 to 𝑛
. Obviously, the invariant is satisfied.
我们得到一个数组 𝑎=[𝑎0,𝑎1,…,𝑎𝑛−1]
 。让我们创建两个指针 𝑙
 和 𝑟
 。他们将负责所考虑的部分的边界。我们将保持不变式 𝑎𝑙≤𝑥
 和 𝑎𝑟>𝑥
 。我们把 𝑙
 和 𝑟
 使得不变量成立。为此，请添加 −∞
 到数组的开头（这个无穷大的索引将是 −1
 )，并到数组末尾 +∞
 （这个无穷大的索引将是 𝑛
 ）。然后设置 𝑙
 到 −1
 和 𝑟
 到 𝑛
 。显然，满足不变量。

We will execute the following algorithm until 𝑙+1<𝑟
 (until the pointers converge):
我们将执行以下算法直到 𝑙+1<𝑟
 （直到指针收敛）：

Let 𝑚
 — be the index of the midpoint of the segment [𝑙,𝑟]
;
让 𝑚
 — 为线段中点的索引 [𝑙,𝑟]
 ;
If 𝑎𝑚≤𝑥
 then put 𝑙=𝑚
. All elements to the left of 𝑚
 are less than 𝑎𝑚
;
如果 𝑎𝑚≤𝑥
 然后把 𝑙=𝑚
 。左边的所有元素 𝑚
 小于 𝑎𝑚
 ;
If 𝑎𝑚>𝑥
 then put 𝑟=𝑚
. All elements to the right of 𝑚
 are greater than 𝑎𝑚
.
如果 𝑎𝑚>𝑥
 然后把 𝑟=𝑚
 。右侧的所有元素 𝑚
 大于 𝑎𝑚
 。
Let's take an example 𝑎=[3,5,10,11,13,18,25,27,31]
, 𝑥=20
.
让我们举个例子 𝑎=[3,5,10,11,13,18,25,27,31]
 , 𝑥=20
 。

Since 𝑥=20
 is greater than 𝑎𝑚=13
, then 𝑙=𝑚

自从 𝑥=20
 大于 𝑎𝑚=13
 ， 然后 𝑙=𝑚
Since 𝑥=20
 is less than 𝑎𝑚=25
, then 𝑟=𝑚

自从 𝑥=20
 小于 𝑎𝑚=25
 ， 然后 𝑟=𝑚
Since 𝑥=20
 is greater than 𝑎𝑚=18
, then 𝑙=𝑚

自从 𝑥=20
 大于 𝑎𝑚=18
 ， 然后 𝑙=𝑚
Pointers converged  指针收敛
Since the invariant is satisfied, then 𝑎𝑙≤𝑥
, and 𝑎𝑟>𝑥
, in this case, 𝑙
 is the maximum of such indices, and 𝑟
 is the minimum.
由于满足不变量，则 𝑎𝑙≤𝑥
 ， 和 𝑎𝑟>𝑥
 ， 在这种情况下， 𝑙
 是此类指数的最大值，并且 𝑟
 是最小值。

It remains only to choose from the elements 𝑎𝑙
 and 𝑎𝑟
 the one that is closer to 𝑥
. In this example, it is 18
.
剩下的只是从元素中进行选择 𝑎𝑙
 和 𝑎𝑟
 更接近的那个 𝑥
 。在这个例子中，它是 18
 。

What happens in special cases?
特殊情况下会发生什么？

If all items are greater than 𝑥
, then 𝑙=−1
.
如果所有项目都大于 𝑥
 ， 然后 𝑙=−1
 。
If all items are less than 𝑥
, then 𝑟=𝑛
.
如果所有项目都小于 𝑥
 ， 然后 𝑟=𝑛
 。
But since we set these elements equal to ±∞
, the correctness the algorithm will not be violated.
但由于我们将这些元素设置为等于 ±∞
 ，算法的正确性不会被违反。