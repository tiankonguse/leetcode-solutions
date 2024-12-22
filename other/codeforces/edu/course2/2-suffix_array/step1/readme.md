# Suffix array. Base algorithm

https://codeforces.com/edu/course/2/lesson/2/1

后缀数组。基础算法
What is a suffix array.
什么是后缀数组。
Consider a string 𝑠
.
考虑一个字符串 。



Let's write all its suffixes in lexicographical order. We get this an array of strings.
让我们按字典顺序写出它的所有后缀。我们得到一个字符串数组。



This sequence of suffixes is called the suffix array. How will we store it? If you store it as strings, then it will occupy 𝑂(𝑛2)
 memory. To keep it smaller, let's notice that the suffix can be identified by the index of the first character. In our example, suffixes will have these numbers.
这个后缀序列称为 .我们将如何存储它？如果将其存储为字符串，那么它将占用 𝑂(𝑛2)
 记忆。为了使其更小，我们注意到后缀可以通过第一个字符的索引来识别。在我们的示例中，后缀将包含这些数字。



We will store the suffix array as an array 𝑝
 of suffix numbers in sorted order. Then it will occupy 𝑂(𝑛)
 memory. Now our first task is this: given the string 𝑠
, build an array 𝑝
.
我们将后缀数组存储为数组 𝑝
 按排序顺序排列的后缀数字。那么就会占据 𝑂(𝑛)
 记忆。现在我们的第一个任务是：给定字符串 𝑠
 ,建立一个数组 𝑝
 。

To make the algorithm simpler, we will make some preparations. First, add the symbol $ to the end of the string. This will be a special character that is smaller than all characters in the string. As a result, the symbol $ will be added to each suffix. Let's notice that the order of the strings has not changed, because $ is smaller than all characters.
为了让算法更加简单，我们会做一些准备工作。首先，将符号$添加到字符串末尾。这将是一个比字符串中所有字符都小的特殊字符。结果，符号$将被添加到每个后缀。我们注意到字符串的顺序没有改变，因为$比所有字符都小。



Now let's make the length of all the strings the same. To do this, let's write after $ all the other characters in the string in a cycle. Again, note that order of strings has not changed, because the characters after $ do not affect the string ordering.
现在让所有字符串的长度相同。为此，我们将字符串中的所有其他字符写在循环中的$之后。再次注意，字符串的顺序没有改变，因为$之后的字符不影响字符串的顺序。



Now the last preparation. Let's make the length of the strings the power of two, for this we add more characters in a cycle until the length of the string becomes a power of two. In our example, the string length is 7, so we need to add one character.
现在是最后的准备。让我们将字符串的长度设置为 2 的幂，为此，我们在一个循环中添加更多字符，直到字符串的长度变为 2 的幂。在我们的例子中，字符串长度为7，所以我们需要添加1个字符。



Algorithm idea 算法思路

We will build this table by columns, each time increasing the number of columns twice. That is, first we construct the first column, then the first two, then four, and so on. In other words, we divide the algorithm into log𝑛
 iterations, and on the iteration 𝑘
 we construct an array consisting of the strings 𝑠[𝑖..𝑖+2𝑘−1]
, sorted in lexicographical order (we assume that the string is cyclic, that is, the character with index 𝑖
 corresponds to the character with index 𝑖mod𝑛
 of the original string).
我们将按列构建此表，每次将列数增加两倍。也就是说，首先我们构建第一列，然后是前两列，然后是第四列，依此类推。换句话说，我们将算法分为 log𝑛
 迭代，以及关于迭代 𝑘
 我们构造一个由字符串组成的数组 𝑠[𝑖..𝑖+2𝑘−1]
 ，按照字典顺序排序（我们假设字符串是循环的，即索引为的字符 𝑖
 对应于带有索引的字符 𝑖mod𝑛
 原始字符串）。



Let's start from the base, if 𝑘=0
, then we need to sort the strings of one character 𝑠[𝑖..𝑖]
. This can be done by any sort in 𝑂(𝑛log𝑛)
.
让我们从基础开始，如果 𝑘=0
 ，那么我们需要对一个字符的字符串进行排序 𝑠[𝑖..𝑖]
 。这可以通过任何排序来完成 𝑂(𝑛log𝑛)
 。

Now make the transition from 𝑘
 to 𝑘+1
. We need to sort the strings of length 2𝑘+1
, using the order of the strings of length 2𝑘
. To do this, let's learn how to quickly compare strings of length 2𝑘+1
. Suppose we have two strings 𝐴
 and 𝐵
, both have lengths 2𝑘+1
. Let's divide both strings into two halves, then each half has a length 2𝑘
.
现在从 𝑘
 到 𝑘+1
 。我们需要对长度的字符串进行排序 2𝑘+1
 ，使用字符串长度的顺序 2𝑘
 。为此，我们来学习如何快速比较字符串的长度 2𝑘+1
 。假设我们有两个字符串 𝐴
 和 𝐵
 ，两者都有长度 2𝑘+1
 。让我们将两个字符串分成两半，然后每一半都有一个长度 2𝑘
 。

Let's compare their left halves. If they are not equal, for example, if 𝐴.𝑙𝑒𝑓𝑡
 is less than 𝐵.𝑙𝑒𝑓𝑡
. This means that they have some common prefix, and after it comes a character that is not equal, and this character in the string 𝐴
 is less than in the string 𝐵
. In this case, the entire string 𝐴
 is less than the string 𝐵
, and the right halves should not be compared.
我们来比较一下他们的左半身。如果它们不相等，例如，如果 𝐴.𝑙𝑒𝑓𝑡
 小于 𝐵.𝑙𝑒𝑓𝑡
 。这意味着它们有一些共同的前缀，后面有一个不相等的字符，而这个字符在字符串中 𝐴
 小于字符串中的值 𝐵
 。在这种情况下，整个字符串 𝐴
 小于字符串 𝐵
 ，并且不应比较右半部分。



If the left halves are equal, then let's compare the right halves. Suppose, for example, 𝐴.𝑟𝑖𝑔ℎ𝑡
 is less than 𝐵.𝑟𝑖𝑔ℎ𝑡
. This again means that there is a common prefix, and then a character that is less in the string 𝐴
 than in the string 𝐵
. Again we get that the string 𝐴
 is less than the string 𝐵
.
如果左半部分相等，那么我们比较右半部分。假设，例如， 𝐴.𝑟𝑖𝑔ℎ𝑡
 小于 𝐵.𝑟𝑖𝑔ℎ𝑡
 。这又意味着有一个共同的前缀，然后是字符串中较少的字符 𝐴
 比字符串中的 𝐵
 。我们再次得到字符串 𝐴
 小于字符串 𝐵
 。



Thus, we get that 𝐴<𝐵⟺𝐴.𝑙𝑒𝑓𝑡<𝐵.𝑙𝑒𝑓𝑡 OR (𝐴.𝑙𝑒𝑓𝑡=𝐵.𝑙𝑒𝑓𝑡 AND 𝐴.𝑟𝑖𝑔ℎ𝑡<𝐵.𝑟𝑖𝑔ℎ𝑡)
. If we learn to quickly compare strings of length 2𝑘
, then we will make a comparator that quickly compares strings of length 2𝑘+1
.
因此，我们得到 𝐴<𝐵⟺𝐴.𝑙𝑒𝑓𝑡<𝐵.𝑙𝑒𝑓𝑡 OR (𝐴.𝑙𝑒𝑓𝑡=𝐵.𝑙𝑒𝑓𝑡 AND 𝐴.𝑟𝑖𝑔ℎ𝑡<𝐵.𝑟𝑖𝑔ℎ𝑡)
 。如果我们学会快速比较长度的字符串 2𝑘
 ，然后我们将制作一个比较器来快速比较长度的字符串 2𝑘+1
 。

Now we need to learn how to compare strings of length 2𝑘
 quickly. We will do it as follows. Let's go through the strings of length 2𝑘
 in sorted order, and assign them integer numbers so that a smaller string corresponds to a smaller number. We call these numbers equivalence classes. Now, instead of comparing strings, we will compare their equivalence classes. Thus, we can compare strings of length 2𝑘+1
 in 𝑂(1)
.
现在我们需要学习如何比较字符串的长度 2𝑘
 迅速地。我们将按如下方式进行。让我们看一下长度的字符串 2𝑘
 按排序顺序，并为它们分配整数，以便较小的字符串对应较小的数字。我们称这些数字为等价类。现在，我们将比较它们的等价类，而不是比较字符串。因此，我们可以比较长度的字符串 2𝑘+1
 在 𝑂(1)
 。

For example, for the string that we analyzed above, for 𝑘=1
 we get the following order of strings of length 2. Let's go through these strings and assign them equivalence classes (array 𝑐
).
例如，对于我们上面分析的字符串，对于 𝑘=1
 我们得到长度为 2 的字符串的以下顺序。让我们遍历这些字符串并为它们分配等价类（数组 𝑐
 ）。



Now, if, for example, we want to compare the strings abab and abba. Divide them into two halves and write the equivalence classes for each of the halves, get the pair (2,2)
 for the string abab, and the pair (2,3)
 for the string abba. Now compare these pairs, we get that (2,2)<(2,3)
, which means that abab < abba.
现在，例如，如果我们想要比较字符串abab和abba 。将它们分成两半，并为每一半写出等价类，得到一对 (2,2)
 对于字符串abab和对 (2,3)
 对于字符串abba 。现在比较这些对，我们得到 (2,2)<(2,3)
 ，这意味着abab < abba 。

Algorithm 算法

Thus, we get the following algorithm. First, we form strings of one character and sort them by any sort algorithm in 𝑂(𝑛log𝑛)
. Next, log𝑛
 times we make the transition from 𝑘
 to 𝑘+1
. Each transition is done like this: take sorted strings of length 2𝑘
, assign equivalence classes to them, then assign to each string of length 2𝑘+1
 a pair of numbers: equivalence classes of its halves, sort these pairs and get a sorted order for a string of length 2𝑘+1
.
因此，我们得到以下算法。首先，我们形成一个字符的字符串，并通过任意排序算法对它们进行排序 𝑂(𝑛log𝑛)
 。下一个， log𝑛
 次我们从 𝑘
 到 𝑘+1
 。每个转换都是这样完成的：获取长度排序的字符串 2𝑘
 ，为它们分配等价类，然后分配给每个长度的字符串 2𝑘+1
 一对数字：其两半的等价类，对这些数字对进行排序并获得长度字符串的排序顺序 2𝑘+1
 。

The time complexity this algorithm will be 𝑂(𝑛log2𝑛)
, because on at each of the log𝑛
 iterations we do the sorting in 𝑂(𝑛log𝑛)
 time.
该算法的时间复杂度为 𝑂(𝑛log2𝑛)
 ，因为在每个 log𝑛
 我们进行排序的迭代 𝑂(𝑛log𝑛)
 时间。