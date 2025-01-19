Two Pointers Method  二指针法
The Two Pointers Method is an important technique that is often used in competetive programming.
双指针方法是竞争性编程中经常使用的一项重要技术。
What is this method? The easiest way to explain it is with the example of the task "Merging two sorted arrays".
这是什么方法呢？最简单的解释方法是使用“合并两个排序数组”任务的示例。

What is this task? We are given two arrays, sorted in ascending order, 𝑎
 and 𝑏
. We want to combine the elements of these arrays into one big array 𝑐
, also sorted in ascending order.
这个任务是什么？我们有两个数组，按升序排序， 𝑎
 和 𝑏
 。我们想要将这些数组的元素组合成一个大数组 𝑐
 ，也按升序排列。


The easiest way to do this is with the following algorithm:
最简单的方法是使用以下算法：

collect all the elements into one big array;
将所有元素收集到一个大数组中；
sort it with any sorting built into your language.
使用您语言中内置的任何排序方式对其进行排序。
Such an algorithm will take time (𝑛⋅𝑙𝑜𝑔(𝑛))
.
这样的算法需要时间 (𝑛⋅𝑙𝑜𝑔(𝑛))
 。

In this step, we will learn how to do it simply, without sorting, and in time faster than (𝑛⋅𝑙𝑜𝑔(𝑛))
 (in linear time).
在这一步中，我们将学习如何简单地做到这一点，无需排序，并且时间比 (𝑛⋅𝑙𝑜𝑔(𝑛))
 （在线性时间内）。

Let's see an example. We are given two arrays:
让我们看一个例子。我们有两个数组：

𝑎=[1,3,5,8,10]
𝑏=[2,6,7,9,13]

How do we merge them into one sorted array? To answer this question, let's understand which element will be in the first position in this array. Of course, this is the smallest element among all in 𝑎
 and 𝑏
. In array 𝑎
, the minimum element is the first (since the array is sorted). The situation is similar in array 𝑏
.
我们如何将它们合并到一个已排序的数组中？为了回答这个问题，让我们了解哪个元素将位于该数组中的第一个位置。当然，这是所有元素中最小的元素 𝑎
 和 𝑏
 。阵列中 𝑎
 ，最小元素是第一个（因为数组已排序）。数组中的情况类似 𝑏
 。

Let's look at these two elements (the first in 𝑎
 and 𝑏
), select the minimum one and move it to the first position in array 𝑐
 .
让我们看看这两个元素（第一个元素 𝑎
 和 𝑏
 )，选择最小的一个并将其移动到数组中的第一个位置 𝑐
 。

𝑎=[⧸1,3,5,8,10]
𝑏=[2,6,7,9,13]
𝑐=[1]

Now let's look again at the first non-deleted element of array 𝑎
 and the first non-deleted element of array 𝑏
. They are the smallest ones remaining in their arrays. Let's choose the smaller of these two elements and transfer it to 𝑐
.
现在让我们再看看数组的第一个未删除元素 𝑎
 和数组的第一个未删除元素 𝑏
 。它们是阵列中剩余的最小的。让我们选择这两个元素中较小的一个并将其传输到 𝑐
 。

𝑎=[⧸1,3,5,8,10]
𝑏=[⧸2,6,7,9,13]
𝑐=[1,2]

We will continue this algorithm until all the elements in 𝑎
 and 𝑏
 are removed.
我们将继续这个算法，直到所有元素 𝑎
 和 𝑏
 被删除。

How to implement this? You need to create two pointers (this where the name of the method is from).
如何实施？您需要创建两个指针（这是方法名称的来源）。

The first pointer will point to the first non-deleted element in 𝑎
, and the second pointer to the first non-deleted element in 𝑏
.
第一个指针将指向第一个未删除的元素 𝑎
 ，以及指向第一个未删除元素的第二个指针 𝑏
 。

𝑎=[⧸1,3𝑖↓,5,8,10]
𝑏=[⧸2,6𝑗↑,7,9,13]
𝑐=[1,2]

Each time we look, which of the elements under the pointers is smaller. If it is from the array 𝑎
, then you need to transfer it. Otherwise, you need to transfer an element from array 𝑏
. The index of the transfered element in array 𝑐
 will always be 𝑖+𝑗
. After we have moved the element, the corresponding pointer needs to be shifted to the right.
每次我们查看指针下的哪个元素较小。如果是来自数组 𝑎
 ，那么你需要转移它。否则，您需要从数组中传输一个元素 𝑏
 。被传输元素在数组中的索引 𝑐
 永远会是 𝑖+𝑗
 。移动元素后，相应的指针需要向右移动。

while i < a.size() || j < b.size():
    if a[i] < b[j]:
       c[i + j] = a[i]
       i++
    else:
       c[i + j] = b[j]
       j++
In the implementation of the algorithm, you need to be careful, at some point the elements of one of the arrays will run out completely, but in the other array the elements will still remain.
在算法的实现中，你需要小心，在某个时刻，其中一个数组的元素会完全耗尽，但另一个数组中的元素仍然会保留。
For example, at the end of the algorithm with our example, we come to the following situation:
例如，在我们的示例的算法结束时，我们会遇到以下情况：

𝑎=[⧸1,⧸3,⧸5,⧸8,⧸10]𝑖↓
𝑏=[⧸2,⧸6,⧸7,⧸9,13𝑗↑]
𝑐=[1,2,3,5,6,7,8,9,10]

If you do not implement the algorithm carefully, then at the next check which of the pointers is on the smallest element, you will go beyond the boundaries of the array.
如果您不仔细实现该算法，那么在下次检查哪个指针位于最小元素上时，您将超出数组的边界。

There are two ways to solve this problem.
有两种方法可以解决这个问题。

The first is to add +∞
 to the end of each of the arrays (in your programming language, this is the maximum number that fits into the data type).
第一个是添加 +∞
 到每个数组的末尾（在您的编程语言中，这是适合该数据类型的最大数字）。

Second solutions is to write the condition more accurately. When do you need to transfer an element from the first array? In case the second array has ended completely or if the first array has not ended yet and the element in it is less than the element in array 𝑏
 . The second case is dealt with in a similar way.
第二个解决方案是更准确地编写条件。什么时候需要从第一个数组中传输元素？如果第二个数组已完全结束或第一个数组尚未结束且其中的元素小于数组中的元素 𝑏
 。第二种情况也以类似的方式处理。

while i < a.size() || j < b.size():
    if j == b.size() || i < a.size() && a[i] < b[j]:
       c[i + j] = a[i]
       i++
    else:
       c[i + j] = b[j]
       j++
Why does this work in linear time? Each time we move one of the two pointers forward. The first pointer will be shifted no more times than the size of array 𝑎
, and the second no more than the size of array 𝑏
. In total, the algorithm will make (𝑎.𝑠𝑖𝑧𝑒()+𝑏.𝑠𝑖𝑧𝑒())
 operations.
为什么这能在线性时间内起作用？每次我们将两个指针之一向前移动。第一个指针的移动次数不会超过数组的大小 𝑎
 ，第二个不超过数组的大小 𝑏
 。总的来说，该算法将使 (𝑎.𝑠𝑖𝑧𝑒()+𝑏.𝑠𝑖𝑧𝑒())
 运营。
Number of smaller  数量较小
Let's apply the same technique to solve a different problem.
让我们应用相同的技术来解决不同的问题。
We have two arrays 𝑎
 and 𝑏
. We want to calculate for each element 𝑏𝑗
 how many such 𝑖
 exist that 𝑎𝑖<𝑏𝑗
.
我们有两个数组 𝑎
 和 𝑏
 。我们要计算每个元素 𝑏𝑗
 有多少这样的 𝑖
 存在 𝑎𝑖<𝑏𝑗
 。

This is a fairly common task, often encountered on a variety of occasions.
这是一项相当常见的任务，经常在各种场合遇到。

How to solve it? First, let's sort both arrays (if initially they were given unsorted). Now you can use binary search to answer the problem (we covered it in another chapter). For each element of 𝑏
, you need to find the prefix of array 𝑎
 that is less than this element.
怎么解决呢？首先，让我们对两个数组进行排序（如果最初它们是未排序的）。现在你可以使用二分搜索来回答这个问题（我们在另一章中介绍过）。对于每个元素 𝑏
 ，你需要找到数组的前缀 𝑎
 小于该元素。

But you can do without binary search by using the two pointer method. Suppose we are doing the same merge sort as in the previous task. We will get a large sorted array 𝑐
 containing all the elements from 𝑎
 and 𝑏
.
但是您可以使用双指针方法来不进行二分搜索。假设我们正在执行与上一个任务相同的合并排序。我们将得到一个大的排序数组 𝑐
 包含来自的所有元素 𝑎
 和 𝑏
 。

How to solve the problem using the resulting array 𝑐
? Let's see to which position of 𝑐
 element 𝑏𝑗
 moved. Where are the elements of array 𝑎
 that are less than 𝑏𝑗
? They are in 𝑐
 to the left of 𝑏𝑗
. Therefore, you need to find out how many elements came from array 𝑎
 on the prefix of array 𝑐
 before the element 𝑏𝑗
.
如何使用结果数组解决问题 𝑐
 ？我们看看到了哪个位置 𝑐
 元素 𝑏𝑗
 感动了。数组的元素在哪里 𝑎
 小于 𝑏𝑗
 ？他们在 𝑐
 的左边 𝑏𝑗
 。因此，您需要找出有多少个元素来自数组 𝑎
 在数组的前缀上 𝑐
 元素之前 𝑏𝑗
 。


For implementation, you can use the same algorithm as in the previous task. Array 𝑐
 itself is not useful to us. Let's take a look at the moment when we move an element from array 𝑏
. How many elements from 𝑎
 were moved before it? These are all elements with indices from 0
 to 𝑖−1
 (𝑖
 is a pointer to the first non-deleted element in 𝑎
). That is, there are exactly 𝑖
 such elements.
对于实现，您可以使用与上一个任务中相同的算法。大批 𝑐
 本身对我们来说没有用。让我们看一下从数组中移动元素的那一刻 𝑏
 。有多少个元素来自 𝑎
 之前被感动过吗？这些都是索引来自的元素 0
 到 𝑖−1
 （ 𝑖
 是指向第一个未删除元素的指针 𝑎
 ）。也就是说，正好有 𝑖
 这样的元素。

We no longer need to move elements into array 𝑐
. We simply move the pointers forward and respond to requests during the "former" moving of elements from 𝑏
.
我们不再需要将元素移动到数组中 𝑐
 。我们只需向前移动指针并在“前”移动元素期间响应请求 𝑏
 。

while ...:
    if ...:
       i++
    else:
       res[j] = i
       j++
Also, in this task, you can write simpler and more intuitive code. Instead of a single while loop with conditions inside, you can loop over the elements of array 𝑏
 (loop over the position of the 𝑗
 pointer). And with the second for loop move the first pointer 𝑖
 forward while 𝑎𝑖<𝑏𝑗
.
此外，在此任务中，您可以编写更简单、更直观的代码。您可以循环遍历数组的元素，而不是使用内部带有条件的单个while循环 𝑏
 （循环的位置 𝑗
 指针）。并在第二个for循环中移动第一个指针 𝑖
 前进同时 𝑎𝑖<𝑏𝑗
 。

i = 0
for j = 0..b.size()-1:
    while i < a.size() && a[i] < b[j]:
       i++
    res[j] = i