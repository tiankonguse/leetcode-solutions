# P8817 [CSP-S 2022] 假期计划

## 题目描述

小熊的地图上有 $n$ 个点，其中编号为 $1$ 的是它的家、编号为 $2, 3, \ldots, n$ 的都是景点。部分点对之间有双向直达的公交线路。如果点 $x$ 与 $z_1$、$z_1$ 与 $z_2$、……、$z_{k - 1}$ 与 $z_k$、$z_k$ 与 $y$ 之间均有直达的线路，那么我们称 $x$ 与 $y$ 之间的行程可转车 $k$ 次通达；特别地，如果点 $x$ 与 $y$ 之间有直达的线路，则称可转车 $0$ 次通达。

很快就要放假了，小熊计划从家出发去 $4$ 个**不同**的景点游玩，完成 $5$ 段行程后回家：家 $\to$ 景点 A $\to$ 景点 B $\to$ 景点 C $\to$ 景点 D $\to$ 家且每段行程最多转车 $k$ 次。转车时经过的点没有任何限制，既可以是家、也可以是景点，还可以重复经过相同的点。例如，在景点 A $\to$ 景点 B 的这段行程中，转车时经过的点可以是家、也可以是景点 C，还可以是景点 D $\to$ 家这段行程转车时经过的点。

假设每个景点都有一个分数，请帮小熊规划一个行程，使得小熊访问的四个**不同**景点的分数之和最大。

## 输入格式

第一行包含三个正整数 $n, m, k$，分别表示地图上点的个数、双向直达的点对数量、每段行程最多的转车次数。

第二行包含 $n - 1$ 个正整数，分别表示编号为 $2, 3, \ldots, n$ 的景点的分数。

接下来 $m$ 行，每行包含两个正整数 $x, y$，表示点 $x$ 和 $y$ 之间有道路直接相连，保证 $1 \le x, y \le n$，且没有重边，自环。

## 输出格式

输出一个正整数，表示小熊经过的 $4$ 个不同景点的分数之和的最大值。

## 输入输出样例 #1

### 输入 #1

```
8 8 1
9 7 1 8 2 3 6
1 2
2 3
3 4
4 5
5 6
6 7
7 8
8 1
```

### 输出 #1

```
27
```

## 输入输出样例 #2

### 输入 #2

```
7 9 0
1 1 1 2 3 4
1 2
2 3
3 4
1 5
1 6
1 7
5 4
6 4
7 4
```

### 输出 #2

```
7
```

## 说明/提示

**【样例解释 \#1】**

当计划的行程为 $1 \to 2 \to 3 \to 5 \to 7 \to 1$ 时，$4$ 个景点的分数之和为 $9 + 7 + 8 + 3 = 27$，可以证明其为最大值。

行程 $1 \to 3 \to 5 \to 7 \to 8 \to 1$ 的景点分数之和为 $24$、行程 $1 \to 3 \to 2 \to 8 \to 7 \to 1$ 的景点分数之和为 $25$。它们都符合要求，但分数之和不是最大的。

行程 $1 \to 2 \to 3 \to 5 \to 8 \to 1$ 的景点分数之和为 $30$，但其中 $5 \to 8$ 至少需要转车 $2$ 次，因此不符合最多转车 $k = 1$ 次的要求。

行程 $1 \to 2 \to 3 \to 2 \to 3 \to 1$ 的景点分数之和为 $32$，但游玩的并非 $4$ 个不同的景点，因此也不符合要求。

**【样例 \#3】**

见附件中的 `holiday/holiday3.in` 与 `holiday/holiday3.ans`。

**【数据范围】**

对于所有数据，保证 $5 \le n \le 2500$，$1 \le m \le 10000$，$0 \le k \le 100$，所有景点的分数 $1 \le s_i \le {10}^{18}$。保证至少存在一组符合要求的行程。

| 测试点编号 | $n \le$ | $m \le$ | $k \le$ |
|:-:|:-:|:-:|:-:|
| $1 \sim 3$ | $10$ | $20$ | $0$ |
| $4 \sim 5$ | $10$ | $20$ | $5$ |
| $6 \sim 8$ | $20$ | $50$ | $100$ |
| $9 \sim 11$ | $300$ | $1000$ | $0$ |
| $12 \sim 14$ | $300$ | $1000$ | $100$ |
| $15 \sim 17$ | $2500$ | $10000$ | $0$ |
| $18 \sim 20$ | $2500$ | $10000$ | $100$ |