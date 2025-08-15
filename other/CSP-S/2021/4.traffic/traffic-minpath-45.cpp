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
#define TASKNO "5"
  freopen(TASK TASKNO ".in", "r", stdin);
  freopen(TASK TASKNO ".out", "w", stdout);
#endif
}

int n, m, t;
vector<vector<pair<ll, ll>>> vg;         // 竖线 vg[n][m]
vector<vector<pair<ll, ll>>> hg;         // 横线 hg[n][m]
vector<tuple<int, int, int>> kIndexPos;  // kP -> (x, y, gP)

// 初始化所有带编号射线的坐标，以及对应到对偶图中的坐标
void InitKIndexPos() {
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
    const int y = m + 1;
    const int gP = x * (m + 1) + y - 1;
    kIndexPos[kIndex++] = {x, y, gP};
  }
  for (int i = m; i >= 1; i--) {  // rightBottom -> leftBottom
    const int x = n + 1;
    const int y = i;
    const int gP = (x - 1) * (m + 1) + y - 1;  // 顺时针，归属前一列
    kIndexPos[kIndex++] = {x, y, gP};
  }
  for (int i = n; i >= 1; i--) {  // leftBottom -> leftTop
    const int x = i;
    const int y = 0;
    const int gP = (x - 1) * (m + 1) + y;  // 顺时针，所以归属上一行
    kIndexPos[kIndex++] = {x, y, gP};
  }
  //   for (int i = 1; i < kIndex; i++) {
  //     const auto [x, y, gP] = kIndexPos[i];
  //     MyPrintf("kP=%d -> (x,y)=(%d,%d), gP=%d\n", i, x, y, gP);
  //   }
}

// 只清空射线的权值，复杂度 O(n+m)
void InitBoard() {
  for (int j = 0; j <= m + 1; j++) {
    vg[0][j] = vg[n][j] = {0, -1};
  }
  for (int i = 0; i <= n + 1; i++) {
    hg[i][0] = hg[i][m] = {0, -1};
  }
}

vector<tuple<ll, ll, int>> points;  // <kP, gP, color>
vector<int> kPoints;
vector<int> kPointToKIndex;  // kP -> index
vector<vector<pair<int, ll>>> g;
vector<vector<ll>> indexDis;             // dis[i][j] 表示 i 到 j 的最短距离
unordered_map<int, int> gPointTokPoint;  // gP -> kP
unordered_set<int> outerGPointsFlag;     // 外部边缘的点，gP
vector<int> outerGPointList;             // 外部边缘的点列表，gP

void InitOuterPoint() {
  outerGPointList.reserve((n + m) * 2 + 20);
  for (int j = 0; j <= m; j++) {  // m 条竖线，m+1 个 kG
    const int gPTop = 0 * (m + 1) + j;
    outerGPointsFlag.insert(gPTop);  // 第一行
    outerGPointList.push_back(gPTop);
    const int gPBottom = n * (m + 1) + j;
    outerGPointsFlag.insert(gPBottom);  // 最后一行
    outerGPointList.push_back(gPBottom);
  }
  for (int i = 0; i <= n; i++) {  // n 条横线，n+1 个 kG
    const int gPRight = i * (m + 1) + m;
    outerGPointsFlag.insert(gPRight);  // 最后一列
    outerGPointList.push_back(gPRight);
    const int gPLeft = i * (m + 1) + 0;
    outerGPointsFlag.insert(gPLeft);  // 第一列
    outerGPointList.push_back(gPLeft);
  }
}

vector<ll> vis;
int visIndex = 0;
void BuildGraph() {
  // 顺时针构图
  g.clear();
  g.resize((n + 1) * (m + 1));
  vis.resize((n + 1) * (m + 1), visIndex);  // 初始化访问数组
  auto AddEdge = [&](int a, int b, ll c) {
    // MyPrintf("AddEdge: %d -> %d, cost=%lld\n", a, b, c);
    g[a].emplace_back(b, c);
    g[b].emplace_back(a, c);
    MyAssert(g[a].size() <= 4);
    MyAssert(g[b].size() <= 4);
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

// 先清空边缘点的所有边，然后重新对边缘点进行构图，复杂度O(n+m)
void BuildBoardGraph() {
  for (auto gP : outerGPointList) {
    g[gP].clear();  // 每个边缘点最多 3 条边
  }
  auto AddEdge = [&](int a, int b, ll c) {
    // MyPrintf("AddEdge: %d -> %d, cost=%lld\n", a, b, c);
    if (outerGPointsFlag.count(a)) {
      MyAssert(g[a].size() <= 3);
      g[a].emplace_back(b, c);
    }
    if (outerGPointsFlag.count(b)) {
      MyAssert(g[b].size() <= 3);
      g[b].emplace_back(a, c);
    }
  };

  // 竖线-列 左右边连线
  for (int i = 1; i < n; i++) {
    // 第 1 列
    int j1 = 1;
    const int a1 = i * (m + 1) + j1 - 1;
    const int b1 = a1 + 1;
    const ll cost1 = vg[i][j1].first;
    AddEdge(a1, b1, cost1);
    // 第 m 列
    int jm = m;
    const int am = i * (m + 1) + jm - 1;
    const int bm = am + 1;
    const ll costm = vg[i][jm].first;
    AddEdge(am, bm, costm);
  }

  // 竖线-行  左右边连线
  for (int j = 1; j <= m; j++) {
    int i0 = 0;  // 第一行
    const int a0 = i0 * (m + 1) + j - 1;
    const int b0 = a0 + 1;
    const ll cost0 = vg[i0][j].first;
    AddEdge(a0, b0, cost0);
    int in = n;  // 最后一行
    const int an = in * (m + 1) + j - 1;
    const int bn = an + 1;
    const ll costn = vg[in][j].first;
    AddEdge(an, bn, costn);
  }

  // 横线-行 上下边连线
  for (int j = 1; j < m; j++) {
    int i1 = 1;  // 第一行
    const int a1 = (i1 - 1) * (m + 1) + j;
    const int b1 = i1 * (m + 1) + j;
    const ll cost1 = hg[i1][j].first;
    AddEdge(a1, b1, cost1);
    int in = n;  // 最后一行
    const int an = (in - 1) * (m + 1) + j;
    const int bn = in * (m + 1) + j;
    const ll costn = hg[in][j].first;
    AddEdge(an, bn, costn);
  }

  // 横线-列 上下边连线
  for (int i = 1; i <= n; i++) {
    int j0 = 0;  // 第一列
    const int a0 = (i - 1) * (m + 1) + j0;
    const int b0 = i * (m + 1) + j0;
    const ll cost0 = hg[i][j0].first;
    AddEdge(a0, b0, cost0);
    int jm = m;  // 最后一列
    const int am = (i - 1) * (m + 1) + jm;
    const int bm = i * (m + 1) + jm;
    const ll costm = hg[i][jm].first;
    AddEdge(am, bm, costm);
  }
}

min_queue<pair<ll, int>> q;
int K;
void SolverMinPath(const int kIndex) {
  const int gp1 = get<1>(points[kIndex]);
  // 计算 gp1 到其他点的最短路径
  fill(vis.begin(), vis.end(), INFL);
  while (!q.empty()) {
    q.pop();  // 清空队列
  }
  auto Add = [&](int gP, ll cost) {
    if (vis[gP] <= cost) return;
    vis[gP] = cost;
    q.push({cost, gP});
  };
  Add(gp1, 0);
  int findKpNum = 0;
  while (!q.empty()) {
    const auto [SCost, SgP] = q.top();
    q.pop();
    if (vis[SgP] < SCost) continue;
    // MyPrintf("gp1=%d SgP=%d, SCost=%lld\n", gp1, SgP, SCost);
    if (gPointTokPoint.count(SgP)) {  // 找到一个 kp 最短路
      const int SkP = gPointTokPoint[SgP];
      const int SkIndex = kPointToKIndex[SkP];
      indexDis[kIndex][SkIndex] = min(indexDis[kIndex][SkIndex], SCost);
      findKpNum++;
      if (findKpNum == K) break;  // 找到所有 kp
    }
    for (const auto& [TgP, TCost] : g[SgP]) {
      Add(TgP, SCost + TCost);
    }
  }
}

vector<vector<ll>> dp;
ll Dfs(const int A, const int B) {  // (a,b]
  int a = A, b = B;
  ll& ret = dp[a][b];
  if (ret != -1) return ret;

  ret = INFL;
  if (a > b) {
    b += K;  // 环形，保证 a < b
  }
  if (a == b || a + 1 == b) return ret = 0;  // 相同颜色，不需要继续拆分
  a++;                                       // a 已经被分割在外面
  for (int i = a + 1; i <= b; i += 2) {      // 枚举分割点
    ret = min(ret, indexDis[a % K][i % K] + Dfs(a % K, i % K) + Dfs(i % K, b % K));
  }
  MyAssert(ret != INFL);
  return ret;
}

// 获取点的颜色
int GetColor(const tuple<ll, ll, int>& point) {
  const auto& [kP, gP, color] = point;
  return color;
}

vector<tuple<ll, ll, int>> newPoints;  // <kP, gP, color>
ll SolverEx() {
  sort(points.begin(), points.end());

  // 第一步：预处理，合并相邻的相同颜色，保留最后一个
  int k = points.size();
  newPoints.clear();
  newPoints.reserve(k);
  for (int i = 0; i < k; ++i) {
    const auto [kP, gP, color] = points[i];
    // MyPrintf("kP=%lld, x=%lld, y=%lld, gP=%lld, color=%d\n", kP, x, y, gP, color);
    if (newPoints.empty() || GetColor(newPoints.back()) != color) {
      newPoints.emplace_back(kP, gP, color);
    } else {
      newPoints.back() = {kP, gP, color};
    }
  }
  // 环形数组，最后一个和第一个相同颜色，合并
  if (newPoints.size() >= 2 && GetColor(newPoints.back()) == GetColor(newPoints.front())) {
    newPoints.pop_back();  // 删除最后一个
  }
  //   MyPrintf("合并后点数: %d\n", (int)newPoints.size());
  points.swap(newPoints);
  K = k = points.size();
  if (k == 1) return 0;  // 合并后只有一个点
  if (k != 2) return 0;  // 合并后只有一个点

  kPointToKIndex.clear();
  gPointTokPoint.clear();
  kPointToKIndex.resize(n * 2 + m * 2 + 1, 0);
  for (int i = 0; i < k; ++i) {
    const auto& [kP, gP, color] = points[i];
    kPointToKIndex[kP] = i;
    gPointTokPoint[gP] = kP;
    // MyPrintf("kP=%lld, gP=%lld, color=%d,i=%d\n", kP, gP, color, i);
  }

  BuildBoardGraph();
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
  InitKIndexPos();
  InitOuterPoint();
  vg.resize(n + 2, vector<pair<ll, ll>>(m + 2, {0, -1}));
  for (int i = 1; i < n; i++) {
    for (int j = 1; j <= m; j++) {
      scanf("%lld", &vg[i][j].first);  // (i,j)->(i+1,j)
    }
  }
  hg.resize(n + 2, vector<pair<ll, ll>>(m + 2, {0, -1}));
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j < m; j++) {
      scanf("%lld", &hg[i][j].first);
    }
  }

  InitBoard();  // 清空 vg 和 hg 的边缘
  BuildGraph();
  //   MyPrintf("n=%d, m=%d, t=%d\n", n, m, t);
  while (t--) {
    InitBoard();  // 清空 vg 和 hg 的边缘
    int k;
    scanf("%d", &k);
    points.resize(k);
    for (int i = 0; i < k; i++) {
      ll x, p, color;  // 第 p 个点，边权是 x，颜色是 color
      scanf("%lld%lld%lld", &x, &p, &color);
      const int kP = p;
      const auto [X, Y, gP] = kIndexPos[kP];
      points[i] = {kP, gP, color};
      if (p <= m) {
        vg[X][Y] = {x, color};
      } else if (p <= n + m) {
        hg[X][Y - 1] = {x, color};
      } else if (p <= m + n + m) {
        vg[X - 1][Y] = {x, color};
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