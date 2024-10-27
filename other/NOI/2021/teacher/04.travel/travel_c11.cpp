
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
vector<ll> flag;

vector<vector<ll>> dpVal;  // dp[n][w] 到达地点n时，背包大小恰好为w的最大价值
vector<vector<ll>> dpCost;  // dp[n][w] 地点n、背包 w、价值最优时的最小代价
ll maxVal;
ll minCost;

void FlagFrom0(ll a) {
  flag[a] = 1;
  for (const auto p : g[a]) {
    ll b = p.first;
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
  for (auto p : g[a]) {
    ll b = p.first;
    if (DelFrom0(b)) {
      delNum++;
    }
  }
  if (delNum == g[a].size()) {
    printf("%lld can not go to n-1\n", a);
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

  for (ll i = 0; i < n; i++) {
    scanf("%lld%lld", &nums[i].first, &nums[i].second);
  }
  for (ll i = 0; i < m; i++) {
    ll a, b, d;
    scanf("%lld%lld%lld", &a, &b, &d);
    a--, b--;
    if (b == 0 || a == n - 1) {
      if (b == 0) {
        printf("0 has in deg, %lld->%lld\n", a, b);
      } else {
        printf("n-1 has out deg, %lld->%lld\n", a, b);
      }
      continue;  // 城市0出发,目的是城市n-1，不能回到这个城市，所以删除对应的边
    }
    g[a].push_back({b, d});
  }
}
void InitGraph() {
  flag.resize(n, 0);
  FlagFrom0(0);
  for (ll a = 0; a < n; a++) {
    if (flag[a]) {
      continue;
    }
    printf("0 can not go to %lld\n", a);
    g[a].clear();
  }
  DelFrom0(0);
}

ll DfsMaxVal(const ll a, const ll W) {  // 到达 a，背包重量恰好为 W 的最大价值
  ll& ret = dpVal[a][W];
  if (ret != -1) {
    return ret;
  }
  if (W == 0) {
    return ret = 0;
  }

  const auto p = nums[a];
  const auto w = p.first;
  const auto v = p.second;
  ret = INT64_MIN;  // 代表没答案
  if (w == W) {     // 当前物品恰好选够
    ret = v;
  }

  for (const auto p : rg[a]) {
    const auto b = p.first;
    const auto d = p.second;
    if (w < W) {  // 选择
      ret = max(ret, v + DfsMaxVal(b, W - w));
    }
    ret = max(ret, DfsMaxVal(b, W));  // 不选择
  }
  if (ret < 0) {
    ret = INT64_MIN;
  }
  return ret;
}

ll DfsMinCost(const ll a, const ll W) {  //
  const ll val = dpVal[a][W];
  ll& ret = dpCost[a][W];
  if (ret != INT64_MAX) {
    return ret;
  }

  const auto p = nums[a];
  const auto w = p.first;
  const auto v = p.second;
  if (W == 0) {
    return ret = 0;
  }
  ret = INT64_MAX;  // 一定存在答案
  if (w == W) {     // 当前物品恰好选够
    return ret = 0;
  }

  for (const auto p : rg[a]) {
    const auto b = p.first;
    const auto d = p.second;
    if (w < W && dpVal[b][W - w] + v == val) {  // 选择
      ret = min(ret, (W - w) * d + DfsMinCost(b, W - w));
    }
    if (dpVal[b][W] == val) {  // 不选择
      ret = min(ret, W * d + DfsMinCost(b, W));
    }
  }

  return ret;
}

void Solver() {  //
  Read();        // 输入
  InitGraph();   // 删除无关边

  rg.resize(n);
  inDeg.resize(n, 0);
  for (ll a = 0; a < n; a++) {
    for (const auto p : g[a]) {
      const auto b = p.first;
      const auto d = p.second;
      rg[b].push_back({a, d});
      inDeg[b]++;
    }
  }

  // 此时保证入度为0只有城市0， 出度为0的只有城市n-1
  dpVal.resize(n, vector<ll>(W + 1, -1));
  maxVal = 0;
  for (ll w = 1; w <= W; w++) {
    maxVal = max(maxVal, DfsMaxVal(n - 1, w));
  }

  dpCost.resize(n, vector<ll>(W + 1, INT64_MAX));
  minCost = INT64_MAX;
  for (ll w = 1; w <= W; w++) {
    if (dpVal[n - 1][w] == maxVal) {
      minCost = min(minCost, DfsMinCost(n - 1, w));
    }
  }

  printf("%lld %lld\n", maxVal, minCost);
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