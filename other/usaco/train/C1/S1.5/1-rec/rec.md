# Search Techniques 搜索技巧


#### Sample Problem: _n_ Queens [Traditional]  
示例问题：n 个皇后 [传统]

Place _n_ queens on an _n x n_ chess board so that no queen is attacked by another queen.  
将 n 个皇后放在 n x n 个棋盘上，以便没有皇后受到另一个皇后的攻击。

#### Depth First Search (DFS)  
深度优先搜索（DFS）

The most obvious solution to code is to add queens recursively to the board one by one, trying all possible queen placements.  
最明显的代码解决方案是将皇后一一递归地添加到棋盘上，尝试所有可能的皇后放置位置。  
It is easy to exploit the fact that there must be exactly one queen in each column: at each step in the recursion, just choose where in the current column to put the queen.  
很容易利用每一列中必须有一个皇后这一事实：在递归的每一步中，只需选择当前列中放置皇后的位置即可。  

     1 search(col)  
     2     if filled all columns  
     3         print solution and exit   

     4   for each row  
     5       if board(row, col) is not attacked  
     6            place queen at (row, col)  
     7            search(col+1)  
     8            remove queen at (row, col)


Calling search(0) begins the search. This runs quickly, since there are relatively few choices at each step: once a few queens are on the board, the number of non-attacked squares goes down dramatically.  
调用 search(0) 开始搜索。这个过程运行得很快，因为每一步的选择相对较少：一旦棋盘上出现了几个皇后，未被攻击的方格数量就会急剧下降。

This is an example of _depth first search_, because the algorithm iterates down to the bottom of the search tree as quickly as possible: once _k_ queens are placed on the board, boards with even more queens are examined before examining other possible boards with only _k_ queens. This is okay but sometimes it is desirable to find the simplest solutions before trying more complex ones.  
这是深度优先搜索的一个示例，因为该算法会尽快迭代到搜索树的底部：一旦将 k 个皇后放置在棋盘上，就会先检查具有更多皇后的棋盘，然后再检查仅具有 k 个皇后的其他可能棋盘皇后。这没关系，但有时在尝试更复杂的解决方案之前最好先找到最简单的解决方案。

Depth first search checks each node in a search tree for some property. The search tree might look like this:  
深度优先搜索检查搜索树中每个节点的某些属性。搜索树可能如下所示：  
![](https://train.usaco.org/usaco/TEXT/rec.tree1.gif)  
The algorithm searches the tree by going down as far as possible and then backtracking when necessary, making a sort of outline of the tree as the nodes are visited. Pictorially, the tree is traversed in the following manner:  
该算法通过尽可能向下搜索树，然后在必要时回溯，在访问节点时形成树的轮廓。如图所示，树的遍历方式如下：  
![](https://train.usaco.org/usaco/TEXT/rec2.gif)

##### Complexity  复杂

Suppose there are _d_ decisions that must be made. (In this case _d=n_, the number of columns we must fill.) Suppose further that there are C choices for each decision. (In this case _c=n_ also, since any of the rows could potentially be chosen.) Then the entire search will take time proportional to $c^d$, i.e., an exponential amount of time. This scheme requires little space, though: since it only keeps track of as many decisions as there are to make, it requires only O(_d_) space.  
假设必须做出 d 个决定。 （在这种情况下，d=n，我们必须填充的列数。）进一步假设每个决策有 C 个选择。 （在这种情况下，c=n 也是如此，因为任何行都可能被选择。）然后整个搜索将花费与 $c^d$ 成比例的时间，即指数时间量。不过，该方案需要的空间很小：因为它只跟踪要做的决策，所以它只需要 O(d) 空间。

#### Sample Problem: Knight Cover [Traditional]  
示例问题：Knight Cover [传统]

Place as few knights as possible on an _n x n_ chess board so that every square is attacked. A knight is not considered to attack the square on which it sits.  
在 n x n 棋盘上放置尽可能少的马，以便每个方格都受到攻击。马不被视为攻击其所在的方格。

##### Breadth First Search (BFS)  
广度优先搜索（BFS）

In this case, it is desirable to try all the solutions with only _k_ knights before moving on to those with _k+1_ knights. This is called `breadth first search`. The usual way to implement breadth first search is to use a queue of states:  
在这种情况下，最好先尝试仅使用 k 个骑士的所有解决方案，然后再转向使用 k+1 个骑士的解决方案。这称为广度优先搜索。实现广度优先搜索的常用方法是使用状态队列：  

     1 process(state)  
     2     for each possible next state from this one  
     3         enqueue next state   

     4 search()  
     5     enqueue initial state  
     6     while !empty(queue)  
     7         state = get state from queue  
     8         process(state)

This is called breadth first search because it searches an entire row (the breadth) of the search tree before moving on to the next row. For the search tree used previously, breadth first search visits the nodes in this order:  
这称为广度优先搜索，因为它在移动到下一行之前搜索搜索树的整行（广度）。对于之前使用的搜索树，广度优先搜索按以下顺序访问节点：  
![](https://train.usaco.org/usaco/TEXT/rec3.gif)  
It first visits the top node, then all the nodes at level 1, then all at level 2, and so on.  
它首先访问顶部节点，然后访问级别 1 的所有节点，然后访问级别 2 的所有节点，依此类推。

##### Complexity  复杂

Whereas depth first search required space proportional to the number of decisions (there were _n_ columns to fill in the _n_ queens problem, so it took O(_n_) space), breadth first search requires space exponential in the number of choices.  
深度优先搜索所需的空间与决策数量成正比（有 n 列来填充 n 个皇后问题，因此需要 O(n) 空间），而广度优先搜索则需要与选择数量呈指数关系的空间。

If there are _c_ choices at each decision and _k_ decisions have been made, then there are $c^k$ possible boards that will be in the queue for the next round. This difference is quite significant given the space restrictions of some programming environments.  
如果每个决策有 c 个选择并且已做出 k 个决策，则有 $c^k$ 个可能的板将进入下一轮的队列。考虑到某些编程环境的空间限制，这种差异非常显着。

[Some details on why $c^k$: Consider the nodes in the recursion tree. The zeroeth level has 1 nodes. The first level has c nodes. The second level has $c^2$ nodes, etc. Thus, the total number of nodes on the k-th level is $c^k$.]  
[关于为什么 $c^k$ 的一些细节：考虑递归树中的节点。第 0 层有 1 个节点。第一层有c个节点。第二层有 $c^2$ 个节点，依此类推。因此，第 k 层的节点总数为 $c^k$ 。]

##### Depth First with Iterative Deepening (ID)  
深度优先与迭代深化 (ID)

An alternative to breadth first search is _iterative deepening_. Instead of a single breadth first search, run D depth first searches in succession, each search allowed to go one row deeper than the previous one.  
广度优先搜索的替代方法是迭代深化。不是单一的广度优先搜索，而是连续运行 D 深度优先搜索，每个搜索允许比前一个搜索更深一行。  
That is, the first search is allowed only to explore to row 1, the second to row 2, and so on. This **simulates** a breadth first search at a cost in time but a savings in space.  
也就是说，第一次搜索仅允许探索第 1 行，第二次搜索则探索第 2 行，依此类推。这模拟了广度优先搜索，但花费了时间但节省了空间。  

     1 truncated_dfsearch(hnextpos, depth)  
     2     if board is covered  
     3         print solution and exit   

     4     if depth == 0  
     5         return   

     6     for i from nextpos to n*n  
     7         put knight at i  
     8         truncated_dfsearch(i+1, depth-1)  
     9         remove knight at i   

    10 dfid_search  
    11     for depth = 0 to max_depth  
    12        truncated_dfsearch(0, depth)

##### Complexity  复杂

The space complexity of iterative deepening is just the space complexity of depth first search: O(_n_). The time complexity, on the other hand, is more complex. Each truncated depth first search stopped at depth _k_ takes $c^k$ time. Then if _d_ is the maximum number of decisions, depth first iterative deepening takes $c0 + c1 + c2 + ... + cd$ time.  
迭代加深的空间复杂度就是深度优先搜索的空间复杂度：$O(n)$。另一方面，时间复杂度更复杂。每个在深度 k 停止的截断深度优先搜索需要 $c^k$ 时间。那么如果 d 是最大决策数，则深度优先迭代加深需要 $c0 + c1 + c2 + ... + cd$ 时间。

If _c = 2_, then this sum is _cd+1 - 1_, about twice the time that breadth first search would have taken. When _c_ is more than two (i.e., when there are many choices for each decision), the sum is even less: iterative deepening cannot take more than twice the time that breadth first search would have taken, assuming there are always at least two choices for each decision.  
如果 c = 2，则该总和为 c d+1 - 1，大约是广度优先搜索所需时间的两倍。当 c 大于 2 时（即，当每个决策有很多选择时），总和甚至更小：迭代深化所花费的时间不能超过广度优先搜索所花费时间的两倍（假设总是有至少两个选择）对于每个决定。

#### Which to Use?  
使用哪个？

Once youve identified a problem as a search problem, its important to choose the right type of search. Here are some things to think about.  
一旦您将问题确定为搜索问题，选择正确的搜索类型就很重要。这里有一些需要考虑的事情。

##### In a Nutshell  
简而言之

| Search 搜索 | Time 时间 | Space 空间 | When to use 何时使用 |
| --- | --- | --- | --- |
| DFS | O(_c^k_) | O(_k_)  | Must search tree anyway, know the level the answers are on, or you aren't looking for the shallowest number.  无论如何都必须搜索树，知道答案所在的级别，否则您不是在寻找最浅的数字。 |
| BFS | O(_c^d_) | O(_c^d_) | Know answers are very near top of tree, or want shallowest answer.  知道答案非常接近树顶，或者想要最浅的答案。 |
| DFS+ID 深度优先+ID | O(_c^d_) | O(_d_) | Want to do BFS, don't have enough space, and can spare the time.  想做BFS，空间不够，可以抽出时间。 |

_d_ is the depth of the answer  
是答案的深度  
_k_ is the depth searched  
k 是搜索深度  
_d <= k_

Remember the ordering properties of each search. If the program needs to produce a list sorted shortest solution first (in terms of distance from the root node), use breadth first search or iterative deepening. For other orders, depth first search is the right strategy.  
记住每个搜索的排序属性。如果程序需要首先生成列表排序的最短解决方案（按照距根节点的距离），请使用广度优先搜索或迭代加深。对于其他订单，深度优先搜索是正确的策略。

If there isnt enough time to search the entire tree, use the algorithm that is more likely to find the answer. If the answer is expected to be in one of the rows of nodes closest to the root, use breadth first search or iterative deepening.  
如果没有足够的时间搜索整个树，请使用更有可能找到答案的算法。如果答案预计位于最接近根的节点行之一中，请使用广度优先搜索或迭代加深。  
Conversely, if the answer is expected to be in the leaves, use the simpler depth first search.  
相反，如果答案预计位于叶子中，请使用更简单的深度优先搜索。

Be sure to keep space constraints in mind. If memory is insufficient to maintain the queue for breadth first search but time is available, use iterative deepening.  
请务必牢记空间限制。如果内存不足以维持广度优先搜索的队列，但时间充足，则使用迭代加深。

#### Sample Problems  示例问题

##### Superprime Rib [USACO 1994 Final Round, adapted]  
Superprime Rib [USACO 1994 决赛，改编]

A number is called superprime if it is prime and every number obtained by chopping some number of digits from the right side of the decimal expansion is prime. For example, 233 is a superprime, because 233, 23, and 2 are all prime.  
如果一个数是素数，并且从小数展开式右侧截去一些数字得到的每个数字都是素数，则该数称为超素数。例如，233 是超素数，因为 233、23 和 2 都是素数。  
Print a list of all the superprime numbers of length _n_, for _n <= 9_. The number 1 is not a prime.  
打印长度为 n 的所有超素数的列表，其中 n <= 9。数字 1 不是素数。

For this problem, use depth first search, since all the answers are going to be at the _n_th level (the bottom level) of the search.  
对于此问题，请使用深度优先搜索，因为所有答案都将位于搜索的第 n 层（底层）。

##### Betsy's Tour [USACO 1995 Qualifying Round]  
贝特西之旅 [USACO 1995 资格赛]

A square township has been partitioned into _n 2_ square plots. The Farm is located in the upper left plot and the Market is located in the lower left plot. Betsy takes a tour of the township going from Farm to Market by walking through every plot exactly once.  
一个正方形的镇区被划分为 n 个 2 个正方形地块。农场位于左上地块，市场位于左下地块。贝特西从农场到市场，对小镇进行了一次游览，每个地块都只走一遍。  
Write a program that will count how many unique tours Betsy can take in going from Farm to Market for any value of _n <= 6_.  
编写一个程序，计算对于 n <= 6 的任何值，Betsy 从农场到市场可以进行多少次独特的旅行。

Since the number of solutions is required, the entire tree must be searched, even if one solution is found quickly. So it doesnt matter from a time perspective whether DFS or BFS is used. Since DFS takes less space, it is the search of choice for this problem.  
由于需要解决方案的数量，因此即使很快找到一个解决方案，也必须搜索整棵树。所以从时间角度来看，使用DFS还是BFS并不重要。由于DFS占用的空间较小，因此它是该问题的搜索选择。

##### Udder Travel [USACO 1995 Final Round; Piele]  
乳房旅行 [USACO 1995 决赛；皮埃勒]

The Udder Travel cow transport company is based at farm A and owns one cow truck which it uses to pick up and deliver cows between seven farms A, B, C, D, E, F, and G. The (commutative) distances between farms are given by an array.  
Udder Travel 奶牛运输公司位于农场 A，拥有一辆奶牛卡车，用于在七个农场 A、B、C、D、E、F 和 G 之间接送奶牛。农场之间的（交换）距离由一个数组给出。  
Every morning, Udder Travel has to decide, given a set of cow moving orders, the order in which to pick up and deliver cows to minimize the total distance traveled. Here are the rules:  
每天早上，Udder Travel 都必须根据一组奶牛移动订单来决定接收和运送奶牛的顺序，以最大限度地减少总行驶距离。规则如下：

*   The truck always starts from the headquarters at farm A and must return there when the day's deliveries are done.  
    卡车始终从 A 农场的总部出发，并且必须在当天的交货完成后返回那里。
*   The truck can only carry one cow at a time.  
    卡车一次只能运一头牛。
*   The orders are given as pairs of letters denoting where a cow is to be picked up followed by where the cow is to be delivered.  
    订单以成对字母的形式给出，表示牛要被提到哪里，然后是牛要被交付到哪里。

Your job is to write a program that, given any set of orders, determines the shortest route that takes care of all the deliveries, while starting and ending at farm A.  
你的工作是编写一个程序，在给定任何一组订单的情况下，确定处理所有交货的最短路线，同时从农场 A 开始和结束。

Since all possibilities must be tried in order to ensure the best one is found, the entire tree must be searched, which takes the same amount of time whether using DFS or BFS. Since DFS uses much less space and is conceptually easier to implement, use that.  
由于必须尝试所有可能性以确保找到最好的一种，因此必须搜索整个树，无论使用 DFS 还是 BFS，这都需要相同的时间。由于 DFS 使用的空间要少得多，并且在概念上更容易实现，因此可以使用它。

##### Desert Crossing [1992 IOI, adapted]  
穿越沙漠 [1992 IOI，改编]

A group of desert nomads is working together to try to get one of their group across the desert.  
一群沙漠游牧民族正在齐心协力，试图让他们中的一个人穿越沙漠。  
Each nomad can carry a certain number of quarts of water, and each nomad drinks a certain amount of water per day, but the nomads can carry differing amounts of water, and require different amounts of water.  
每个游牧民族可以携带一定数量的水，每个游牧民族每天喝一定量的水，但是游牧民族可以携带的水量不同，需要的水量也不同。  
Given the carrying capacity and drinking requirements of each nomad, find the minimum number of nomads required to get at least one nomad across the desert.  
考虑到每个游牧民族的承载能力和饮水要求，求出至少一名游牧民族穿越沙漠所需的最少游牧民族数量。

All the nomads must survive, so every nomad that starts out must either turn back at some point, carrying enough water to get back to the start or must reach the other side of the desert. However, if a nomad has surplus water when it is time to turn back, the water can be given to their friends, if their friends can carry it.  
所有游牧民都必须生存，因此每个出发的游牧民都必须在某个时刻返回，携带足够的水回到起点，或者必须到达沙漠的另一边。然而，如果游牧者在返程时有多余的水，如果他们的朋友可以携带水，则可以将水送给他们的朋友。

Analysis: This problem actually is two recursive problems: one recursing on the set of nomads to use, the other on when the nomads turn back.  
分析：这个问题实际上是两个递归问题：一个是对游牧民族使用的集合进行递归，另一个是对游牧民族何时返回进行递归。  
Depth-first search with iterative deepening works well here to determine the nomads required, trying first if any one can make it across by themselves, then seeing if two work together to get across, etc.  
具有迭代加深的深度优先搜索在这里可以很好地确定所需的游牧者，首先尝试是否有人可以自己穿越，然后看看两个人是否可以一起穿越，等等。

##### Addition Chains  加法链

An addition chain is a sequence of integers such that the first number is 1, and every subsequent number is the sum of some two (not necessarily unique) numbers that appear in the list before it. For example, 1 2 3 5 is such a chain, as 2 is 1+1, 3 is 2+1, and 5 is 2+3. Find the minimum length chain that ends with a given number.  
加法链是一个整数序列，其中第一个数字是 1，每个后续数字都是出现在它之前的列表中的两个（不一定是唯一的）数字的总和。例如，1 2 3 5就是这样的链，2是1+1，3是2+1，5是2+3。找到以给定数字结尾的最小长度链。

Analysis: Depth-first search with iterative deepening works well here, as DFS has a tendency to first try 1 2 3 4 5 ... n, which is really bad and the queue grows too large very quickly for BFS.  
分析：带有迭代加深的深度优先搜索在这里效果很好，因为 DFS 倾向于首先尝试 1 2 3 4 5 ... n，这非常糟糕，并且对于 BFS 来说队列增长得​​太快。
