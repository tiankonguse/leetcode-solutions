Binary Search for Answer  二分查找答案
Let's solve the following problem — all numbers are divided into good and bad. If 𝑥
 is good, then 𝑥+1
 is also good. Find the minimum good number.
让我们解决以下问题——所有数字都分为好数和坏数。如果 𝑥
 很好，那么 𝑥+1
 也不错。找出最小的好数。
In real problems, this means that there is some function that determines whether it is good or bad by a number.
在实际问题中，这意味着存在某种函数通过数字来确定它的好坏。

Let's create a function 𝑓
, which for the number 𝑥
 will return 1
, if 𝑥
 — is a good number, otherwise 0
.
让我们创建一个函数 𝑓
 ，对于数字 𝑥
 会回来 1
 ， 如果 𝑥
 — 是一个好数字，否则 0
 。

𝑓(𝑥)={1,0,𝑥−good number,otherwise

Let's set two pointers 𝑙
 and 𝑟
 so that 𝑙
 points to a bad number and 𝑟
 to a good one. That is, 𝑓(𝑙)=0
 and 𝑓(𝑟)=1
. If there are no such numbers, then as in the last lesson, we will create a fictitious number for which the invariant will be fulfilled.
让我们设置两个指针 𝑙
 和 𝑟
 以便 𝑙
 指向一个错误的数字并且 𝑟
 到一个好人。那是， 𝑓(𝑙)=0
 和 𝑓(𝑟)=1
 。如果没有这样的数字，那么就像上一课一样，我们将创建一个虚构的数字来满足不变量。

Until the pointers 𝑙
 and 𝑟
 point to adjacent numbers, we will do the following:
直到指点为止 𝑙
 和 𝑟
 指向相邻的数字，我们将执行以下操作：

Set 𝑚
 equal to 𝑙+𝑟2
;
放 𝑚
 等于 𝑙+𝑟2
 ;
If 𝑓(𝑚)=1
, then 𝑚
 is a good number, therefore, replace 𝑟
 with 𝑚
;
如果 𝑓(𝑚)=1
 ， 然后 𝑚
 是一个很好的数字，因此，替换 𝑟
 和 𝑚
 ;
Otherwise, 𝑓(𝑚)=0
, hence 𝑚
 is a bad number, so replace 𝑙
 with 𝑚
.
否则， 𝑓(𝑚)=0
 ， 因此 𝑚
 是一个错误的数字，所以更换 𝑙
 和 𝑚
 。

This algorithm also works for the complexity of calculating the function 𝑓
 per logarithm of the distance between 𝑟
 and 𝑙
, that is, for (𝑇(𝑓)⋅log(𝑟−𝑙))
, where 𝑇(𝑓)
 — is the computational complexity of the function 𝑓
. At each step, we calculate the value of the function 𝑓
 at the point 𝑚
, and then shift one of the boundaries to the middle of the segment.
该算法也适用于计算函数的复杂性 𝑓
 每个之间的距离的对数 𝑟
 和 𝑙
 ，即对于 (𝑇(𝑓)⋅log(𝑟−𝑙))
 ， 在哪里 𝑇(𝑓)
 — 是函数的计算复杂度 𝑓
 。在每一步，我们计算函数的值 𝑓
 在这一点上 𝑚
 ，然后将边界之一移动到线段的中间。

Let's consider the application of this algorithm for the following problem.
让我们考虑一下该算法在以下问题中的应用。

Given 𝑛
 identical rectangles of size 𝑎×𝑏
. You need to find a square of the minimum area in which all 𝑛
 rectangles can be placed. Rectangles can touch along a point or side, but they cannot intersect. Rectangles cannot be rotated.
给定 𝑛
 大小相同的矩形 𝑎×𝑏
 。你需要找到一个最小面积的正方形，其中所有 𝑛
 可以放置矩形。矩形可以沿点或边相交，但不能相交。矩形不能旋转。

Then 𝑓(𝑥)=1
 if all 𝑛
 rectangles can be placed in a square with side 𝑥
. It is easy to see that the function 𝑓
 is monotone, since if all rectangles can be placed in a square with side 𝑥
, then they can also be placed in a square with side 𝑥+1
, since the square has become larger.
然后 𝑓(𝑥)=1
 如果全部 𝑛
 长方形可以放入有边的正方形中 𝑥
 。很容易看出函数 𝑓
 是单调的，因为如果所有矩形都可以放置在有边的正方形中 𝑥
 ，那么它们也可以放置在有边的正方形中 𝑥+1
 ，因为正方形变大了。

It can be shown that one of the optimal spacing of rectangles within a square is the following:
可以证明，正方形内矩形的最佳间距之一如下：


To count the number of rectangles that fit into the 𝑥×𝑥
 square, multiply the number of rectangles that fit on the first side — ⌊𝑥𝑎⌋
, and the number of rectangles that are placed on the second side — ⌊𝑥𝑏⌋
. The resulting formula is ⌊𝑥𝑎⌋⋅⌊𝑥𝑏⌋
.
计算适合的矩形的数量 𝑥×𝑥
 正方形，乘以适合第一条边的矩形数量 - ⌊𝑥𝑎⌋
 ，以及放置在第二条边上的矩形的数量 - ⌊𝑥𝑏⌋
 。得到的公式是 ⌊𝑥𝑎⌋⋅⌊𝑥𝑏⌋
 。

It's easy to see that we've explicitly expressed the function 𝑓
:
很容易看出我们已经明确地表达了该函数 𝑓
 ：
𝑓(𝑥)={1,0,if ⌊𝑥𝑎⌋⋅⌊𝑥𝑏⌋≥𝑛,otherwise

Now, to solve the problem, it remains to do a binary search for 𝑥
. This method allows you to solve a large class of problems in which the function 𝑓
 is monotone.
现在，要解决这个问题，仍然需要进行二分搜索 𝑥
 。这种方法可以让你解决一大类问题，其中函数 𝑓
 是单调的。

Rope Problem  绳子问题
Let's look at one more problem — the rope problem.
我们再来看一个问题——绳子问题。
We have 𝑛
 ropes, the length of the 𝑖
-th rope is 𝑎𝑖
. We want to cut 𝑘
 pieces of the same length out of them. Of all the cutting methods, you need to choose the one in which the length of the cut pieces is maximum.
我们有 𝑛
 绳索的长度， 𝑖
 第 - 根绳子是 𝑎𝑖
 。我们想剪 𝑘
 从中取出相同长度的碎片。在所有切割方法中，您需要选择切割件长度最大的一种。

To solve this problem, let's make the following function — 𝑓(𝑥)
 = is it possible to cut out 𝑘
 pieces of length 𝑥
. This function behaves almost the same as in the previous problem, but there are some differences.
为了解决这个问题，让我们创建以下函数 - 𝑓(𝑥)
 = 可以剪掉吗 𝑘
 长度的片断 𝑥
 。该函数的行为与上一个问题几乎相同，但也存在一些差异。

If we can cut pieces of length 𝑥
, then we can cut pieces of smaller size (since they need less length). That is, in binary search, you need to swap zeros and ones in order to transform the function to the general algorithm.
如果我们能切割一定长度的碎片 𝑥
 ，那么我们可以切割更小的尺寸（因为它们需要更短的长度）。也就是说，在二分查找中，您需要交换 0 和 1，以便将函数转换为通用算法。
The function now accepts not integer values, but real ones. Sometimes it is beneficial to cut off pieces of non-integer size (for example, if there is only one rope of length 1
 and it needs to be cut into three pieces, then the answer to the problem is 13
.
该函数现在不接受整数值，而是接受实数。有时，切断非整数尺寸的碎片是有益的（例如，如果只有一根长度为 1
 并且需要将其切成三块，那么问题的答案是 13
 。
How to solve the second problem? Let's remember what binary search looked like before. We repeated the cycle until 𝑙
 and 𝑟
 are adjacent numbers. But with real numbers, this trick will not work, since there are no neighboring real numbers.
第二个问题如何解决？让我们回想一下二分查找以前的样子。我们重复这个循环直到 𝑙
 和 𝑟
 是相邻的数字。但对于实数，这个技巧不起作用，因为没有相邻的实数。

Therefore, such tasks can be solved with certain accuracy (it is usually indicated in the conditions). It is necessary to continue the loop as long as the segment [𝑙,𝑟]
 has a length greater than the required precision.
因此，此类任务可以以一定的精度解决（通常在条件中注明）。只要该段存在，就必须继续循环 [𝑙,𝑟]
 长度大于所需的精度。

However, this algorithm also has a problem, it can get stuck. This will happen if the numbers 𝑙
 and 𝑟
 are adjacent in the type 𝑑𝑜𝑢𝑏𝑙𝑒
. Since 𝑑𝑜𝑢𝑏𝑙𝑒
 stores numbers not with arbitrary precision, but only a certain number of digits, then if the numbers 𝑙
 and 𝑟
 are adjacent, then the middle between them will not be found and it will be equal to either 𝑙
 or 𝑟
 and the algorithm will run infinitely. This problem appears if the answer is large and the required precision is high enough.
然而，这个算法也有一个问题，它可能会卡住。如果数字会发生这种情况 𝑙
 和 𝑟
 在类型中相邻 𝑑𝑜𝑢𝑏𝑙𝑒
 。自从 𝑑𝑜𝑢𝑏𝑙𝑒
 不以任意精度存储数字，而仅存储一定数量的数字，那么如果数字 𝑙
 和 𝑟
 相邻，那么将找不到它们之间的中间，并且它将等于其中之一 𝑙
 或者 𝑟
 并且算法将无限运行。如果答案很大并且所需的精度足够高，就会出现此问题。

The easiest way to deal with this is not to use a 𝑤ℎ𝑖𝑙𝑒
 loop, but a 𝑓𝑜𝑟
 loop with a sufficiently large number of iterations (you need at least log𝑚𝑎𝑥𝐴𝑛𝑠𝑒𝑝𝑠
, where 𝑚𝑎𝑥𝐴𝑛𝑠
 — the maximum possible answer, and 𝑒𝑝𝑠
 — the required precision). Usually, you can always write 100
 iterations and not think.
解决这个问题最简单的方法是不使用 𝑤ℎ𝑖𝑙𝑒
 循环，但是一个 𝑓𝑜𝑟
 具有足够多迭代次数的循环（您至少需要 log𝑚𝑎𝑥𝐴𝑛𝑠𝑒𝑝𝑠
 ， 在哪里 𝑚𝑎𝑥𝐴𝑛𝑠
 — 最大可能的答案，以及 𝑒𝑝𝑠
 — 所需的精度）。通常，你可以随时写 100
 迭代而不去思考。

The function 𝑓(𝑥)
 itself should simply go through all ropes, divide their lengths by 𝑥
, and round the resulting number down. That is how many pieces of length 𝑥
 we can cut. If the sum of all these numbers is not less than 𝑘
, then you need to return 1
, otherwise 0
. It should be noted that the 𝑓
 function is not fast. It spends (𝑛)
 operations, where 𝑛
 — is the length of the array. The total complexity will be (𝑛⋅log1𝑒𝑝𝑠)
.
功能 𝑓(𝑥)
 本身应该简单地穿过所有绳索，将它们的长度除以 𝑥
 ，并将结果数字向下舍入。也就是多少块长度 𝑥
 我们可以削减。如果所有这些数字的总和不小于 𝑘
 ，那么你需要返回 1
 ， 否则 0
 。应该指出的是， 𝑓
 功能不快。它花费 (𝑛)
 操作，其中 𝑛
 — 是数组的长度。总复杂度将为 (𝑛⋅log1𝑒𝑝𝑠)
 。