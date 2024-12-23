Example Problems  示例问题
Now that we have learned how to build a suffix array and how to find 𝐿𝐶𝑃
, let's solve two classic problems.
现在我们已经学习了如何构建后缀数组以及如何查找 𝐿𝐶𝑃
 ，让我们解决两个经典问题。
Number of different substrings
不同子串的数量

The first task is: given a string 𝑠
, you need to find the number of its different substrings.
第一个任务是：给定一个字符串 𝑠
 ，你需要找到它不同子串的数量。

Recall that any substring is a prefix of some suffix, so we need to calculate how many different prefixes the suffixes of the string 𝑠
 have. Let's iterate over the suffixes of the string 𝑠
 in sorted order. Let's look at the next suffix. Let's see how many new prefixes he adds. The total number of prefixes is equal to the length of the suffix. To find out which of them have already occurred in the previous suffixes, we just need to look at the 𝐿𝐶𝑃
 of this suffix with the previous one. Thus, we can calculate this number in 𝑂(1)
. Adding these numbers together, we get the answer.
回想一下，任何子字符串都是某个后缀的前缀，因此我们需要计算该字符串的后缀有多少个不同的前缀 𝑠
 有。让我们迭代字符串的后缀 𝑠
 按排序顺序。让我们看看下一个后缀。让我们看看他添加了多少新前缀。前缀的总数等于后缀的长度。要找出其中哪些已经出现在前面的后缀中，我们只需要查看 𝐿𝐶𝑃
 该后缀与前一个后缀的组合。因此，我们可以计算这个数字 𝑂(1)
 。将这些数字加在一起，我们就得到了答案。

Largest common substring  最大公共子串

The second task: given two strings 𝑠
 and 𝑡
. You need to find the longest string that occurs on both strings as a substring.
第二个任务：给定两个字符串 𝑠
 和 𝑡
 。您需要找到两个字符串中出现的最长字符串作为子字符串。

Let's combine two strings into one through the symbol “sharp”, a special character that does not occur in these strings. Now let's look at the suffixes of the resulting long string. Divide them into two classes: suffixes that begin on the string 𝑠
 and suffixes that begin on the string 𝑡
. If there is a common substring 𝑥
, then it must be a prefix of some suffix of the first class and some suffix of the second class. Thus, we need to find the maximum of 𝐿𝐶𝑃(𝑖,𝑗)
 for all pairs (𝑖,𝑗)
 such that the suffix 𝑖
 belongs to the first class and 𝑗
 belongs to the second class. Let's show that it’s enough to check only adjacent suffixes in sorted order. Indeed, let there be two suffixes, and they are not adjacent in the suffix array. Let's move from the suffix 𝑖
 along the suffix array to the suffix 𝑗
. Then at some point we get two adjacent suffixes of different classes. Their 𝐿𝐶𝑃
 will be no less than 𝐿𝐶𝑃(𝑖,𝑗)
.
让我们通过符号“sharp”将两个字符串合并为一个，“sharp”是这些字符串中不会出现的特殊字符。现在让我们看看生成的长字符串的后缀。将它们分为两类： 以字符串开头的后缀 𝑠
 以及以字符串开头的后缀 𝑡
 。如果存在公共子串 𝑥
 ，那么它一定是第一类的某个后缀和第二类的某个后缀的前缀。因此，我们需要找到最大值 𝐿𝐶𝑃(𝑖,𝑗)
 对于所有对 (𝑖,𝑗)
 这样后缀 𝑖
 属于第一类并且 𝑗
 属于第二类。让我们证明只检查按排序顺序相邻的后缀就足够了。事实上，假设有两个后缀，并且它们在后缀数组中不相邻。让我们从后缀开始 𝑖
 沿着后缀数组到后缀 𝑗
 。然后在某个时刻我们得到两个不同类别的相邻后缀。他们的 𝐿𝐶𝑃
 将不少于 𝐿𝐶𝑃(𝑖,𝑗)
 。

Thus, we obtain such an algorithm. We combine the strings through a sharp, build a suffix array of the resulting string, and then look for a maximum of 𝐿𝐶𝑃
 for all pairs of adjacent suffixes of different classes. Now try to implement solutions to these problems, as well as solve several additional tasks by yourself.
这样，我们就得到了这样一个算法。我们通过锐利组合字符串，构建结果字符串的后缀数组，然后查找最大值 𝐿𝐶𝑃
 对于不同类别的所有相邻后缀对。现在尝试实施这些问题的解决方案，并自己解决一些额外的任务。