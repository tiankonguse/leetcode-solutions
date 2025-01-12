Disjoint Sets Union. Part 1.
不相交集并集。第 1 部分。
DSU is a data structure that supports disjoint sets on 𝑛
 elements and allows two type of queries:
DSU 是一种支持不相交集的数据结构 𝑛
 元素并允许两种类型的查询：
get(𝑎
) — return the identifier of the set to which 𝑎
 belongs to;
得到（ 𝑎
 ) — 返回集合的标识符 𝑎
 属于；
union(𝑎
, 𝑏
) — join two sets that contain 𝑎
 and 𝑏
.
联盟（ 𝑎
 , 𝑏
 ) — 连接两个包含以下内容的集合 𝑎
 和 𝑏
 。
For example, when we call get(𝑎
) and get(𝑏
), we can compare whether 𝑎
 and 𝑏
 are in the same set.
例如，当我们调用get( 𝑎
 )并得到( 𝑏
 ) ，我们可以比较是否 𝑎
 和 𝑏
 属于同一组。

What is the simplest way to define the identifier of the set? — As an identifier, we can choose the leader of the set.
定义集合标识符的最简单方法是什么？ — 作为标识符，我们可以选择集合的领导者。

Let us maintain an array 𝑝
, where 𝑝[𝑎]
 is the identifier (the leader) of a set to which 𝑎
 belongs to.
让我们维护一个数组 𝑝
 ， 在哪里 𝑝[𝑎]
 是一个集合的标识符（领导者） 𝑎
 属于.

Let us consider the pseudo-code of two functions.
让我们考虑两个函数的伪代码。

init():
  p = new int[n]
  for i in 1..n:
    p[i] = i

get(a):
  return p[a]

union(a, b):
  a = p[a]
  b = p[b]
  for i in 1..n:
    if p[i] == a:
      p[i] = b
The function get(𝑎
) just returns the leader of a set, and the function union(𝑎
, 𝑏
) takes the leaders of both sets and set 𝑏
 as a leader of elements with the leader 𝑎
.
函数获取（ 𝑎
 )只是返回集合的首领，而函数union( 𝑎
 , 𝑏
 )取两个集合和集合的领导者 𝑏
 作为元素的领导者与领导者 𝑎
 。

Unfortunately, this algorithm is too slow: get works in 𝑂(1)
, however, union works in 𝑂(𝑛)
. Is there a way to improve the algorithm?
不幸的是，这个算法太慢了： get可以在 𝑂(1)
 然而，工会工作于 𝑂(𝑛)
 。有没有办法改进算法？

Let us consider the simplest idea — let us iterate not over all the elements, but over the elements with the leader 𝑎
. For that, for each leader, we will maintain a linked list 𝑙[𝑎]
. When we have to unite two sets, we will just link two lists together.
让我们考虑最简单的想法 - 让我们不迭代所有元素，而是迭代具有领导者的元素 𝑎
 。为此，对于每个领导者，我们将维护一个链表 𝑙[𝑎]
 。当我们必须合并两个集合时，我们只需将两个列表链接在一起即可。

init():
  p = new int[n]
  l = new List[n]
  for i in 1..n:
    p[i] = i
    l[i] = { i }

get(a):
  return p[a]

union(a, b):
  a = p[a]
  b = p[b]
  for x in l[a]:
    p[x] = b
  l[b].append(l[a])
Now, get(𝑎
) works in 𝑂(1)
 and union(𝑎
, 𝑏
) works in 𝑂(|𝑙[𝑎]|)
. Unfortunately, this complexity is not good enough: it is possible to find an execution such that union will work in 𝑂(𝑛)
 in amortization. Consider this execution:
现在，得到（ 𝑎
 ）工作于 𝑂(1)
 和联盟（ 𝑎
 , 𝑏
 ）工作于 𝑂(|𝑙[𝑎]|)
 。不幸的是，这种复杂性还不够好：有可能找到一个执行，使union可以在 𝑂(𝑛)
 在摊销中。考虑这个执行：

union(1
, 2
), where |𝑙[1]|=1
 and |𝑙[2]|=1
,
联盟（ 1
 , 2
 ） ， 在哪里 |𝑙[1]|=1
 和 |𝑙[2]|=1
 ,
union(2
, 3
), where |𝑙[2]|=2
 and |𝑙[3]|=1
,
联盟（ 2
 , 3
 ） ， 在哪里 |𝑙[2]|=2
 和 |𝑙[3]|=1
 ,
union(3
, 4
), where |𝑙[3]|=3
 and |𝑙[4]|=1
,
联盟（ 3
 , 4
 ） ， 在哪里 |𝑙[3]|=3
 和 |𝑙[4]|=1
 ,
and so on.   等等。
All operations in total work in 1+2+3+…+(𝑛−1)=𝑂(𝑛2)
, and, thus, union still works in 𝑂(𝑛)
. How to improve it? Note that the main problem is that we always join the first set to the second one. But what if we join the smallest set to the largest? Then, the code of union becomes the following.
所有操作的总工作量为 1+2+3+…+(𝑛−1)=𝑂(𝑛2)
 ，因此， union仍然有效 𝑂(𝑛)
 。如何改进呢？请注意，主要问题是我们总是将第一组连接到第二组。但是如果我们将最小的集合与最大的集合连接起来会怎样呢？那么union的代码就变成了下面这样。
union(a, b):
  a = p[a]
  b = p[b]
  if size(l[a]) > size(l[b]):
    swap(a, b)
  for x in l[a]:
    p[x] = b
  l[b].append(l[a])
We compare two sets and if the set 𝑎
 is larger than the set 𝑏
 we swap them. Note that we can implement size(l[a]) in 𝑂(1)
 — for that we have to store the size of the list separately. How fast does this algorithm work? get(𝑎
) still works in 𝑂(1)
, but did we improve union(𝑎
, 𝑏
)? Let us calculate how many times we changed the leader of 𝑥
, i.e., the algorithm performs line p[x] = b. The first time we changed the leader of 𝑥
 is when we unite it with the larger set. This means that the size of the union is at least 2
. The second time we changed the leader of 𝑥
 is when we unite the set with the larger set of size at least 2
. This means that the size of the union is at least 4
. And so on. We change the leader of 𝑥
 only when we unite with the larger set. Since we unite all the sets together, we perform 𝑂(log𝑛)
 changes per element and, thus, the total cost is 𝑂(𝑛log𝑛)
. Since, there are 𝑛−1
 union operations, each of them works in 𝑂(log𝑛)
 in amortization.
我们比较两个集合，如果该集合 𝑎
 大于集合 𝑏
 我们交换它们。请注意，我们可以在中实现size(l[a]) 𝑂(1)
 ——为此我们必须单独存储列表的大小。该算法的运行速度有多快？得到（ 𝑎
 ）仍然工作在 𝑂(1)
 ，但是我们是否改进了union( 𝑎
 , 𝑏
 ） ？让我们计算一下我们更换了多少次领导 𝑥
 ，即算法执行行p[x] = b 。我们第一次更换领导者 𝑥
 就是当我们将它与更大的集合结合起来时。这意味着联合的大小至少为 2
 。第二次换领导了 𝑥
 是当我们至少将集合与较大的集合联合起来时 2
 。这意味着联合的大小至少为 4
 。等等。我们更换领导者 𝑥
 只有当我们与更大的群体联合起来时。由于我们将所有集合结合在一起，因此我们执行 𝑂(log𝑛)
 每个元素都会发生变化，因此总成本是 𝑂(𝑛log𝑛)
 。因为，有 𝑛−1
 工会运作，他们每个人都在 𝑂(log𝑛)
 在摊销中。

We explain how to improve the algorithm further.
我们解释如何进一步改进算法。

Disjoint Sets Union. Part 2.
不相交集并集。第 2 部分。
In the previous part we explained how to implement get(𝑎
) in 𝑂(1)
 and union(𝑎
, 𝑏
) in 𝑂(log𝑛)
 amortized. But can we reduce the complexity of union, while slowdown get a little bit? It appears to be possible, but we should treat the data structure another way. We need to store the elements another way rather than in linked lists — for example, we can store them in trees. We are already given an array 𝑝
: let us store there a parent of an element in a tree. If 𝑝[𝑎]
 is equal to 𝑎
, then 𝑎
 is a root and a leader of the corresponding set. Initially, each element is a root of its own set, i.e., 𝑝[𝑎]=𝑎
. To implement get, we just simply need to follow the parent links until we find the root. To implement union, we need to find the leaders of both sets and link one set to another.
在上一部分中我们解释了如何实现get( 𝑎
 ）在 𝑂(1)
 和联盟（ 𝑎
 , 𝑏
 ）在 𝑂(log𝑛)
 摊销。但是我们可以降低union的复杂性，同时稍微减慢速度吗？看起来是可能的，但我们应该以另一种方式对待数据结构。我们需要以另一种方式存储元素，而不是存储在链表中——例如，我们可以将它们存储在树中。我们已经给定了一个数组 𝑝
 ：让我们存储树中元素的父元素。如果 𝑝[𝑎]
 等于 𝑎
 ， 然后 𝑎
 是对应集合的根和领导者。最初，每个元素都是其自己集合的根，即 𝑝[𝑎]=𝑎
 。要实现get ，我们只需要简单地跟踪父链接，直到找到根。为了实现union ，我们需要找到两个集合的领导者并将一个集合链接到另一个集合。
get(a):
  while a != p[a]:
    a = p[a]
  return a

union(a, b):
  a = get(a)
  b = get(b)
  p[a] = b
Unfortunately, such an algorithm is subject to the problem discussed in the previous part: the total time of union operations can reach 𝑂(𝑛2)
. But we already know how to solve such an issue! For that, we have to join the smaller set to the larger one. When we unite two sets, elements of the smaller set now have one more link to the root.
不幸的是，这样的算法受到前一部分讨论的问题的影响：联合操作的总时间可以达到 𝑂(𝑛2)
 。但我们已经知道如何解决这样的问题了！为此，我们必须将较小的集合加入到较大的集合中。当我们合并两个集合时，较小集合的元素现在多了一个到根的链接。
It is not hard to show that for each element the total number of links to pass to reach the root cannot exceed 𝑂(log𝑛)
. Thus, we get that get and union works in 𝑂(log𝑛)
 (!!not in amortization!!). It is pretty simple to implement.
不难证明，对于每个元素，到达根节点所经过的链接总数不能超过 𝑂(log𝑛)
 。因此，我们得到get和union 的工作原理 𝑂(log𝑛)
 （！！不计入摊销！！）。实施起来非常简单。

union(a, b):
  a = get(a)
  b = get(b)
  if size[a] > size[b]:
    swap(a, b)
  p[a] = b
  size[b] += size[a]
How to improve the algorithm further? Note, that when we call get we find the root. Then, it is reasonable to update 𝑝[𝑎]
 to point to the root, so that next get will work faster. Operation get becomes the following.
如何进一步改进算法？请注意，当我们调用get时，我们找到了根。那么更新就合理了 𝑝[𝑎]
 指向根，以便下一次get工作得更快。 get操作变成如下。

get(a):
  if p[a] != a:
    p[a] = get(p[a])
  return p[a]
We rewrote the function in a recursive manner. If 𝑎
 is a root, then the result is 𝑝[𝑎]
, otherwise, we set 𝑝[𝑎]
 to the root. This heuristic is named path-compression.
我们以递归方式重写了该函数。如果 𝑎
 是一个根，那么结果是 𝑝[𝑎]
 ，否则，我们设置 𝑝[𝑎]
 到根。这种启发式方法称为路径压缩。

It appears that if we apply both heuristics: the path-compression heuristic and the link-small-to-large heuristic, we get that get and union work in 𝑂(𝛼(𝑚,𝑛))
 time amortized, where 𝛼(𝑚,𝑛)
 is the inverse Ackermann function, 𝑚
 is the number of performed operations get and 𝑛
 is the number of elements.
看来，如果我们应用两种启发式：路径压缩启发式和从小到大链接启发式，我们就可以得到get和union 的工作 𝑂(𝛼(𝑚,𝑛))
 摊销时间，其中 𝛼(𝑚,𝑛)
 是阿克曼反函数， 𝑚
 是执行的操作数get和 𝑛
 是元素的数量。

To give the intuition on how slow the inverse Ackermann function rises, we look at 𝑂(log∗𝑛)
 that rises a little bit faster. This function means how many times we should take the binary logarithm of 𝑛
 to get a value smaller than one. Consider an example. Suppose we take a very large number — 265536
 and calculate its log∗
. 265536→65536=216→16=24→4=22→2→1→0
. In total we get that log∗265536=6
. So, we can suppose that for all reasonable 𝑛
 this function is almost constant, while the inverse Ackermann function rises even slower!
为了直观地了解反阿克曼函数上升的速度有多慢，我们看一下 𝑂(log∗𝑛)
 上升得快一点。这个函数的意思是我们应该取多少次二进制对数 𝑛
 得到一个小于一的值。考虑一个例子。假设我们取一个非常大的数字 - 265536
 并计算其 log∗
 。 265536→65536=216→16=24→4=22→2→1→0
 。总共我们得到了 log∗265536=6
 。所以，我们可以假设对于所有合理的 𝑛
 这个函数几乎是恒定的，而反阿克曼函数上升得更慢！

Disjoint Sets Union. Thoughts.
不相交集并集。想法。
It appears that one can implement get in Java and C++ in one line using the ternary conditional operator.
看来可以使用三元条件运算符在一行中实现 Java 和 C++ 中的get 。
get(a):
  return p[a] = (p[a] == a ? a : get(p[a]))
Typically, the operation union is implemented using rank heuristic instead of small-to-large one: we maintain the rank 𝑟
 of sets and also link the smallest to largest. The code becomes very clean without swap operation, which is not supported by Java.
通常，操作并集是使用排名启发式而不是从小到大的方式实现的：我们维护排名 𝑟
 集合并链接最小到最大。代码变得非常干净，没有Java不支持的交换操作。

union(a, b):
  a = get(a)
  b = get(b)
  if r[a] == r[b]:
    r[a]++
  if r[a] > r[b]:
    p[b] = a
  else:
    p[a] = b
Except for maintaining the sets, we can support associative and commutative functions. An operation ⊗
 is associative, if its result does not depend on the order of application, i.e., (𝑎⊗𝑏)⊗𝑐=𝑎⊗(𝑏⊗𝑐)
. An operation ⊗
 is commutative, if its result does not depend on the order of the arguments, i.e., 𝑎⊗𝑏=𝑏⊗𝑎
. For example, we can maintain sum or minimum on elements of a set. Then, the code of union becomes the following. Of course, arrays sum and min should be properly initialized.
除了维护集合之外，我们还可以支持关联函数和交换函数。一次手术 ⊗
 是结合的，如果它的结果​​不依赖于应用的顺序，即 (𝑎⊗𝑏)⊗𝑐=𝑎⊗(𝑏⊗𝑐)
 。一次手术 ⊗
 是可交换的，如果它的结果​​不依赖于参数的顺序，即 𝑎⊗𝑏=𝑏⊗𝑎
 。例如，我们可以维护集合元素的总和或最小值。那么union的代码就变成了下面这样。当然，数组sum和min应该正确初始化。

union(a, b):
  a = get(a)
  b = get(b)
  if r[a] == r[b]:
    r[a]++
  if r[a] > r[b]:
    p[b] = a
    sum[a] += sum[b]
    min[a] = min(min[a], min[b])
  else:
    p[a] = b
    sum[b] += sum[a]
    min[b] = min(min[a], min[b])