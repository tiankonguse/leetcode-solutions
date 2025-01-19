ITMO Academy: pilot course » Disjoint Sets Union » Step 3
ITMO学院：飞行员赛车 » 不相交集并集 » 步骤3

Mo's algorithm and DSU  Mo的算法和DSU
Consider the following problem. Suppose you are given 𝑚
 edges. You have to answer 𝑘
 queries of the form: how many connected components are in a graph that consists of edges from 𝑙
-th to 𝑟
-th. The simplest solution is to create new DSU per query and populate it with edges [𝑙,𝑟)
, decreasing the number of components by one on the successful insertion of an edge. Unfortunately, this solution is obviously slow. Can we use the fact that all the queries are given in advance? It appears to be possible with Mo's algorithm.
考虑以下问题。假设你被给予 𝑚
 边缘。你必须回答 𝑘
 形式的查询：由边组成的图中有多少个连接的组件 𝑙
 -th 到 𝑟
 -th。最简单的解决方案是为每个查询创建新的 DSU 并用边填充它 [𝑙,𝑟)
 ，在成功插入一条边时将组件数量减少 1。不幸的是，这个解决方案显然很慢。我们可以利用所有查询都是提前给出的事实吗？ Mo的算法似乎可以实现。
As the first step we split all the edges into 𝑚‾‾√
 blocks of size 𝑚‾‾√
. Then, we cluster the queries onto the blocks: we add all the queries with the left end in the first block to the first block; we add all the queries with the left end in the second block to the second block; and so on. In the 𝑖
-th block we store the queries [𝑙𝑖1,𝑟𝑖1),…,[𝑙𝑖𝑘𝑖,𝑟𝑖𝑘𝑖)
, with the left end 𝑙𝑖𝑗
 in the 𝑖
-th block. Then, in each block, we sort the queries by their right end.
作为第一步，我们将所有边分成 𝑚‾‾√
 大小块 𝑚‾‾√
 。然后，我们将查询聚集到块上：将第一个块中左端的所有查询添加到第一个块中；我们将第二个块中左端的所有查询添加到第二个块中；等等。在 𝑖
 我们存储查询的第一个块 [𝑙𝑖1,𝑟𝑖1),…,[𝑙𝑖𝑘𝑖,𝑟𝑖𝑘𝑖)
 ，与左端 𝑙𝑖𝑗
 在 𝑖
 第-块。然后，在每个块中，我们按查询的右端对查询进行排序。

We preprocess the queries. Suppose we are provided with the magical data structure: a persistent DSU that can be saved, then perform several queries, and, finally, rollback to the checkpoint. Using this data structure we process the queries in the following order.
我们预处理查询。假设我们提供了神奇的数据结构：一个可以保存的持久DSU，然后执行多次查询，最后回滚到检查点。使用此数据结构，我们按以下顺序处理查询。
We start by considering the requests of the first block. If the left and the right ends lie in the first block, we perform the query straightforwardly: save DSU, apply requests, get an answer, and rollback. Thus, we suppose that 𝑟11
 exceeds 𝑚‾‾√
. We take an empty DSU and add all edges from [𝑚‾‾√,𝑟11)
. Then, we save DSU, add edges from [𝑙11,𝑚‾‾√)
, get an answer to the first query of the first block, and rollback to the checkpoint. Then, we add edges from [𝑟11,𝑟12)
, save DSU, add edges from [𝑙12,𝑚‾‾√)
, get an answer to the second query of the first block, and rollback to the checkpoint. In a similar manner we perform all other queries: for 𝑖
-th query we add edges from [𝑟1𝑖−1,𝑟1𝑖)
, save DSU, add edges from [𝑙1𝑖,𝑚‾‾√)
, get an answer to the 𝑖
-th query, and rollback to the checkpoint. After processing all the requests of the first block, we re-initialize DSU and apply the queries of the second block in a similar manner. Then, we process the requests of other blocks.
我们首先考虑第一个块的请求。如果左端和右端位于第一个块，我们直接执行查询：保存DSU，应用请求，得到答案，然后回滚。因此，我们假设 𝑟11
 超过 𝑚‾‾√
 。我们采用一个空的 DSU 并添加来自 [𝑚‾‾√,𝑟11)
 。然后，我们保存 DSU，添加边 [𝑙11,𝑚‾‾√)
 ，获取第一个块的第一个查询的答案，并回滚到检查点。然后，我们添加边缘 [𝑟11,𝑟12)
 ，保存DSU，添加边 [𝑙12,𝑚‾‾√)
 ，得到第一个块的第二个查询的答案，并回滚到检查点。以类似的方式，我们执行所有其他查询： 𝑖
 我们添加边的第一个查询 [𝑟1𝑖−1,𝑟1𝑖)
 ，保存DSU，添加边 [𝑙1𝑖,𝑚‾‾√)
 ，得到答案 𝑖
 -th 查询，并回滚到检查点。处理完第一个块的所有请求后，我们重新初始化 DSU 并以类似的方式应用第二个块的查询。然后，我们处理其他块的请求。

How to implement persistent DSU? At first, we put the path-compression heuristic aside and apply only small-to-large one. When we apply union we change only two memory cells: one in array 𝑝
 and one in array 𝑠𝑢𝑚
. Thus, we can simply store on a stack which cells we modified and how. By that, the rollback operation simply takes the modifications from the stack and applies them. Note that without the path-compression heuristic get and union work in 𝑂(log𝑛)
 time.
如何实现持久化DSU？首先，我们将路径压缩启发式放在一边，仅应用从小到大的启发式。当我们应用联合时，我们只改变两个内存单元：一个在数组中 𝑝
 和数组中的一个 𝑠𝑢𝑚
 。因此，我们可以简单地将我们修改的单元格以及修改方式存储在堆栈上。这样，回滚操作只需从堆栈中获取修改并应用它们。请注意，如果没有路径压缩启发式get和union工作 𝑂(log𝑛)
 时间。

Let us calculate the complexity of the resulting algorithm. At first, we sort the queries by the right end — 𝑂(𝑘log𝑘)
. When we processed the queries of the first block, the right end moved at most 𝑚
 times, while the left end moved at maximum by 𝑂(𝑚‾‾√)
 for each request. Thus, the application of the requests of the first block takes 𝑂(𝑘1𝑚‾‾√log𝑛+𝑚log𝑛)
. Summing this over all blocks we get the total complexity 𝑂((𝑘+𝑚)𝑚‾‾√log𝑛)
. This is faster than our first straightforward solution.
让我们计算所得算法的复杂度。首先，我们按右端对查询进行排序 - 𝑂(𝑘log𝑘)
 。当我们处理第一个块的查询时，右端最多移动了 𝑚
 次，而左端最大移动了 𝑂(𝑚‾‾√)
 对于每个请求。因此，第一个块的请求的应用需要 𝑂(𝑘1𝑚‾‾√log𝑛+𝑚log𝑛)
 。将所有块相加，我们得到总复杂度 𝑂((𝑘+𝑚)𝑚‾‾√log𝑛)
 。这比我们第一个简单的解决方案要快。

Dynamic Connectivity Offline
离线动态连接
Dynamic Connectivity Problem is a problem in which one should answer queries of three types:
动态连接问题是一个需要回答三种类型的查询的问题：
add(𝑢
, 𝑣
) — add an edge 𝑢−𝑣
 into the graph;
添加（ 𝑢
 , 𝑣
 ) — 添加一条边 𝑢−𝑣
 进入图表；
remove(𝑢
, 𝑣
) — add an edge 𝑢−𝑣
 into the graph;
消除（ 𝑢
 , 𝑣
 ) — 添加一条边 𝑢−𝑣
 进入图表；
get(𝑢
, 𝑣
) — check whether two vertices are connected.
得到（ 𝑢
 , 𝑣
 ) — 检查两个顶点是否相连。
One of the well-known solutions to this problem was proposed by Holm et al. in "Poly-Logarithmic Deterministic Fully-Dynamic Algorithms for Connectivity, Minimum Spanning Tree, 2-Edge, and Biconnectivity" in which all operations work in amortized 𝑂(log2𝑛)
. Unfortunately, this algorithm is quite complicated and hard to implement. Can we relax the problem a little bit and get a simpler algorithm with similar asymptotics? It appears to be possible: for that, we have to know all the requests in advance.
Holm 等人提出了解决此问题的著名解决方案之一。在“用于连接、最小生成树、2 边和双连接的多对数确定性全动态算法”中，所有操作均以摊销方式进行 𝑂(log2𝑛)
 。不幸的是，这个算法相当复杂并且难以实现。我们能否稍微放松一下问题并获得具有类似渐近性的更简单的算法？这似乎是可能的：为此，我们必须提前了解所有请求。

Since now the requests are given in advance, each of them has a new parameter 𝑡
 — the time of the application. Suppose that each query on edge addition has a paired query on edge removal. Note that we can achieve it by adding the necessary removal queries at the end. Then we replace a pair of queries add(𝑙
, 𝑢
, 𝑣
) and remove(𝑟
, 𝑢
, 𝑣
) into one special request edge(𝑙
, 𝑟
, 𝑢
, 𝑣
) — edge 𝑢−𝑣
 exists in a graph from time 𝑙
 to time 𝑟
.
由于现在请求是提前给出的，因此每个请求都有一个新参数 𝑡
 — 申请时间。假设每个关于边缘添加的查询都有一个关于边缘删除的配对查询。请注意，我们可以通过在末尾添加必要的删除查询来实现它。然后我们替换一对查询add( 𝑙
 , 𝑢
 , 𝑣
 )并删除( 𝑟
 , 𝑢
 , 𝑣
 )进入一个特殊请求边( 𝑙
 , 𝑟
 , 𝑢
 , 𝑣
 ） - 边缘 𝑢−𝑣
 存在于图表中的时间 𝑙
 到时间 𝑟
 。

How does the algorithm work? We divide the timeline into halves, then again into halves and etc., until the segments become of length 1
. For each segment, we maintain DSU on the graph consisting of edges that cover the whole segment. Thus, when we get to the lowest level on which a segment contains only one moment in time 𝑡
, we get DSU for all the edges that belong to the graph at moment 𝑡
, and, by that, we can correctly answer a query get.
该算法是如何工作的？我们将时间线分成两半，然后再分成两半，依此类推，直到片段变得足够长 1
 。对于每个段，我们在由覆盖整个段的边组成的图上维护 DSU。因此，当我们到达一个片段仅包含一个时刻的最低级别时 𝑡
 ，我们得到此时属于图的所有边的 DSU 𝑡
 ，这样我们就可以正确回答查询get 。


On the picture above you can see three requests edge and two requests get, depicted as arrows. On the first level, we have the whole timeline. On the second level, we have two segments, none of which is covered by some query. On the third level, we have four segments and, for example, the third one is covered by two edge requests, which we should apply to our DSU. At the lowest level, each segment has length one and we can answer get queries. Let us write the pseudo-code.
在上图中，您可以看到三个请求edge和两个请求get ，如箭头所示。在第一层，我们有完整的时间表。在第二层，我们有两个段，其中任何一个都没有被某些查询覆盖。在第三层，我们有四个段，例如，第三个段由两个边缘请求覆盖，我们应该将其应用于我们的 DSU。在最低级别，每个段的长度为一，我们可以回答get查询。让我们编写伪代码。

work(l, r, queries):
  if l == r - 1:
    for q in queries:
      if q.type == get && q.t == l:
        q.answer = get(q.u) == get(q.v)
    return

  save DSU
  queries2 = {}
  for q in queries:
    if q.type == edge && [l, r) lies in [q.l, q.r):
      union(q.u, q.v)
    if (q.type == get && q.t in [l, r)) ||
        (q.type == edge && [l, r) intersects [q.l, q.r)):
      queries2.add(q)
  m = (l + r) / 2
  work(l, m, queries2)
  work(m, r, queries2)
  rollback DSU
At first, we check that we are on the lowest level, and if so, we answer on get request. Otherwise, we make a checkpoint in DSU and iterate through all the queries. If a query edge covers the current segment we add this edge into DSU. If the query intersects with the current segment we take it to the next level. In the end, we recursively call from two halves and, finally, rollback DSU.
首先，我们检查我们是否处于最低级别，如果是，我们就响应get请求。否则，我们在 DSU 中创建一个检查点并迭代所有查询。如果查询边覆盖当前段，我们会将此边添加到 DSU 中。如果查询与当前段相交，我们会将其带到下一个级别。最后，我们从两半递归调用，最后回滚DSU。

What is the complexity of such an algorithm? Let us count the total size of all queries2 arrays on one level. Note that each query can lie only in a constant number of arrays: if it covers the whole segment it is applied, otherwise, one of its ends lies in the segment. Since each query has at most two ends, the total size of queries2 arrays on one level does not exceed 𝑂(𝑚)
, where 𝑚
 is the total number of requests. There are log𝑚
 levels. Thus, we perform 𝑂(𝑚log𝑚)
 union and add operations. Since each union operation works in 𝑂(log𝑛)
, the total complexity of an algorithm is 𝑂(𝑚log𝑚log𝑛)
.
这种算法的复杂度是多少？让我们计算一级上所有query2数组的总大小。请注意，每个查询只能位于恒定数量的数组中：如果它覆盖了整个段，则应用它，否则，其末端之一位于该段中。由于每个查询最多有两端，因此一级上的queries2数组的总大小不超过 𝑂(𝑚)
 ， 在哪里 𝑚
 是请求总数。有 log𝑚
 水平。因此，我们执行 𝑂(𝑚log𝑚)
 联合和添加操作。由于每个工会的运作都在 𝑂(log𝑛)
 ，算法的总复杂度是 𝑂(𝑚log𝑚log𝑛)
 。