Addition and minimum  加法和最小值

https://codeforces.com/edu/course/2/lesson/5/2

We have learned how to process requests of the form “change on a segment” and “value at a point”. Let's modify the segment tree so that it can handle the requests “change on segment” and “function value on segment”.
我们已经学习了如何处理“段上的更改”和“某个点上的值”形式的请求。让我们修改段树，使其能够处理“段上更改”和“段上的函数值”请求。
Let's take the following operations:
我们进行以下操作：

add(l, r, x): add 𝑥
 to all 𝑎𝑖
 (𝑙≤𝑖<𝑟
),
添加（l，r，x） ：添加 𝑥
 致所有人 𝑎𝑖
 （ 𝑙≤𝑖<𝑟
 ),
min(l, r): find the minimum of all 𝑎𝑖
 (𝑙≤𝑖<𝑟
).
min(l, r) ：找到所有最小值 𝑎𝑖
 （ 𝑙≤𝑖<𝑟
 ）。
First, let's build a segment tree for the minimum.
首先，让我们构建一个最小线段树。


Segment tree for the min operation built over an array
基于数组构建的最小操作的线段树

[3, 4, 2, 5, 6, 8, 1, 3].
[3,4,2,5,6,8,1,3] 。

How to perform change operations on a segment in such a tree? We will store two values ​​at each node (the minimum on the segment and the value added on the segment). Suppose we need to process the request add(l, r, x). We will use the method similar to the one we used on previous step:
如何对这样的树中的段执行更改操作？我们将在每个节点存储两个值（段上的最小值和段上的添加值）。假设我们需要处理请求add(l, r, x) 。我们将使用与上一步中使用的方法类似的方法：

If the current node is inside the segment from the query, then add 𝑥
 to both values ​​at the current node.
如果当前节点位于查询的段内，则添加 𝑥
 到当前节点的两个值。
If the segment that is covered by the current node does not intersect with the segment from the request, then exit the current node.
如果当前节点覆盖的线段与请求中的线段不相交，则退出当前节点。
Every time we leave the node (which we have not changed), it is necessary to recalculate the minimum in it. It will be equal to the minimum of the values ​​of the children.
每次我们离开节点（我们没有改变）时，都需要重新计算其中的最小值。它将等于孩子们的价值观的最小值。

This is how the processing of the request add(3, 8, 2) looks like.
这就是请求add(3, 8, 2)的处理方式。

As you can see, some vertices, for example, the fourth leaf, have old (not updated) values.
正如您所看到的，某些顶点（例如第四个叶子）具有旧的（未更新的）值。
The real value at the node is the minimum at the node plus the sum of additions from the ancestor of this node to the root of the tree (changes only in these nodes lead to a change in the current minimum).
节点处的实际值是该节点处的最小值加上从该节点的祖先到树的根的加法之和（仅这些节点中的更改会导致当前最小值的更改）。

This fact gives an idea of ​​how to respond to the request min (l, r). We will recursively traverse the tree and maintain the sum on the way from the root to the ancestor of the current node. Take the minimum of the values ​​the minimum at the node plus the sum from it to the root at all vertices, the segments of which make up the segment [𝑙,𝑟)
 (as in a regular query to the tree of segments) will be the answer.
这个事实给出了如何响应请求min (l, r)的想法。我们将递归地遍历树并维护从根到当前节点的祖先的路径的总和。取该节点处的最小值加上从该节点到根处所有顶点的值的最小值，其线段组成线段 [𝑙,𝑟)
 （就像对线段树的常规查询一样）将是答案。


This picture shows the response to the min(4, 7) request.
该图显示了对min(4, 7)请求的响应。

These operations also work in (log𝑛)
 time.
这些操作也适用于 (log𝑛)
 时间。
Other operations  其他操作
How to process other operations? Suppose we have two types of queries:
如何处理其他操作？假设我们有两种类型的查询：
modify(l, r, x): apply to each 𝑎𝑖
 (𝑙≤𝑖<𝑟
) operation ⊗
 with the second argument 𝑥
, that is, 𝑎𝑖=𝑎𝑖⊗𝑥
,
修改（l，r，x） ：适用于每个 𝑎𝑖
 （ 𝑙≤𝑖<𝑟
 ） 手术 ⊗
 与第二个参数 𝑥
 ， 那是， 𝑎𝑖=𝑎𝑖⊗𝑥
 ,
calc(l, r): calculate the function on the segment [𝑙,𝑟)
, that is, 𝑎𝑙⊙𝑎𝑙+1⊙…⊙𝑎𝑟−1

calc(l, r) ：计算线段上的函数 [𝑙,𝑟)
 ， 那是， 𝑎𝑙⊙𝑎𝑙+1⊙…⊙𝑎𝑟−1
⊗
 and ⊙
 are any operations that have the properties below.
⊗
 和 ⊙
 是具有以下属性的任何操作。

What properties of operations do we need?
我们需要操作的哪些属性？

It is necessary that both ⊗
 and ⊙
 were associative, because to calculate a function on a segment (operation ⊙
), it is necessary to combine it from the left and right sides, and to change it on a segment, two functions must be combined (old and new) in node (operation ⊗
).
两者都必须 ⊗
 和 ⊙
 是关联的，因为要计算一个段上的函数（操作 ⊙
 ），需要从左右两侧组合起来，要在一个段上改变它，必须在节点中组合（旧的和新的）两个函数（操作 ⊗
 ）。
⊗
 needs to be commutative (if it is not, then you need to use the propagation technique, which we will look at later).
⊗
 需要是可交换的（如果不是，那么您需要使用传播技术，我们稍后会讨论）。
It is necessary that ⊗
 be distributive relative to ⊙
, that is, the equality (𝑎⊗𝑥)⊙(𝑏⊗𝑥)=(𝑎⊙𝑏)⊗𝑥
 is true. For example, for requests add and min, we used the fact that 𝑚𝑖𝑛(𝑎+𝑥,𝑏+𝑥)=𝑚𝑖𝑛(𝑎,𝑏)+𝑥
.
有必要的是 ⊗
 相对于具有分配性 ⊙
 ，即平等 (𝑎⊗𝑥)⊙(𝑏⊗𝑥)=(𝑎⊙𝑏)⊗𝑥
 是真的。例如，对于请求add和min ，我们使用了以下事实： 𝑚𝑖𝑛(𝑎+𝑥,𝑏+𝑥)=𝑚𝑖𝑛(𝑎,𝑏)+𝑥
 。
Examples of operations matching the conditions above.
符合上述条件的操作示例。

𝚖𝚘𝚍𝚒𝚏𝚢∗+&𝚌𝚊𝚕𝚌+𝑚𝑖𝑛,𝑚𝑎𝑥|
Note that the operations modify = add and calc = sum can also be processed using the segment tree, only for the request calc the sum on the segment must be multiplied by its length, since (𝑎+𝑥)+(𝑏+𝑥)=(𝑎+𝑏)+2𝑥
. By multiplying the value by the length of the segment, we retained the distributivity condition.
请注意，操作“modify = add”和“calc = sum”也可以使用线段树进行处理，仅对于请求计算，线段上的总和必须乘以其长度，因为 (𝑎+𝑥)+(𝑏+𝑥)=(𝑎+𝑏)+2𝑥
 。通过将该值乘以线段的长度，我们保留了分布性条件。

Lazy propagation  惰性传播
If the operation in the modify request is not commutative, then we will use the lazy propagation technique again.
如果修改请求中的操作不可交换，那么我们将再次使用惰性传播技术。
We will maintain the order of operations by pushing old operations deeper into the tree. This technique was covered in the last step. Also, when entering the node, we will push the change into children, and when exiting the node, we will recalculate the value from the children.
我们将通过将旧操作推入树的更深处来维持操作的顺序。该技术已在最后一步中介绍。另外，当进入节点时，我们会将更改推送到子节点中，而当退出节点时，我们将从子节点中重新计算值。

This is how the propagation from the selected node occurs.
这就是从选定节点进行传播的方式。