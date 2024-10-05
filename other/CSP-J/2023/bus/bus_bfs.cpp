/*
ID: tiankonguse
TASK: bus
LANG: C++
OJ: https://qoj.ac/submission/601150
*/
#define TASK "bus"

#include <bits/stdc++.h>

using namespace std;

void InitIO() {
#ifndef USACO_LOCAL_JUDGE1
  freopen(TASK ".in", "r", stdin);
  freopen(TASK ".out", "w", stdout);
#endif
}

/*
题意：给一个图，部分路径有起始时间限制，起点p1时刻是k周期(t1=a*k)，
终点pn要求也是k周期时刻(tn=b*k). 思路1:
不考虑k周期与路径限制，p1到pn存在路径才有答案，即必须联通 思路2:
假设图是一个树，终点无k周期限制。 -）p1到pn只有一个路径,假设路径长度是 L。
  -) 加入起点周期
     起点时刻可以是 `[0,k,2k,...]`, 终点时刻是 `[L, L+k, K+2k,...]`
     规律：每个点 a 时刻可以到达，则 `a+bk` 时刻都可以到达（入口等 b 个周期）。
  -）加入路径时间限制。
     对于路径`[u,v,a]`，假设到达 u 的时刻是 t, 且 `t<a`,
可以等若干周期，直到`t+bk>=a`，之后可以通过这个路径。
  -）树+起点周期+路径限制的答案：
     最短路算法，边的代价默认是1。
     当一个边未开放时，代价需加若干周期
思路3：图中存在环
  -）不考虑路径时间限制，不考虑终点周期限制：
    经典的最短路。
    最短路注意实现：由于环的存在，一个点可能到达多次，需优先处理时间最短的点。如果没有优先处理时间最短的点，每个点有更优到达时间时，需重新计算答案。
  -) 考虑路径时间限制
    经典的最短路，此时有限制的路径代价不是1，需要加上等待时间。
  -) 考虑终点周期限制
    终点必须满足 `t%k==0`，即倒数第一步需满足 `t%k == k-1`，倒数第二步需满足
`t%k == k-1`。 k 数据范围最大100，可以求出每个点满足`t%k = [0,k-1]`的最优解。


汇总：
题意：给一个图，部分路径有起始时间限制，起点p1时刻是k周期(t1=a*k)，
终点pn要求也是k周期时刻(tn=b*k). 1）不考虑任何限制：经典最短路。
2）考虑起点周期k：如果一个点在 a 时刻可以到达，则可以在 a+b*k 时刻到达（b*k
时刻进入起点）。 3）考虑路径`[u,v,a]`开放时间：到达 u 时，时刻 t<a，
则可以加上若干 k，使得时间大于等于 a，即可通过这个路径。
4）考虑终点周期限制：终点必须满足 `t%k==0`，这意味着倒数第二步需满足 `t%k ==
k-1`，倒数第三步需满足 `t%k == k-2`。 k 数据范围最大100，可以求出每个点满足`t%k
= [0,k-1]`的所有最优时间。


算法：广度优先搜索
重复节点标记： flag[N][K]，含义：到达节点 N 时，时间取模 K 为 K 时的最短时间。
剪枝1：标记节点重复到达，时间更短时才进入队列
剪枝2：标记节点出队列时，如果自身不是当前最优解，说明有更优解，忽略当前节点。
答案：flag[n][0]


*/

constexpr int INF = 1 << 30;
vector<vector<pair<int, int>>> g;  // g[u]{v, a}
queue<pair<int, int>> que;         // {cost, u}
vector<vector<int>> dp;
void Solver() {  //
  int n, m, k;
  scanf("%d%d%d", &n, &m, &k);
  g.resize(n);
  dp.resize(k, vector<int>(n, INF));

  while (m--) {
    int u, v, a;
    scanf("%d%d%d", &u, &v, &a);  // u->v
    u--, v--;                     // 下标转换为从0开始
    g[u].push_back({v, a});
  }

  dp[0][0] = 0;
  que.push({0, 0});

  while (!que.empty()) {
    auto [tu, u] = que.front();
    que.pop();

    // 剪枝，如果有更优解，说明已经计算过了
    if (dp[tu % k][u] < tu) {
      continue;
    }

    for (auto [v, a] : g[u]) {
      int tv = tu;
      if (tv < a) {  // 道路没开放，在门口等到 num 个 k, 向上取整
        int num = (a - tv + k - 1) / k;
        tv += num * k;
      }
      tv++;  // 通过这条道路，时间加1

      int tvk = tv % k;
      if (tv < dp[tvk][v]) {  // 有更优解
        dp[tvk][v] = tv;
        que.push({tv, v});
      }
    }
  }

  if (dp[0][n - 1] == INF) {  // 没有答案
    dp[0][n - 1] = -1;
  }
  printf("%d\n", dp[0][n - 1]);
}

int main() {
  InitIO();
  Solver();
  return 0;
}
/*
5 5 3
1 2 0
2 5 1
1 3 0
3 4 3
4 5 1
*/