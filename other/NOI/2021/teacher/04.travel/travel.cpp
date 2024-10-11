
/*
ID: tiankonguse
TASK: travel
LANG: C++
CONTEST: 2021 年 CCF NOI线上教师培训测试
OJ:
*/
#define TASK "travel"

#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

void InitIO() {
  // #ifndef USACO_LOCAL_JUDGE
  //   freopen(TASK ".in", "r", stdin);
  //   freopen(TASK ".out", "w", stdout);
  // #endif
}
ll n, m, W;
vector<pair<ll, ll>> nums;        // {重量为𝑤 ，价值为 𝑣}
vector<vector<pair<ll, ll>>> g;   // 正向边
vector<vector<pair<ll, ll>>> rg;  // 反向边
vector<ll> inDeg;

vector<vector<ll>> dp;  // dp[n][w] 前n个容量恰好为w的最大价值
vector<vector<ll>> dp2;  // dp[n][w] 前n个容量恰好为w。价值为最优时的最小代价
ll maxVal;

vector<ll> flag;

void FlagFrom0(ll a) {
  flag[a] = 1;
  for (auto [b, _] : g[a]) {
    FlagFrom0(b);
  }
}
bool DelFrom0(ll a) {
  if (g[a].size() == 0) {
    if (a == n - 1) {
      return false;  // 是目标路径
    } else {
      return true;  // 无关分支，需要删除
    }
  }

  ll delNum = 0;
  for (auto [b, _] : g[a]) {
    if (DelFrom0(b)) {
      delNum++;
    }
  }
  if (delNum == g[a].size()) {
    g[a].clear();  // 儿子都被删除了，自己也是无关分支，删除
    return true;
  } else {
    return false;
  }
}

void Read() {
  scanf("%lld%lld%lld", &n, &m, &W);
  nums.resize(n);
  g.resize(n);
  rg.resize(n);
  dp.resize(n, vector<ll>(W + 1, -1));
  dp2.resize(n, vector<ll>(W + 1, -1));
  inDeg.resize(n, 0);
  flag.resize(n, 0);

  for (ll i = 0; i < n; i++) {
    scanf("%lld%lld", &nums[i].first, &nums[i].second);
  }
  for (ll i = 0; i < m; i++) {
    ll a, b, d;
    scanf("%lld%lld%lld", &a, &b, &d);
    a--, b--;
    if (b == 0 || a == n - 1) {
      continue;  // 城市0出发,目的是城市n-1，不能回到这个城市，所以删除对应的边
    }
    g[a].push_back({b, d});
  }
}
void InitGraph() {
  FlagFrom0(0);
  for (ll a = 0; a < n; a++) {
    if (flag[a]) {
      continue;
    }
    g[a].clear();
  }
  DelFrom0(0);

  for (ll a = 0; a < n; a++) {
    for (auto [b, d] : g[a]) {
      rg[b].push_back({a, d});
      inDeg[b]++;
    }
  }
}

ll Dfs1(ll a, ll W) {
  ll& ret = dp[a][W];
  if (ret != -1) {
    return ret;
  }
  if (W == 0) {
    return ret = 0;
  }
  ret = -2;  // -2 代表没答案

  auto [w, v] = nums[a];
  if (w == W) {  // 当前物品恰好选够
    ret = v;
  }

  for (auto [b, d] : rg[a]) {
    if (w < W) {  // 选择
      ret = max(ret, Dfs1(b, W - w));
    }
    ret = max(ret, Dfs1(b, W));  // 不选择
  }
  return ret;
}

void Solver() {  //
  Read();        // 输入
  InitGraph();   // 删除无关边
  // 此时保证入度为0只有城市0， 出度为0的只有城市n-1
  maxVal = 0;
  for (ll w = 1; w <= W; w++) {
    maxVal = max(maxVal, Dfs1(n - 1, w));
  }

  printf("%lld\n", maxVal);
}

int main() {
  InitIO();
  Solver();
  return 0;
}
/*
5 6 10
2 2
1 3
3 5
4 2
2 3
1 2 1
2 4 5
2 5 3
1 3 4
3 4 2
4 5 2

10 20
*/