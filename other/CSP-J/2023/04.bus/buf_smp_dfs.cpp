#include <bits/stdc++.h>

/*
题意：给一个图，部分路径有最早时间限制，起点p1时刻是k周期出发(t1=a*k)，
终点pn要求也是k周期时刻到达(tn=b*k).

基本思路：搜索(bfs 或 dfs)求最短路，每个节点在 t%k 时间，只能到达一次

分析：
1）不考虑任何限制：经典最短路。
2）考虑起点周期k：如果一个点在 t 时刻可以到达，则可以在 t+b*k
时刻到达，故只需要储存最小的 t。 3）考虑路径 [u,v,a] 开放时间：到达 u 时，时刻
t<a， 则可以加上若干 k，使得可以通过这个路径， 即找到最小的 T=t+bk, 使得 T>=a。
4）考虑终点周期限制：终点必须满足 `t%k==0`，这意味着倒数第二步需满足 `t%k ==
k-1`，倒数第三步需满足 `t%k == k-2`。 故每个点满足`t%k =
[0,k-1]`的时刻都需要计算出来，按结论2，储存下每个时刻的最小 t， k 数据范围 100。


算法：广度优先搜索 或 深度优先搜索
重复节点标记： flag[T][N]，含义：到达节点 N 时，时间为 `T`
(0<=T<k)时的最早到达时间。 复杂度：`O(nk)` 答案：flag[n][0]
*/

using namespace std;
typedef long long ll;     // 整数别名
const int INF = 1 << 30;  // 整数最大值

vector<vector<pair<ll, ll>>> g;  // 图储存在 g 里面, 元素值为 {v, a}
vector<vector<ll>> flag;         // 标记每个位置 t%k 到达的最优时间

ll n, m, k;
void dfs(ll tu, ll u) {
  if (flag[tu % k][u] <= tu) return;  // 达到时间没有更优，不处理
  flag[tu % k][u] = tu;

  for (auto [v, a] : g[u]) {
    ll tv = tu;
    if (tv < a) {                   // 道路没开放，在门口等到 b 个 k
      ll b = (a - tv + k - 1) / k;  // 相差 a-tv 时间，等待 k 周期，需向上取整
      tv += b * k;
    }
    tv++;  // 通过这条道路，时间加1
    dfs(tv, v);
  }
}

void Solver() {  //
  scanf("%lld%lld%lld", &n, &m, &k);
  g.resize(n);
  flag.resize(k, vector<ll>(n, INF));  // 默认每个节点每个时刻都是不可到达

  while (m--) {
    ll u, v, a;
    scanf("%lld%lld%lld", &u, &v, &a);  // u->v
    u--, v--;                           // 下标转换为从0开始
    g[u].push_back({v, a});
  }

  dfs(0, 0);  // 入口,0时刻可以到达

  ll ans = flag[0][n - 1];
  printf("%lld\n", ans == INF ? -1 : ans);
}

int main() {
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