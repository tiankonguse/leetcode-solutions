Typical Tasks  典型任务

https://codeforces.com/edu/course/2/lesson/4/3

Inversions  倒转
A permutation 𝑝
 of 𝑛
 elements is given. You need to find for each element the number of inversions: the number of elements to the left, which are greater. It is solved quite simply. We construct an empty segment tree of size 𝑛
 with the operation 𝑠𝑢𝑚
. Now go through the permutation elements from left to right. A one in a leaf of a tree of segments will mean that such an element was already visited. When moving to the 𝑖
-th element of 𝑝[𝑖]
, we will make a request to calculate the sum of [𝑝[𝑖],𝑛]
 in the segment tree: it will just count the number of elements to the left which are greater than 𝑝[𝑖]
. And finally, put one in position 𝑝[𝑖]
. The total time is 𝑂(𝑛log𝑛)
.
一个排列 𝑝
 的 𝑛
 给出了元素。您需要找到每个元素的反转次数：左侧较大的元素数量。解决起来非常简单。我们构造一个大小为的空线段树 𝑛
 随着操作 𝑠𝑢𝑚
 。现在从左到右浏览排列元素。段树的叶子中的一个意味着已经访问过这样的元素。当搬到 𝑖
 第-个元素 𝑝[𝑖]
 ，我们将请求计算总和 [𝑝[𝑖],𝑛]
 在线段树中：它只会计算左侧大于的元素数量 𝑝[𝑖]
 。最后，将其放置到位 𝑝[𝑖]
 。总时间是 𝑂(𝑛log𝑛)
 。

Inversions 2  倒立 2

Array of inversions 𝑎
 is given. You need to restore the permutation 𝑝
. Let's build a segment tree of size 𝑛
, which is filled with ones, and is able to respond to the request 𝑘
-th one from the end. (finding the 𝑘
-th one from the end is similar to the task of finding the 𝑘
-th one from the beginning from step 2) Now, let's process the elements from right to left. A one in a leaf of a segment tree will mean that an element with this value is to the left. When moving to the 𝑖
-th element, we will look for the 𝑎[𝑖]
-th one from the right: this just means that there will 𝑎[𝑖]
 greater elements to the left of the 𝑖
-th position. Finally, put 0
 in the found position, i.e. remove the element from consideration. The total time is 𝑂(𝑛log𝑛)
.
反转数组 𝑎
 被给出。您需要恢复排列 𝑝
 。让我们构建一个大小的线段树 𝑛
 ，其中填满了，并且能够响应请求 𝑘
 - 从最后算起第一个。 （找到 𝑘
 倒数第 - 一个类似于寻找 𝑘
 - 从步骤 2 开始的第一个）现在，让我们从右到左处理元素。线段树的叶子中的 1 意味着具有该值的元素位于左侧。当搬到 𝑖
 -th 元素，我们将寻找 𝑎[𝑖]
 - 右数第一个：这只是意味着将会有 𝑎[𝑖]
 左边更大的元素 𝑖
 第-个位置。最后，放 0
 在找到的位置，即从考虑中删除该元素。总时间是 𝑂(𝑛log𝑛)
 。

Nested Segments  嵌套段

We are given an array of length 2𝑛
 where each number from 1 to 𝑛
 occurs exactly two times. Two occurrences of a number indicate the segment between two positions. Task: for each segment, it is necessary to calculate the number of nested segments. In other words, for each 𝑥
 count the number 𝑦
 such that two occurrences of 𝑦
 lie between two occurrences of 𝑥
. We will process the elements from left to right. Note that for the segment 𝑥
, the answer is the number of segments that have already been fully considered (both ends on the left), and those with the left end lying between 𝑥
 s.
我们得到一个长度的数组 2𝑛
 其中每个数字从 1 到 𝑛
 恰好发生两次。数字出现两次表示两个位置之间的段。任务：对于每个段，需要计算嵌套段的数量。换句话说，对于每个 𝑥
 数数 𝑦
 使得两次出现 𝑦
 位于两次出现之间 𝑥
 。我们将从左到右处理元素。请注意，对于段 𝑥
 ，答案是已经充分考虑的线段数（两端都在左边），以及左端位于之间的线段数 𝑥
 s。

The algorithm is as follows. Consider the number 𝑥
. If we consider the left end of the segment, then we do nothing. Otherwise, we consider the number of nested segments between two 𝑥
. Note that for this it is enough for us to store for each fully considered segment one in the tree of segments at the position of its left end. Then the number of nested segments between 𝑥
 will be equal to the sum on the corresponding segment. When the amount is calculated, put the one at the left end of the segment 𝑥
. The total time is 𝑂(𝑛log𝑛)
.
算法如下。考虑数量 𝑥
 。如果我们考虑线段的左端，那么我们什么也不做。否则，我们考虑两个之间的嵌套段数 𝑥
 。请注意，为此，我们为每个经过充分考虑的段在段树的左端位置存储一个就足够了。然后之间的嵌套段数 𝑥
 将等于相应段上的总和。计算金额时，将其放在该段的左端 𝑥
 。总时间是 𝑂(𝑛log𝑛)
 。

Intersecting segments  相交线段

Again we are given an array of length 2𝑛
. Two occurrences of each number indicate the segment between two positions. Task: for each segment, it is necessary to calculate the number of segments intersecting with it. In other words, for each 𝑥
, calculate the number 𝑦
 such that 𝑦
 is between two 𝑥
 and 𝑥
 is between two 𝑦
. The line segments 𝑥
 and 𝑦
 can intersect in two ways: 𝑥…𝑦…𝑥…𝑦
 and 𝑦…𝑥…𝑦…𝑥
. Let's calculate for each 𝑥
 the number of 𝑦
 segments of the first type. Then we reverse the array and in the same way we calculate the number of segments 𝑦
 of the second type. The sum of these two values ​​will be our answer. We will process the elements from left to right. Note that for the segment 𝑥
 the answer is the number of segments that are not completely considered (only the left end is considered), and those in which the left end lies between the 𝑥
.
我们再次得到一个长度的数组 2𝑛
 。每个数字出现两次表示两个位置之间的段。任务：对于每条线段，需要计算与其相交的线段数量。换句话说，对于每个 𝑥
 , 计算数量 𝑦
 这样 𝑦
 是在两个之间 𝑥
 和 𝑥
 是在两个之间 𝑦
 。线段 𝑥
 和 𝑦
 可以通过两种方式相交： 𝑥…𝑦…𝑥…𝑦
 和 𝑦…𝑥…𝑦…𝑥
 。我们来计算一下每个 𝑥
 的数量 𝑦
 第一种类型的段。然后我们反转数组并以同样的方式计算段数 𝑦
 属于第二种类型。这两个值的总和就是我们的答案。我们将从左到右处理元素。请注意，对于段 𝑥
 答案是没有完全考虑的线段数（只考虑左端），以及左端位于 𝑥
 。

The algorithm is as follows. Consider the number 𝑥
. If we consider the left end of the segment, then put the one in this position. Otherwise, we consider the sum between the 𝑥
 and set the zero to the left end of the segment 𝑥
. The total time is 𝑂(𝑛log𝑛)
.
算法如下。考虑数量 𝑥
 。如果我们考虑该段的左端，则将其放在该位置。否则，我们考虑之间的总和 𝑥
 并将零设置为该段的左端 𝑥
 。总时间是 𝑂(𝑛log𝑛)
 。