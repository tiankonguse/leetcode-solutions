Segment Tree  线段树
https://codeforces.com/edu/course/2/lesson/4/1


The segment tree is one of the most useful data structures in competitive programming. For what tasks is it needed? Let's start with the most basic task.
线段树是竞技编程中最有用的数据结构之一。哪些任务需要它？让我们从最基本的任务开始。
Sum on a segment  线段求和

Suppose we have an array 𝑎𝑖
 of 𝑛
 elements, and we want to be able to do two operations with it:
假设我们有一个数组 𝑎𝑖
 的 𝑛
 元素，我们希望能够用它执行两个操作：

set(i, v): set the element with index 𝑖
 to 𝑣
.
set(i, v) ：设置具有索引的元素 𝑖
 到 𝑣
 。
sum(l, r): find the sum on the segment from 𝑙
 to 𝑟−1
.
sum(l, r) ：求出段上的总和 𝑙
 到 𝑟−1
 。
Note that in the request for the sum we take the left border 𝑙
 inclusive, and the right border 𝑟
 exclusive. So we will do in all cases when we talk about segments.
请注意，在请求总和时，我们采用左边框 𝑙
 包容性和右边界 𝑟
 独家的。因此，当我们谈论细分时，我们将在所有情况下这样做。

Structure of the segment tree
线段树的结构

Let's imagine that we need to build a segment tree for the following array:
假设我们需要为以下数组构建线段树：


The segment tree be constructed as follows. This is a binary tree, in the leaves of which there are elements of the original array, and each internal node contains the sum of the numbers in its children.
线段树的构造如下。这是一棵二叉树，其叶子中包含原始数组的元素，每个内部节点包含其子节点中的数字之和。


Note that the tree turned out so beautiful, because the length of the array was a power of two. If the length of the array is not a power of two, you can extend the array with zeroes to the nearest power of two.
请注意，这棵树看起来非常漂亮，因为数组的长度是 2 的幂。如果数组的长度不是 2 的幂，则可以将带有零的数组扩展到最接近的 2 的幂。
In this case, the length of the array will increase no more than twice, so the asymptotic time complexity of the operations will not change.
在这种情况下，数组的长度增加不会超过两倍，因此操作的渐近时间复杂度不会改变。

Now let's look at how to do operations on such a tree.
现在让我们看看如何对这样的树进行操作。

Operation set  操作设定

Let's start with the operation set. When the element of the array changes, you need to change the corresponding number in the leaf node of the tree, and then recalculate the values ​​that will change from this. These are the values ​​that are higher up the tree from the modified leaf.
我们先从操作集开始。当数组的元素发生变化时，需要改变树的叶子节点中对应的数字，然后重新计算由此将发生变化的值。这些是修改后的叶子中树上较高的值。
We can simply recalculate the value in each node as the sum of the values ​​in children.
我们可以简单地重新计算每个节点中的值作为子节点中的值的总和。


When performing such an operation, we need to recalculate one node on each layer of the tree. We have only log𝑛
 layers, so the operation time will be 𝑂(log𝑛)
.
当执行这样的操作时，我们需要重新计算树的每一层上的一个节点。我们只有 log𝑛
 层数，所以操作时间为 𝑂(log𝑛)
 。

Operation sum  运算金额

Now let's look at how to calculate the sum on a segment. To do this, let's first see what kind of numbers are written in the nodes of the segment tree. Note that these numbers are the sums on some segments of the original array.
现在让我们看看如何计算段上的总和。为此，我们首先看看线段树的节点中写入了什么样的数字。请注意，这些数字是原始数组某些段的总和。


In this case, for example, the number in the root is the sum over the entire array, and the numbers in the leaves are the sum over the segment of one element.
例如，在这种情况下，根中的数字是整个数组的总和，叶子中的数字是一个元素的段上的总和。

Let's try to build the sum on the segment [𝑙..𝑟)
 from these already calculated sums. To do this, run a recursive traversal of the segment tree. In this case, we will interrupt recursion in two situations.
让我们尝试在线段上求和 [𝑙..𝑟)
 从这些已经计算出的总和中。为此，请运行线段树的递归遍历。在这种情况下，我们将在两种情况下中断递归。

The segment corresponding to the current node does not intersect the segment [𝑙..𝑟)
. In this case, all the elements in this subtree are outside the area in which we need to calculate the sum, so we can stop the recursion.
当前节点对应的线段不与线段相交 [𝑙..𝑟)
 。在这种情况下，该子树中的所有元素都在我们需要计算总和的区域之外，因此我们可以停止递归。
The segment corresponding to the current node is entirely nested in the segment [𝑙..𝑟)
. In this case, all the elements in this subtree are in the area in which we need to calculate the sum, so we need to add to the answer their sum, which is recorded in the current node.
当前节点对应的段完全嵌套在段中 [𝑙..𝑟)
 。在这种情况下，该子树中的所有元素都在我们需要计算总和的区域中，因此我们需要将它们的总和添加到答案中，该总和记录在当前节点中。

Here, the crosses indicate the vertices at which the recursion broke off in the first cutoff, and the vertices in which the number was added to the answer are circled.
这里，叉号表示在第一次截止时递归中断的顶点，并且将数字添加到答案的顶点被圈出。

How long does such a tree traversal work? To answer this question, we need to understand how many nodes none of the cutoffs will happen in, and we will need to go deeper into the tree. Each such case gives us a new branch of recursion.
这样的树遍历需要多长时间？为了回答这个问题，我们需要了解有多少节点不会发生任何截止，并且我们需要更深入地了解树。每个这样的情况都给我们一个新的递归分支。
It turns out that there will be quite a few such nodes. The fact is that in order for none of the cutoffs to work, the segment corresponding to the node of the tree must intersect the query segment, but not be contained in it entirely.
事实证明这样的节点会有不少。事实是，为了使所有截止都不起作用，与树的节点相对应的线段必须与查询线段相交，但不能完全包含在其中。
This is only possible if it contains one of the boundaries of the segment [𝑙..𝑟)
. But on each layer of the tree of segments there can be no more than one segment containing each of the boundaries. Thus, there can be no more than 2log𝑛
 nodes at which cutoffs did not work, and, therefore, the general asymptotic time of this procedure will be 𝑂(log𝑛)
.
仅当它包含线段的边界之一时，这才有可能 [𝑙..𝑟)
 。但在线段树的每一层上，包含每个边界的线段不能超过一个。因此，不能有超过 2log𝑛
 截止点不起作用的节点，因此，该过程的一般渐近时间将是 𝑂(log𝑛)
 。

Minimum and other functions
最小及其他函数
What other operations can be done using the segment tree? Instead of the sum, you can calculate other functions on the interval, for example, a minimum. Add the following operation to the tree:
使用线段树还可以进行哪些其他操作？除了求和之外，您还可以计算区间上的其他函数，例如最小值。将以下操作添加到树中：
min(l, r), which returns the minimum on the segment 𝑎[𝑙..𝑟−1]
.
min(l, r) ，返回线段上的最小值 𝑎[𝑙..𝑟−1]
 。
How to handle such an operation using the segment tree. Let's build the same tree as for the sum, only in each node record not the sum of the elements in children, but the minimum.
如何使用线段树处理这样的操作。让我们构建与求和相同的树，只是在每个节点中记录的不是子元素的总和，而是最小值。


The set operation is performed as before. You need to replace the element in the leaf node and then recalculate the values ​​up the tree to the root. The operation min is performed in the same way as sum: you need to traverse the tree, while doing the same cutoffs, while the segment will be divided into several segments, on which we already know the minimum. Taking a minimum of these numbers, we get a minimum over the entire segment. The operation time will also be 𝑂(log𝑛)
.
设置操作与以前一样执行。您需要替换叶节点中的元素，然后重新计算树向上到根的值。 min操作的执行方式与sum相同：您需要遍历树，同时进行相同的截止，而线段将被分为几个线段，我们已经知道了这些线段的最小值。取这些数字的最小值，我们就得到了整个段的最小值。运行时间也将是 𝑂(log𝑛)
 。

Other functions  其他功能

In addition to the sum and the minimum, using the segment tree, you can calculate any associative operation. The operation ⊗
 is called associative if its result does not depend on the order in which it is calculated, that is, if (𝑎⊗𝑏)⊗𝑐=𝑎⊗(𝑏⊗𝑐)
.
除了求和和最小值之外，使用线段树还可以计算任何关联运算。操作 ⊗
 如果其结果不依赖于计算顺序，则称为关联性，即，如果 (𝑎⊗𝑏)⊗𝑐=𝑎⊗(𝑏⊗𝑐)
 。

For example, in addition to the sum and the minimum, associative operations are:
例如，除了求和和最小值之外，关联运算还有：

multiplication (including modulo multiplication, matrix multiplication, etc.),
乘法（包括模乘、矩阵乘法等），
bitwise operations: &, |, ^,
按位运算： & 、 | , ^ ,
the largest common divisor (in this case, it should be noted that the calculation time of the GCD is not 𝑂(1)
, so the operation time will be longer.
最大公约数（在这种情况下，需要注意的是，GCD的计算时间不是 𝑂(1)
 ，所以运行时间会更长。
In simpler terms, a function can be used for a segment tree, if you know the result of its calculation for two halves of a segment, you can quickly calculate its result for the entire segment.
简单来说，一个函数可以用于线段树，如果你知道它对线段两半的计算结果，你就可以快速计算出它对整个线段的结果。

Consider a more nontrivial operation. Suppose we want to be able to calculate on a segment the number of elements equal to the minimum on this segment. To add such an operation, let's store in each node a pair of numbers (𝑚𝑖𝑛,𝑐𝑛𝑡)
: the minimum value on the segment and the number of elements equal to this minimum.
考虑一个更重要的操作。假设我们希望能够计算一个段上的元素数量等于该段上的最小值。为了添加这样的操作，我们在每个节点中存储一对数字 (𝑚𝑖𝑛,𝑐𝑛𝑡)
 ：线段上的最小值以及等于该最小值的元素数量。

Now let's see how to recalculate the value of such a pair in a segment, knowing the values ​​in halves. Suppose that the values ​​are (𝑚1,𝑐1)
 and (𝑚2,𝑐2)
 on each half of the segment, let's see how the values ​​of 𝑚1
 and 𝑚2
 are related. If 𝑚1<𝑚2
, then the minimum on the segment is 𝑚1
, and the number of elements equal to the minimum is 𝑐1
, so for a large segment we get the value (𝑚1,𝑐1)
. Similarly, if 𝑚1>𝑚2
, then the value for a large segment is (𝑚2,𝑐2)
. If 𝑚1=𝑚2
, then the minimums at half are the same. The total number of elements equal to the minimum is 𝑐1+𝑐2
, so we get the pair (𝑚1,𝑐1+𝑐2)
. We construct a segment tree in which such a pair is recorded in each node, and we will update it using the described function. As a result, we obtain a segment tree with the required operation.
现在让我们看看如何在知道一半的值的情况下重新计算段中此类对的值。假设值为 (𝑚1,𝑐1)
 和 (𝑚2,𝑐2)
 在该段的每一半上，让我们看看 𝑚1
 和 𝑚2
 是相关的。如果 𝑚1<𝑚2
 ，则线段上的最小值为 𝑚1
 ，等于最小值的元素数量为 𝑐1
 ，因此对于很大一部分，我们得到的值 (𝑚1,𝑐1)
 。同样，如果 𝑚1>𝑚2
 ，那么大段的值为 (𝑚2,𝑐2)
 。如果 𝑚1=𝑚2
 ，那么一半的最小值是相同的。等于最小值的元素总数为 𝑐1+𝑐2
 ，所以我们得到了这对 (𝑚1,𝑐1+𝑐2)
 。我们构造一个线段树，其中每个节点中记录这样的对，并且我们将使用所描述的函数更新它。结果，我们获得了具有所需操作的线段树。