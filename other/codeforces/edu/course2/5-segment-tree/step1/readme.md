Mass changing operations  大规模变更操作

https://codeforces.com/edu/course/2/lesson/5?locale=en

Last time we learned the segment tree data structure. Now we will improve it to perform operations of changing elements on a segment.
上次我们学习了线段树数据结构。现在我们将改进它以执行更改段上元素的操作。
Segment addition  段添加

Suppose we have an array 𝑎
 of 𝑛
 elements, and we want to process the following operations:
假设我们有一个数组 𝑎
 的 𝑛
 元素，我们要处理以下操作：

add(l, r, x): add 𝑥
 to all 𝑎𝑖
 (𝑙≤𝑖<𝑟
),
添加（l，r，x） ：添加 𝑥
 致所有人 𝑎𝑖
 （ 𝑙≤𝑖<𝑟
 ),
get(i): get the value of 𝑎𝑖
.
get(i) ：获取值 𝑎𝑖
 。
The solution to this problem was discussed earlier, but now we will solve this problem using a different technique that is applicable to more functions.
前面讨论了这个问题的解决方案，但现在我们将使用适用于更多功能的不同技术来解决这个问题。

Let's build a segment tree of an array of length 𝑛
, consisting of zeros.
让我们构建一个长度数组的线段树 𝑛
 ，由零组成。


Each node of the segment tree will be responsible for some segment of the original array. The numbers that are written in the nodes of the tree will describe not the function on the segment, as before, but the operation that must be applied to the segment.
线段树的每个节点将负责原始数组的某些线段。写入树的节点中的数字不会像以前那样描述段上的函数，而是必须应用于段的操作。


The number that is written in the specified node must be added to all numbers on the selected segment.
写入指定节点的数字必须与所选段上的所有数字相加。

Operation add  操作添加

Let's start with the add operation. To add the value 𝑥
 to the elements on the segment [𝑙..𝑟)
, we split the original segment into several segments, each of which is covered by some tree node. To find such a partition into segments, we use recursive traversal, similar to traversal we used to find the sum on a segment. We will stop recursion in the following cases:
让我们从添加操作开始。添加值 𝑥
 到段上的元素 [𝑙..𝑟)
 ，我们将原始段分割成几个段，每个段都被某个树节点覆盖。为了找到这样的分段划分，我们使用递归遍历，类似于我们用来求分段总和的遍历。在以下情况下我们将停止递归：

The segment corresponding to the current node does not intersect with the segment [𝑙..𝑟)
. In this case, all elements in the current subtree will be outside the original segment, so it makes no sense to go deeper.
当前节点对应的线段与线段不相交 [𝑙..𝑟)
 。在这种情况下，当前子树中的所有元素都将位于原始段之外，因此深入下去是没有意义的。
The segment corresponding to the current node lies entirely in the segment [𝑙..𝑟)
. In this case, all elements in the current subtree belong to the segment [𝑙..𝑟)
, so it is enough to add 𝑥
 to the value in the current node.
当前节点对应的段完全位于段内 [𝑙..𝑟)
 。在这种情况下，当前子树中的所有元素都属于该段 [𝑙..𝑟)
 ，所以添加就足够了 𝑥
 为当前节点中的值。

These pictures show the steps we take when process the operation add(3, 8, 5).
这些图片显示了我们在处理add(3, 8, 5)操作时所采取的步骤。



Here the cross marks the nodes at which the recursion cut off by the first cut, and the tick marks the nodes where the number was added to the node, and the recursion was cut off at the second cut. How long does this tree traversal work? The running time of the operation add is (log𝑛)
, for the same reason as finding the sum on the segment from the last lecture.
这里十字标记的是第一次切割时递归被切断的节点，勾号标记的是节点上添加了数字，第二次切割时递归被切断的节点。这个树遍历需要多长时间？ add操作的运行时间为 (log𝑛)
 ，其原因与求上一课的片段之和相同。

Let's execute two more queries:
让我们再执行两个查询：


add(1, 6, 3)  添加(1,6,3)



add(4, 7, 1)  添加(4, 7, 1)

Operation get  操作得到

How do we find the value of the 𝑖
-th element of an array? Note that the value of 𝑎𝑖
 was changed only by those operations, those segments contain the point 𝑖
. That is, these are the segments that changed the value at the nodes on the path from the 𝑖
-th leaf to the root of the tree. To calculate the value of 𝑎𝑖
, we need to apply a function, in this case addition, to all elements along the path from leaf to root. The execution time of this operation is also (log𝑛)
, since the height of the tree is log𝑛
.
我们如何找到它的价值 𝑖
 - 数组的第一个元素？请注意，值 𝑎𝑖
 仅由这些操作更改，这些段包含点 𝑖
 。也就是说，这些段改变了从 𝑖
 -第 叶子到树根。计算值 𝑎𝑖
 ，我们需要将一个函数（在本例中为加法）应用于从叶到根的路径上的所有元素。该操作的执行时间也是 (log𝑛)
 ，因为树的高度是 log𝑛
 。

In this picture, the vertices are highlighted in a circle, the values ​​of which must be added to answer the request get(4).
在这张图中，顶点以圆圈突出显示，必须添加其值才能响应get(4)请求。
Other commutative operations
其他交换运算
Recall that the operation ⊗
 (⊗
 is an arbitrary operation, for example +
, ∗
 or 𝑔𝑐𝑑
) is called:
回想一下操作 ⊗
 （ ⊗
 是任意操作，例如 +
 , ∗
 或者 𝑔𝑐𝑑
 ) 称为：
associative, if (𝑎⊗𝑏)⊗𝑐=𝑎⊗(𝑏⊗𝑐)
, that is, for any arrangement of parentheses in the expression, the result does not change,
结合的，如果 (𝑎⊗𝑏)⊗𝑐=𝑎⊗(𝑏⊗𝑐)
 ，也就是说，对于表达式中括号的任何排列，结果都不会改变，
commutative if 𝑎⊗𝑏=𝑏⊗𝑎
, that is, for any order of arguments, the result does not change. end {itemize}
可交换的如果 𝑎⊗𝑏=𝑏⊗𝑎
 ，也就是说，对于任何参数顺序，结果都不会改变。结束{逐项列出}
In the current version of the segment tree, we can handle only associative and commutative operations. Why is this so? Let's introduce a new request modify(l, r, x): apply to all 𝑎𝑖
 (𝑙≤𝑖<𝑟
) the operation ⊗
 with the second argument 𝑥
, that is, 𝑎𝑖=𝑎𝑖⊗𝑥
.
在当前版本的线段树中，我们只能处理关联和交换操作。为什么会这样呢？让我们引入一个新的请求modify(l, r, x) ：适用于所有 𝑎𝑖
 （ 𝑙≤𝑖<𝑟
 ）操作 ⊗
 与第二个参数 𝑥
 ， 那是， 𝑎𝑖=𝑎𝑖⊗𝑥
 。

Why is it necessary for the operation to be associative? When we want to change a value in a node that has already been changed before, we apply the ⊗
 operation to the two requests 𝑥
 (old value) and 𝑦
 (new request). That is, it is necessary that the results of (𝑎𝑖⊗𝑥)⊗𝑦
 and 𝑎𝑖⊗(𝑥⊗𝑦)
 are equal. Why is it necessary for the operation to be commutative? Because we have to calculate the operation from the arguments that come in order from request to request, but we calculate the operation from the arguments that come in the order from the leaf to the root.
为什么运算必须具有关联性？当我们想要更改之前已经更改过的节点中的值时，我们应用 ⊗
 对两个请求的操作 𝑥
 （旧值）和 𝑦
 （新请求）。也就是说，结果必须是 (𝑎𝑖⊗𝑥)⊗𝑦
 和 𝑎𝑖⊗(𝑥⊗𝑦)
 是平等的。为什么运算必须是可交换的？因为我们必须根据从一个请求到另一个请求的顺序的参数来计算操作，但是我们根据从叶子到根的顺序的参数来计算操作。
That is, it is necessary that when the order of the arguments is changed, the result of the operation does not change.
也就是说，当参数的顺序改变时，运算结果必须不改变。

Non-commutative operations
非交换运算
Let's improve the segment tree to handle associative, non-commutative operations.
让我们改进线段树以处理关联、非交换操作。
Let's say we have two operations:
假设我们有两个操作：

modify(l, r, x): replace all 𝑎𝑖
 (𝑙≤𝑖<𝑟
) with the 𝑎𝑖⊗𝑥
, that is, 𝑎𝑖=𝑎𝑖⊗𝑥
.
修改（l，r，x） ：替换所有 𝑎𝑖
 （ 𝑙≤𝑖<𝑟
 ）与 𝑎𝑖⊗𝑥
 ， 那是， 𝑎𝑖=𝑎𝑖⊗𝑥
 。
get(i): get the value of 𝑎𝑖
.
get(i) ：获取值 𝑎𝑖
 。
We will maintain the invariant that the old operations are deeper in the tree than the new ones. That is, the operations on the path from any node of the tree to the root are sorted by time. This allows you to respond to a get request by walking from the leaf of the tree to the root and calculating operations in the usual order.
我们将保持旧操作比新操作在树中更深的不变式。即从树的任意节点到根的路径上的操作按时间排序。这允许您通过从树的叶子走到根并按通常的顺序计算操作来响应get请求。


To do this, we will use the lazy propagation technique. If the value 𝑥
 is written in the node, and in the children 𝑦
 and 𝑧
, then after propagation the value 𝑦⊗𝑥
 in the left child, 𝑧⊗𝑥
 in the right, and the value in the current node will disappear (we applied the query to children, so the current value is no longer needed). Thus, we have retained the invariant and released the current node.
为此，我们将使用惰性传播技术。如果值 𝑥
 写在节点和子节点中 𝑦
 和 𝑧
 ，然后传播后的值 𝑦⊗𝑥
 在左边的孩子中， 𝑧⊗𝑥
 右侧，当前节点中的值将消失（我们将查询应用于子节点，因此不再需要当前值）。因此，我们保留了不变式并释放了当前节点。


But in order to apply the operation to a certain node, you need to free all the vertices on the way from it to the root, that is, you need to go from the root to the node from top to bottom and push through.
但为了将操作应用到某个节点，需要释放从它到根的途中的所有顶点，即需要从根到该节点从上到下推通。


The node to which a new operation should be applied is highlighted in orange. The node to which propagation is applied at the corresponding step is highlighted in blue.
应应用新操作的节点以橙色突出显示。在相应步骤中应用传播的节点以蓝色突出显示。
At the fifth step, all the vertices on the path from the orange node to the root are empty, so we can write the value 𝑥
 into it.
第五步，从橙色节点到根的路径上的所有顶点都是空的，所以我们可以写入值 𝑥
 进入其中。

Propagation works in (1)
, so we process requests in (log𝑛)
. Thus, we have learned how to work with associative, non-commutative operations, such as matrix multiplication or assignment on a segment.
传播工作于 (1)
 ，所以我们处理请求 (log𝑛)
 。因此，我们已经学习了如何使用关联、非交换运算，例如矩阵乘法或段上的赋值。

