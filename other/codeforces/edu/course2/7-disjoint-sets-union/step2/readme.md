Problem with people  与人相处有问题
Suppose that there are 𝑛
 people standing on positions from 1
 to 𝑛
. There are two types of queries: the person at position 𝑖
 goes away and find the nearest person to the right for position 𝑝
 that did not leave.
假设有 𝑛
 人们站在立场上 1
 到 𝑛
 。有两种类型的查询： 所在位置的人 𝑖
 走开并找到右边最近的人来定位 𝑝
 那并没有离开。
Consider an example. Initially, each element points to itself.
考虑一个例子。最初，每个元素都指向其自身。


When a person leaves, we change its pointer to the right neighbour. Then, when we ask for the nearest person to the right, we just have to follow the links to the right until we find a root, i.e., the element that points to itself.
当一个人离开时，我们将其指针更改为正确的邻居。然后，当我们询问右边最近的人时，我们只需沿着右边的链接，直到找到根，即指向自身的元素。


At the example, 2
 and 3
 go away and we link them to the right. Then, when we ask the second query at position 2
 we follow the links to the right until we find 4
.
在该示例中， 2
 和 3
 走开，我们将它们连接到右侧。然后，当我们在位置询问第二个查询时 2
 我们沿着右边的链接，直到找到 4
 。

It is clear that this algorithm is slow. Luckily for us, we can use the path-compression heuristic and a query will work in 𝑂(log𝑛)
 amortized. We can do it even faster. Note that when we unite two components the nearest person to the right is the maximal element in the set. We know how to maintain the maximum in DSU.
很明显这个算法很慢。幸运的是，我们可以使用路径压缩启发式，并且查询将在 𝑂(log𝑛)
 摊销。我们可以做得更快。请注意，当我们合并两个组件时，最右边的人是集合中的最大元素。我们知道如何保持 DSU 的最大值。

Minimal Spanning Tree  最小生成树
The most known application of DSU is Kruskal's algorithm to find the minimal spanning tree. The minimal spanning tree is a tree of smallest weight that connects all the vertices and is the subset of the weighted graph.
DSU 最著名的应用是 Kruskal 算法来查找最小生成树。最小生成树是连接所有顶点的权值最小的树，是带权图的子集。
Remind the lemma of the safe edge: let us split the set of vertices into two, 𝐴
 and 𝐵
, the minimal edge between sets 𝐴
 and 𝐵
 definitely belongs to the minimal spanning tree. From that, we can suggest to sort the edges and add them to the tree in that order. When we add an edge we check whether two vertices are not connected. If it is true, we add an edge, otherwise, we do nothing.
提醒安全边的引理：让我们将顶点集分成两部分， 𝐴
 和 𝐵
 ，集合之间的最小边 𝐴
 和 𝐵
 肯定属于最小生成树。由此，我们可以建议对边进行排序并按该顺序将它们添加到树中。当我们添加一条边时，我们会检查两个顶点是否未连接。如果为真，我们添加一条边，否则，我们什么都不做。
For example, below you can see the pseudocode of the algorithm that calculates the weight of the minimal spanning tree.
例如，下面您可以看到计算最小生成树权重的算法的伪代码。
sort(edges)

for e in edges:
  if get(e.u) != get(e.v):
    union(e.u, e.v)
    w += e.w
The complexity of this algorithm is 𝑂(𝑚log𝑚)
.
该算法的复杂度为 𝑂(𝑚log𝑚)
 。
The bipartition test  二分法测试
Suppose we are given requests to add an edge and we have to answer after which edge the graph stops being bipartite. A graph is bipartite, if its vertices can be split into two sets, named parts, such that there does not exist an edge inside a part.
假设我们收到添加一条边的请求，并且我们必须回答在哪条边之后图不再是二分的。如果一个图的顶点可以分为两个集合（称为部分），并且部分内不存在边，则该图是二分图。
How do we check that the graph stops being bipartite? Two vertices belong to the same part if any path between them has an even length. Let us reformulate that a little bit. For that, we choose a special vertex ℓ
 in a connected component. Then, two vertices 𝑎
 and 𝑏
 belong to the same part, if the distances between 𝑎
 and ℓ
, and between 𝑏
 and ℓ
 are of the same parity, i.e., the path between 𝑎
 and 𝑏
 has even length. It is almost as our DSU, however, now we have to maintain the parity of the path to the leader. To do this we can store the parity of the distance to the parent in a special array 𝑙𝑒𝑛
. Then, how does get work? Now, it returns a pair <the leader, the parity of the distance to the leader>.
我们如何检查图是否不再是二分图？如果两个顶点之间的任何路径长度相等，则它们属于同一部分。让我们稍微重新表述一下。为此，我们选择一个特殊的顶点 ℓ
 在连接的组件中。然后，两个顶点 𝑎
 和 𝑏
 属于同一部分，如果之间的距离 𝑎
 和 ℓ
 ，和之间 𝑏
 和 ℓ
 具有相同的奇偶性，即之间的路径 𝑎
 和 𝑏
 长度均匀。这几乎就像我们的 DSU 一样，但是现在我们必须保持通往领导者的路径的平等。为此，我们可以将到父级的距离奇偶校验存储在一个特殊的数组中 𝑙𝑒𝑛
 。那么，如何上班呢？现在，它返回一对< 领导者，即到领导者 > 的距离的奇偶校验。

get(a):
  if p[a] == a:
    return <a, 0>
  val = get(p[a])
  p[a] = val.fst
  len[a] = (len[a] + val.snd) % 2
  return <p[a], len[a]>
We start by checking 𝑎
 to be a root. If it is a root, we return <a, 0>, i.e., the root 𝑎
 and the distance 0
. Otherwise, we call get and retrieve 𝑣𝑎𝑙
: the root and the parity of the distance from the parent to the root. We set 𝑝[𝑎]
 to 𝑣𝑎𝑙.𝑓𝑠𝑡
 since it is the root. However, the distance to the parent has changed: now it should be the distance to the root which is equal to the distance to the old parent plus the distance from the old parent to the root, 𝑣𝑎𝑙.𝑠𝑛𝑑
.
我们首先检查 𝑎
 成为根。如果是根，我们返回<a, 0> ，即根 𝑎
 和距离 0
 。否则，我们调用get并检索 𝑣𝑎𝑙
 ：根和从父节点到根的距离的奇偶性。我们设定 𝑝[𝑎]
 到 𝑣𝑎𝑙.𝑓𝑠𝑡
 因为它是根。然而，到父级的距离已经改变：现在应该是到根的距离，等于到旧父级的距离加上旧父级到根的距离， 𝑣𝑎𝑙.𝑠𝑛𝑑
 。

Now, how to implement union? Suppose that we perform a request to connect two vertices 𝑎
 and 𝑏
. Let 𝑟𝑎
 and 𝑟𝑏
 be the leaders of vertices 𝑎
 and 𝑏
, respectively. We connect 𝑎
 and 𝑏
 with an edge, and in union we set up a link between the leaders and write the parity of the distance between 𝑟𝑎
 and 𝑟𝑏
. Note that the parity of the distance between 𝑟𝑎
 and 𝑟𝑏
 equals to the parity of the sum: the distance from 𝑟𝑎
 to 𝑎
, an edge between 𝑎
 and 𝑏
, and the distance from 𝑏
 to 𝑟𝑏
. Then, the pseudocode of union becomes the following.
现在，如何实现union 呢？假设我们执行连接两个顶点的请求 𝑎
 和 𝑏
 。让 𝑟𝑎
 和 𝑟𝑏
 成为顶点的领导者 𝑎
 和 𝑏
 ， 分别。我们连接 𝑎
 和 𝑏
 具有边缘，并且在联盟中我们在领导者之间建立了联系并写出之间的距离平价 𝑟𝑎
 和 𝑟𝑏
 。请注意，之间的距离奇偶性 𝑟𝑎
 和 𝑟𝑏
 等于总和的奇偶校验：距离 𝑟𝑎
 到 𝑎
 ，之间的一条边 𝑎
 和 𝑏
 ，以及距离 𝑏
 到 𝑟𝑏
 。那么union的伪代码就变成了下面这样。

union(a, b):
  valA = get(a)
  valB = get(b)
  if size[valA.fst] > size[valB.fst]:
    swap(valA, valB)
  p[valA.fst] = valB.fst
  len[valA.fst] = (1 + valA.snd + valB.snd) % 2
  size[valB.fst] += size[valA.fst]