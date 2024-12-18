Finding LCP 寻找LCP
Finding LCP of two suffixes
查找两个后缀的LCP
To solve more complex problems, we need a little more information, namely, we need to learn how to quickly calculate the value of 𝐿𝐶𝑃(𝑖,𝑗)
, the length of the largest common prefix for suffixes starting at 𝑖
 and 𝑗
.
为了解决更复杂的问题，我们需要更多的信息，即我们需要学习如何快速计算 𝐿𝐶𝑃(𝑖,𝑗)
 ，从以下位置开始的后缀的最大公共前缀的长度 𝑖
 和 𝑗
 。

To do this, for each pair of adjacent suffixes in the suffix array, find the length of their largest common prefix and put them in the array 𝑙𝑐𝑝[𝑖]=𝐿𝐶𝑃(𝑝[𝑖],𝑝[𝑖+1])
. For example, for the string that we used in the first step, we get such an array.
为此，对于后缀数组中的每对相邻后缀，找到它们最大公共前缀的长度并将它们放入数组中 𝑙𝑐𝑝[𝑖]=𝐿𝐶𝑃(𝑝[𝑖],𝑝[𝑖+1])
 。例如，对于我们在第一步中使用的字符串，我们得到这样一个数组。



Now, in order to find the LCP of any two suffixes, we just need to find their positions in the suffix array and calculate the minimum in the 𝑙𝑐𝑝
 array on the segment between them. 𝐿𝐶𝑃(𝑖,𝑗)=min(𝑙𝑐𝑝[𝑝𝑜𝑠[𝑖]..𝑝𝑜𝑠[𝑗]−1])
, where 𝑝𝑜𝑠[𝑖]
 is the position of the suffix 𝑖
 in the suffix array.
现在，为了找到任意两个后缀的LCP，我们只需要找到它们在后缀数组中的位置并计算后缀中的最小值 𝑙𝑐𝑝
 数组位于它们之间的段上。 𝐿𝐶𝑃(𝑖,𝑗)=min(𝑙𝑐𝑝[𝑝𝑜𝑠[𝑖]..𝑝𝑜𝑠[𝑗]−1])
 ， 在哪里 𝑝𝑜𝑠[𝑖]
 是后缀的位置 𝑖
 在后缀数组中。

Why is this true? Let's look at some two suffixes 𝑖
 and 𝑗
. Let 𝑘=𝐿𝐶𝑃(𝑖,𝑗)
, that is, the suffixes 𝑖
 and 𝑗
 have 𝑘
 common characters in the beginning. Since the suffixes are sorted, in all suffixes between them the first 𝑘
 characters must also be the same. So all 𝑙𝑐𝑝
 on this segment is not less than 𝑘
, and therefore the minimum on this segment is not less than 𝑘
. On the other hand, it cannot be greater than 𝑘
, since this means that each pair of suffixes has more than 𝑘
 common characters, which means that 𝑖
 and 𝑗
 must have more than 𝑘
 common characters.
为什么这是真的？让我们看一下两个后缀 𝑖
 和 𝑗
 。让 𝑘=𝐿𝐶𝑃(𝑖,𝑗)
 ，即后缀 𝑖
 和 𝑗
 有 𝑘
 开头的共同字符。由于后缀已排序，因此在它们之间的所有后缀中，第一个后缀 𝑘
 字符也必须相同。所以所有 𝑙𝑐𝑝
 在此段上不小于 𝑘
 ，因此该段的最小值不小于 𝑘
 。另一方面，它不能大于 𝑘
 ，因为这意味着每对后缀有超过 𝑘
 常见字符，这意味着 𝑖
 和 𝑗
 必须有超过 𝑘
 常见字符。

How do we quickly calculate the minimum on a segment of the 𝑙𝑐𝑝
 array? To do this, we can use one of two data structures: a segment tree or a sparse table. A segment tree is built in 𝑂(𝑛)
 and answers a query in 𝑂(log𝑛)
, a sparse table is built in 𝑂(𝑛log𝑛)
 and answers a query in 𝑂(1)
. Sparse tables are usually used, but a segment tree can also be useful in some specific task.
我们如何快速计算一段上的最小值 𝑙𝑐𝑝
 大批？为此，我们可以使用两种数据结构之一：线段树或稀疏表。内置线段树 𝑂(𝑛)
 并回答查询 𝑂(log𝑛)
 ，内置一个稀疏表 𝑂(𝑛log𝑛)
 并回答查询 𝑂(1)
 。通常使用稀疏表，但线段树在某些特定任务中也很有用。

Thus, if we have built an array 𝑙𝑐𝑝
, then the task of finding 𝐿𝐶𝑃
 for two suffixes reduces to find a minimum on a segment in array, it remains to learn how to build an array 𝑙𝑐𝑝
.
因此，如果我们构建了一个数组 𝑙𝑐𝑝
 ，那么寻找的任务 𝐿𝐶𝑃
 对于两个后缀约简以找到数组中段上的最小值，仍然需要学习如何构建数组 𝑙𝑐𝑝
 。

Building array lcp𝑙𝑐𝑝

建筑阵列 lcp 𝑙𝑐𝑝

To build the 𝑙𝑐𝑝
 array, we will use the algorithm of Kasai, Arimura, Arikawa, Lee and Park. The algorithm works as follows. We will iterate over the suffixes from longest to shortest, and for each find 𝐿𝐶𝑃
 with the previous one in the suffix array.
为了建立 𝑙𝑐𝑝
 数组，我们将使用 Kasai、Arimura、Arikawa、Lee 和 Park 的算法。该算法的工作原理如下。我们将从最长到最短的方式迭代后缀，并且对于每个查找 𝐿𝐶𝑃
 与后缀数组中的前一个。

For example, in our line, we first calculate the LCP for the suffixes 0 and 5 (it is 1), then for the suffixes 1 and 4 (it is 2).
例如，在我们的行中，我们首先计算后缀 0 和 5（它是 1）的 LCP，然后计算后缀 1 和 4（它是 2）。
And here we will do the trick: we know that the suffixes 1 and 4 have two common characters, which means that the suffixes 2 and 5 have one common character.
这里我们将使用一个技巧：我们知道后缀 1 和 4 有两个公共字符，这意味着后缀 2 和 5 有一个公共字符。
For all suffixes between 2 and 5, the first character must be the same, in particular, the suffix 2 with the previous one has at least one common character.
对于2到5之间的所有后缀，第一个字符必须相同，特别是后缀2与前一个后缀至少有一个共同字符。
Therefore, the first character of the suffixes 2 and 0 may be skipped, and we start the comparison immediately with the second character.
因此，后缀2和0的第一个字符可能会被跳过，我们立即开始与第二个字符进行比较。



In the general case, let the suffix 𝑗
 be in the suffix array before the suffix 𝑖
, and they have 𝑘>0
 common characters. Then the suffixes 𝑖+1
 and 𝑗+1
 have 𝑘−1
 common characters, so the suffix 𝑖+1
 has at least 𝑘−1
 common characters with the previous suffix. We can skip them and start the comparison with the 𝑘
-th character.
一般情况下，让后缀 𝑗
 位于后缀数组中后缀之前 𝑖
 ，并且他们有 𝑘>0
 常见字符。然后是后缀 𝑖+1
 和 𝑗+1
 有 𝑘−1
 常见字符，所以后缀 𝑖+1
 至少有 𝑘−1
 带有前面后缀的常见字符。我们可以跳过它们并开始与 𝑘
 第 - 个字符。

What is the time complexity of this algorithm? Let's see how many times we compare characters. If we compared the characters, and they were not equal, then we found the value of 𝑙𝑐𝑝
 and move on to the next suffix. This happens 𝑂(𝑛)
 times. If the characters are equal, then we increase the number of common characters 𝑘
. This number decreases by 1 when moving to the next suffix and cannot become more than 𝑛
, which means it increases no more than 2𝑛
 times. Thus, the total time of the algorithm is 𝑂(𝑛)
.
该算法的时间复杂度是多少？让我们看看我们比较了多少次角色。如果我们比较这些字符，并且它们不相等，那么我们发现的值 𝑙𝑐𝑝
 并继续下一个后缀。发生这种情况 𝑂(𝑛)
 次。如果字符相等，那么我们增加共同字符的数量 𝑘
 。当移动到下一个后缀时，该数字减 1，并且不能超过 𝑛
 ，这意味着它增加不超过 2𝑛
 次。因此，算法的总时间为 𝑂(𝑛)
 。