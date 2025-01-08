Maximum Average  最大平均值
Another interesting class of problems that are solved by binary search is this: we have some set, we need to choose a subset that has some properties, and in this subset, we need to maximize/minimize the arithmetic mean of the elements.
二分搜索解决的另一类有趣的问题是：我们有一些集合，我们需要选择一个具有某些属性的子集，并且在这个子集中，我们需要最大化/最小化元素的算术平均值。
Suppose we have an array 𝑎=[𝑎0,𝑎1,…,𝑎𝑛−1]
. We need to find a segment [𝑙,𝑟]
 of length at least 𝐷
 such that
假设我们有一个数组 𝑎=[𝑎0,𝑎1,…,𝑎𝑛−1]
 。我们需要找到一个段 [𝑙,𝑟]
 至少长度 𝐷
 这样
∑𝑖=𝑙𝑟−1𝑎𝑖𝑟−𝑙→max

That is, it is necessary to find such a segment of length at least 𝐷
 that the arithmetic mean of the numbers on it is maximum.
也就是说，需要找到这样一段长度至少为 𝐷
 其上数字的算术平均值最大。

We will do a binary search by the answer (arithmetic mean). Now, for fixed arithmetic mean 𝑥
, it is necessary to check whether there is a segment [𝑙,𝑟]
 on which the arithmetic mean is not less than 𝑥
. That is, it is necessary to check whether there is such a segment [𝑙,𝑟]
 that the inequality holds for it:
我们将根据答案（算术平均值）进行二分搜索。现在，对于固定算术平均值 𝑥
 ，需要检查是否存在段 [𝑙,𝑟]
 其算术平均值不小于 𝑥
 。即需要检查是否存在这样的段 [𝑙,𝑟]
 不等式成立：
∑𝑖=𝑙𝑟−1𝑎𝑖𝑟−𝑙≥𝑥

How are we going to do this? We transform the inequality. Let's multiply both sides by 𝑟−𝑙
. Then we get that ∑𝑖=𝑙𝑟−1𝑎𝑖≥𝑥⋅(𝑟−𝑙)
. Note that there are exactly 𝑟−𝑙
 on the left-hand side of the terms, which coincides with the factor of 𝑥
. Subtract 𝑥
 from each 𝑎𝑖
 from the left side. Then we get the following inequality: (𝑎𝑙−𝑥)+(𝑎𝑙+1−𝑥)+…+(𝑎𝑟−1−𝑥)≥0
. Now the problem is reduced to the fact that we replace each 𝑎𝑖
 by 𝑎𝑖−𝑥
 and try to find a segment of length at least 𝐷
 with a non-negative sum.
我们要怎么做呢？我们改变不平等。我们将两边都乘以 𝑟−𝑙
 。然后我们就得到了 ∑𝑖=𝑙𝑟−1𝑎𝑖≥𝑥⋅(𝑟−𝑙)
 。请注意，正好有 𝑟−𝑙
 在项的左侧，这与因子一致 𝑥
 。减去 𝑥
 从每个 𝑎𝑖
 从左侧。然后我们得到以下不等式： (𝑎𝑙−𝑥)+(𝑎𝑙+1−𝑥)+…+(𝑎𝑟−1−𝑥)≥0
 。现在问题就简化为我们替换每个 𝑎𝑖
 经过 𝑎𝑖−𝑥
 并尝试找到长度至少为 𝐷
 具有非负和。

Let's learn how to quickly find such a segment. The sum of numbers on a segment is the difference of prefix sums. Let's calculate the array of prefix sums 𝑝
.
让我们学习如何快速找到这样的细分。段上的数字之和是前缀和的差。让我们计算前缀和数组 𝑝
 。

𝑝𝑖=∑𝑗=0𝑖−1(𝑎𝑗−𝑥)

It is easy to see that 𝑎𝑙+𝑎𝑙+1+…+𝑎𝑟−1=𝑝𝑟−𝑝𝑙
. Combining the condition of non-negativity of the sum and the minimum length of the required segment, we obtain the following system:
很容易看出 𝑎𝑙+𝑎𝑙+1+…+𝑎𝑟−1=𝑝𝑟−𝑝𝑙
 。结合和非负的条件以及所需线段的最小长度，我们得到如下系统：

{𝑝𝑟−𝑝𝑙≥0𝑟−𝑙≥𝐷⇒{𝑝𝑙≤𝑝𝑟𝑙≤𝑟−𝐷

These conditions mean that on the prefix [0,𝑟−𝐷]
 there must be a prefix amount not greater than the current one. Note that if the minimum amount on the prefix [𝑙,𝑟−𝐷]
 is greater than 𝑝𝑟
, then any other amount will also be greater. Therefore, it makes sense to compare only the minimum prefix amount with the current one. To do this, let's calculate one more array 𝑚
 — an array of minimum of prefix sums: 𝑚𝑖=𝑚𝑖𝑛(𝑝0,𝑝1,…,𝑝𝑖)=𝑚𝑖𝑛(𝑚𝑖−1,𝑝𝑖)
. Now the original system has been transformed into one condition:
这些条件意味着在前缀上 [0,𝑟−𝐷]
 必须有一个不大于当前前缀数量的前缀。请注意，如果前缀上的最小金额 [𝑙,𝑟−𝐷]
 大于 𝑝𝑟
 ，那么任何其他金额也会更大。因此，仅将最小前缀数量与当前前缀数量进行比较是有意义的。为此，我们再计算一个数组 𝑚
 — 最小前缀和的数组： 𝑚𝑖=𝑚𝑖𝑛(𝑝0,𝑝1,…,𝑝𝑖)=𝑚𝑖𝑛(𝑚𝑖−1,𝑝𝑖)
 。现在原来的系统已经改造成一种情况：
{𝑝𝑙≤𝑝𝑟𝑙≤𝑟−𝐷⇒𝑚𝑟−𝐷≤𝑝𝑟

Thus, we have solved the problem in (𝑛log𝐴𝑛𝑠)
.  
因此，我们已经解决了这个问题 (𝑛log𝐴𝑛𝑠)
 。