/*
ID: tiankonguse
TASK: traffic
LANG: C++
MAC EOF: ctrl+D
link:  https://www.luogu.com.cn/problem/P7916
PATH: P7916 [CSP-S 2021] 交通规划
submission:
*/
#define TASK "traffic"
#define TASKEX ""

#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

void CheckUsacoTask() {
#ifdef USACO_LOCAL_JUDGE
  string filePath = __FILE__;
  string fileNameEx = filePath.substr(filePath.rfind('/') + 1);
  string fileName = fileNameEx.substr(0, fileNameEx.find("."));
  assert(fileName == TASK TASKEX);
#endif
}

#ifdef USACO_LOCAL_JUDGE
int debug_log = 0;
int debug_assert = 1;
#define MyPrintf(...)                   \
  do {                                  \
    if (debug_log) printf(__VA_ARGS__); \
  } while (0)

#define MyAssert(...)                      \
  do {                                     \
    if (debug_assert) assert(__VA_ARGS__); \
  } while (0)
#else
#define MyPrintf(...)
#define MyAssert(...)
#endif

constexpr int INF = 1 << 30;
constexpr ll INFL = 1LL << 60;
constexpr ll MOD = 1000000007;

const double pi = acos(-1.0), eps = 1e-7;
const int inf = 0x3f3f3f3f, ninf = 0xc0c0c0c0, mod = 1000000007;
const int max3 = 2010, max4 = 20010, max5 = 200010, max6 = 2000010;

template <class T>
using min_queue = priority_queue<T, vector<T>, greater<T>>;
template <class T>
using max_queue = priority_queue<T>;

void InitIO() {  //
#ifdef USACO_LOCAL_JUDGE
// #define TASKNO "4"
//   freopen(TASK TASKNO ".in", "r", stdin);
//   freopen(TASK TASKNO ".out", "w", stdout);
#endif
}

int n, m, t;
vector<vector<pair<ll, ll>>> vg;  // 竖线 vg[n][m]
vector<vector<pair<ll, ll>>> hg;  // 横线 hg[n][m]

void InitBoard() {
  for (int j = 0; j <= m + 1; j++) {
    vg[0][j] = vg[n][j] = {0, -1};
  }
  for (int i = 0; i <= n + 1; i++) {
    hg[i][0] = hg[i][m] = {0, -1};
  }
}

vector<tuple<ll, ll, ll, ll, int>> points;  // <kP, x, y, gP, color>
vector<int> kPoints;
vector<vector<pair<int, ll>>> g;
vector<vector<ll>> dis;                  // dis[i][j] 表示 i 到 j 的最短距离
unordered_map<int, int> gPointTokPoint;  // gP -> kP
void BuildGraph(const int k) {
  // 顺时针构图
  g.clear();
  g.resize((n + 1) * (m + 1));
  auto AddEdge = [&](int a, int b, ll c) {
    g[a].emplace_back(b, c);
    g[b].emplace_back(a, c);
  };
  for (int i = 0; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      const int a = i * (m + 1) + j - 1;
      const int b = a + 1;
      const ll cost = vg[i][j].first;
      AddEdge(a, b, cost);
    }
  }
  for (int j = 0; j <= m; j++) {
    for (int i = 1; i <= n; i++) {
      const int a = (i - 1) * (m + 1) + j;
      const int b = i * (m + 1) + j;
      const ll cost = hg[i][j].first;
      AddEdge(a, b, cost);
    }
  }
}

vector<pair<int, int>> preColors;
void SolverMinPath(const int kP1) {
  const int gp1 = get<3>(points[kP1]);
  // 计算 gp1 到其他点的最短路径
  vector<ll> vis(g.size(), INFL);
  min_queue<pair<ll, int>> q;
  auto Add = [&](int p, ll cost) {
    if (vis[p] < cost) return;
    vis[p] = cost;
    q.push({cost, p});
  };
  Add(gp1, 0);
  while (!q.empty()) {
    const auto [cost, p] = q.top();
    q.pop();
    if (vis[p] < cost) continue;
    if (gPointTokPoint.count(p)) {  // 找到一个 kp 最短路
      const int kP2 = gPointTokPoint[p];
      dis[kP1][kP2] = min(dis[kP1][kP2], cost);
    }
    for (const auto [to, c] : g[p]) {
      Add(to, cost + c);
    }
  }
}

pair<int, int> allColor;

vector<vector<ll>> dp;

pair<int, int> GetColor(int a, int b){
    if(a < b){

    }else{
        
    }
}
ll Dfs(int a, int b){
  ll& ret = dp[a][b];
  if(ret != -1) return ret;
  ret = 0;
  auto colorNum = GetColor(a, b);

  return ret;
}

ll Solver(const int k) {
  if (k == 1) return 0;
  sort(points.begin(), points.end());

  // 环形 DP 求最优值
  // 第一步，计算 k 个 kp 点的前缀颜色个数
  preColors.resize(k + 1, {0, 0});
  for (int i = 1; i <= k; i++) {
    const auto [kP, x, y, gP, color] = points[i - 1];
    preColors[i] = preColors[i - 1];
    if (color == 0) {
      preColors[i].first++;
    } else {
      preColors[i].second++;
    }
  }
  allColor = preColors.back();
  if (allColor.first == 0 || allColor.second == 0) return 0;  // 都是相同颜色

  for (const auto [kP, x, y, gP, color] : points) {
    gPointTokPoint[gP] = kP;
  }
  BuildGraph(k);
  dis.resize(k, vector<ll>(k, INFL));
  for (int i = 0; i < k; i++) {
    SolverMinPath(i);
  }

  // 第二步：计算环形DP的最优值
  dp.clear();
  dp.resize(k, vector<ll>(k, -1));
  ll ans = INFL;
  for (int a = 0; a < k; a++) {
    for (int b = 0; b < k; b++) {
      if (a == b) continue;
      ans = min(ans, dis[a][b] + Dfs(a, b) + Dfs(b, a));
    }
  }
  return ans;
}

void Solver() {  //
  scanf("%d%d%d", &n, &m, &t);
  vg.resize(n + 2, vector<pair<ll, ll>>(m + 2, {0, -1}));
  for (int i = 1; i < n; i++) {
    for (int j = 1; j <= m; j++) {
      scanf("%lld", &vg[i][j].first);
    }
  }
  hg.resize(m + 2, vector<pair<ll, ll>>(n + 2, {0, -1}));
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j < m; j++) {
      scanf("%lld", &hg[i][j].first);
    }
  }
  while (t--) {
    InitBoard();
    int k;
    scanf("%d", &k);
    points.resize(k);
    for (int i = 0; i < k; i++) {
      ll x, p, color;  // 第 p 个点，边权是 x，颜色是 color
      scanf("%lld%lld%lld", &x, &p, &color);
      const ll kP = p;
      if (p <= m) {
        const int X = 0;
        const int Y = p;
        const int gP = X * (m + 1) + Y;
        vg[X][Y] = {x, color};
        points[i] = {kP, X, Y, gP, color};
      } else if (p <= n + m) {
        const int X = p - m;
        const int Y = m;
        const int gP = X * (m + 1) + Y;
        hg[X][Y] = {x, color};
        points[i] = {kP, X, Y, gP, color};
      } else if (p <= m + n + m) {
        const int X = n;
        const int Y = m - (p - (m + n)) + 1;
        const int gP = X * (m + 1) + Y - 1;  // 顺时针，归属前一列
        vg[X][Y] = {x, color};
        points[i] = {kP, X, Y, gP, color};
      } else {
        const int X = n - (p - (m + n + m)) + 1;
        const int Y = 0;
        const int gP = (X - 1) * (m + 1) + Y;  // 顺时针，所以归属上一行
        hg[X][Y] = {x, color};
        points[i] = {kP, X, Y, gP, color};
      }
    }
    printf("%lld\n", Solver(k));
  }
}

void ExSolver() {
#ifdef USACO_LOCAL_JUDGE
  auto t1 = std::chrono::steady_clock::now();
#endif
  Solver();
#ifdef USACO_LOCAL_JUDGE
  auto t2 = std::chrono::steady_clock::now();
  auto my = std::chrono::duration_cast<std::chrono::duration<double, ratio<1, 1000>>>(t2 - t1);
  printf("my 用时: %.0lfms\n", my.count());
#endif
}

int main(int argc, char** argv) {
  CheckUsacoTask();
  InitIO();
  ExSolver();
  return 0;
}

/*

*/