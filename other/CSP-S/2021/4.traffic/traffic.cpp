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
int debug_log = 1;
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
vector<vector<pair<ll, ll>>> vg;         // 竖线 vg[n][m]
vector<vector<pair<ll, ll>>> hg;         // 横线 hg[n][m]
vector<tuple<int, int, int>> kIndexPos;  // kP -> (x, y, gP)
void InitBoard() {
  for (int j = 0; j <= m + 1; j++) {
    vg[0][j] = vg[n][j] = {0, -1};
  }
  for (int i = 0; i <= n + 1; i++) {
    hg[i][0] = hg[i][m] = {0, -1};
  }
  kIndexPos.resize(n * 2 + m * 2 + 1);
  int kIndex = 1;
  for (int i = 1; i <= m; i++) {  // leftTop -> rightTop
    const int x = 0;
    const int y = i;
    const int gP = x * (m + 2) + y;
    kIndexPos[kIndex++] = {x, y, gP};
  }
  for (int i = 1; i <= n; i++) {  // rightTop -> rightBottom
    const int x = i;
    const int y = m;
    const int gP = x * (m + 1) + y;
    kIndexPos[kIndex++] = {x, y, gP};
  }
  for (int i = m; i >= 1; i--) {  // rightBottom -> leftBottom
    const int x = n;
    const int y = i;
    const int gP = x * (m + 1) + y - 1;  // 顺时针，归属前一列
    kIndexPos[kIndex++] = {x, y, gP};
  }
  for (int i = n; i >= 1; i--) {  // leftBottom -> leftTop
    const int x = i;
    const int y = 0;
    const int gP = (x - 1) * (m + 1) + y;  // 顺时针，所以归属上一行
    kIndexPos[kIndex++] = {x, y, gP};
  }
}

vector<tuple<ll, ll, ll, ll, int>> points;  // <kP, x, y, gP, color>
vector<int> kPoints;
vector<int> kPointToIndex;  // kP -> index
vector<vector<pair<int, ll>>> g;
vector<vector<ll>> indexDis;             // dis[i][j] 表示 i 到 j 的最短距离
unordered_map<int, int> gPointTokPoint;  // gP -> kP
void BuildGraph() {
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

void SolverMinPath(const int kIndex) {
  const int gp1 = get<3>(points[kIndex]);
  // 计算 gp1 到其他点的最短路径
  vector<ll> vis(g.size(), INFL);
  min_queue<pair<ll, int>> q;
  auto Add = [&](int gP, ll cost) {
    if (vis[gP] < cost) return;
    vis[gP] = cost;
    q.push({cost, gP});
  };
  Add(gp1, 0);
  while (!q.empty()) {
    const auto [SCost, SgP] = q.top();
    q.pop();
    if (vis[SgP] < SCost) continue;
    if (gPointTokPoint.count(SgP)) {  // 找到一个 kp 最短路
      const int SkP = gPointTokPoint[SgP];
      const int SkIndex = kPointToIndex[SkP];
      indexDis[kIndex][SkIndex] = min(indexDis[kIndex][SkIndex], SCost);
    }
    for (const auto& [TgP, TCost] : g[SgP]) {
      Add(TgP, SCost + TCost);
    }
  }
}

vector<vector<ll>> dp;
int K;
ll Dfs(int a, int b) {  // (a,b]
  ll& ret = dp[a][b];
  if (ret != -1) return ret;
  if (a == b || a == b + 1 || a + 1 == b) return ret = 0;  // 相同颜色，不需要继续拆分

  ret = INFL;
  if (a > b) {
    b += K;  // 环形，保证 a < b
  }
  a++;                                   // a 已经被分割在外面
  for (int i = a + 1; i <= b; i += 2) {  // 枚举分割点
    ret = min(ret, indexDis[a % K][i % K] + Dfs(a % K, i % K) + Dfs(i % K, b % K));
  }
  return ret;
}

ll SolverEx() {
  sort(points.begin(), points.end());

  // 第一步：预处理，合并相邻的相同颜色，保留最后一个
  vector<tuple<ll, ll, ll, ll, int>> newPoints;
  int k = points.size();
  newPoints.reserve(k);
  for (int i = 0; i < k; i++) {
    const auto [kP, x, y, gP, color] = points[i];
    if (newPoints.empty() || get<4>(newPoints.back()) != color) {
      newPoints.emplace_back(kP, x, y, gP, color);
    } else {
      newPoints.back() = {kP, x, y, gP, color};
    }
  }
  // 环形数组，最后一个和第一个相同颜色，合并
  if (newPoints.size() >= 2 && get<4>(newPoints.back()) == get<4>(newPoints.front())) {
    newPoints.pop_back();  // 删除最后一个
  }
  MyPrintf("合并后点数: %d\n", (int)newPoints.size());
  points.swap(newPoints);
  K = k = points.size();
  if (k == 1) return 0;  // 合并后只有一个点

  kPointToIndex.clear();
  kPointToIndex.resize(n * 2 + m * 2 + 1, 0);
  for (int i = 1; i <= k; i++) {
    const auto [kP, x, y, gP, color] = points[i - 1];
    kPointToIndex[kP] = i;  // 从 1 开始
  }

  gPointTokPoint.clear();
  for (const auto& [kP, x, y, gP, color] : points) {
    gPointTokPoint[gP] = kP;
  }
  BuildGraph();
  indexDis.clear();
  indexDis.resize(k, vector<ll>(k, INFL));
  for (int i = 0; i < k; i++) {
    SolverMinPath(i);
  }

  // 第二步：计算环形DP的最优值
  dp.clear();
  dp.resize(k, vector<ll>(k, -1));
  ll ans = INFL;
  for (int a = 0; a < k; a++) {
    for (int b = a + 1; b < k; b += 2) {  // 奇数点只能连偶数点
      ans = min(ans, indexDis[a][b] + Dfs(a, b) + Dfs(b, a));
    }
  }
  return ans;
}

void Solver() {  //
  scanf("%d%d%d", &n, &m, &t);
  MyPrintf("n=%d, m=%d, t=%d\n", n, m, t);
  vg.resize(n + 2, vector<pair<ll, ll>>(m + 2, {0, -1}));
  for (int i = 1; i < n; i++) {
    for (int j = 1; j <= m; j++) {
      scanf("%lld", &vg[i][j].first); // (i,j)->(i+1,j)
    }
  }
  hg.resize(n + 2, vector<pair<ll, ll>>(m + 2, {0, -1}));
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j < m; j++) {
      scanf("%lld", &hg[i][j].first);
    }
  }
  while (t--) {
    InitBoard(); // 清空 vg 和 hg 的边缘
    int k;
    scanf("%d", &k);
    points.resize(k);
    for (int i = 1; i <= k; i++) {
      ll x, p, color;  // 第 p 个点，边权是 x，颜色是 color
      scanf("%lld%lld%lld", &x, &p, &color);
      const int kP = p;
      const auto [X, Y, gP] = kIndexPos[kP];
      points[i] = {kP, X, Y, gP, color};
      if (p <= m) {
        vg[X][Y] = {x, color};
      } else if (p <= n + m) {
        hg[X][Y] = {x, color};
      } else if (p <= m + n + m) {
        vg[X][Y] = {x, color};
      } else {
        hg[X][Y] = {x, color};
      }
    }
    printf("%lld\n", SolverEx());
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