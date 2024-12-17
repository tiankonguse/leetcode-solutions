# Improved algorithm 改进算法
Using Radix Sort 使用基数排序

https://codeforces.com/edu/course/2/lesson/2/2

At the last step, we got the algorithm working in the time 𝑂(𝑛log2𝑛)
. To make the algorithm faster, we need to get rid of the sorting in 𝑂(𝑛log𝑛)
 on each transition. Let's notice that we need to sort the pairs of numbers (𝑎𝑖,𝑏𝑖)
, with each of the numbers 𝑎𝑖
 and 𝑏𝑖
 being integers in the range from 0 to 𝑛−1
. We can use the radix sort to sort these pairs.
最后一步，我们让算法及时运行 𝑂(𝑛log2𝑛)
 。为了使算法更快，我们需要摆脱排序 𝑂(𝑛log𝑛)
 在每次转换时。让我们注意到我们需要对数字对进行排序 (𝑎𝑖,𝑏𝑖)
 ，每个数字 𝑎𝑖
 和 𝑏𝑖
 是 0 到 0 之间的整数 𝑛−1
 。我们可以使用基数排序来对这些对进行排序。

Radix sort works as follows. We sort the pairs by the second element, and then sort them again using stable sorting algorithm by the first element. Since each time the key is an integer from 0 to 𝑛−1
, in both cases we can use counting sort. Counting sort works as follows. We will calculate how many times each element occurs, after that we create the buckets of the required size for each element, and arrange the elements into buckets.
基数排序的工作原理如下。我们按第二个元素对这些对进行排序，然后使用稳定的排序算法按第一个元素对它们再次排序。由于每次key都是从0到的整数 𝑛−1
 ，在这两种情况下我们都可以使用计数排序。计数排序的工作原理如下。我们将计算每个元素出现的次数，然后为每个元素创建所需大小的桶，并将元素排列到桶中。

Thus, each sort will work in linear time, and the total time of the algorithm will be 𝑂(𝑛log𝑛)
.
因此，每次排序都将以线性时间进行，算法的总时间将为 𝑂(𝑛log𝑛)
 。

Additional optimizations To make the algorithm even a little faster and easier, the following fact can be noted. At iteration 𝑘
 we get sorted strings of length 2𝑘
. If we add another 2𝑘
 characters to the beginning of each string, we get strings of length 2𝑘+1
, sorted by right halves. After that, it will be enough to do only the second phase of radix sort, sorting the pairs by the first element.
额外的优化为了使算法更快更简单，需要注意以下事实。迭代时 𝑘
 我们得到长度排序的字符串 2𝑘
 。如果我们添加另一个 2𝑘
 字符到每个字符串的开头，我们得到长度的字符串 2𝑘+1
 ，按右半部分排序。之后，仅进行基数排序的第二阶段就足够了，即按第一个元素对对进行排序。