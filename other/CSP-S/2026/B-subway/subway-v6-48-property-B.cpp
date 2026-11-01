/*
ID: tiankonguse
TASK: subway
LANG: C++
MAC EOF: ctrl+D
link: https://www.luogu.com.cn/problem/P17832
PATH: P17832 [CSP-S 2026] 地铁 / subway
submission:
*/
#define TASK "subway"
#define TASKEX "-tmp"

#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

void CheckUsacoTask() {
#ifdef USACO_LOCAL_JUDGE
  // 获取当前文件的完整路径
  string filePath = __FILE__;
  // 从路径中提取文件名（包含扩展名）
  string fileNameEx = filePath.substr(filePath.rfind('/') + 1);
  // 提取文件名（不包含扩展名）
  string fileName = fileNameEx.substr(0, fileNameEx.find("."));
  // 检查文件名是否与预定义的 TASK 和 TASKEX 匹配
  assert(fileName == TASK TASKEX);
#endif
}

#ifdef USACO_LOCAL_JUDGE
int debug_log = 1;
int debug_assert = 0;
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
// const int inf = 0x3f3f3f3f, ninf = 0xc0c0c0c0, mod = 1000000007;
const int max3 = 2010, max4 = 20010, max5 = 200010, max6 = 2000010;

template <class T>
using min_queue = priority_queue<T, vector<T>, greater<T>>;
template <class T>
using max_queue = priority_queue<T>;

void InitIO(int fileIndex) {  //
// #define LOCAL_IO 1
#ifdef USACO_LOCAL_JUDGE
#define MAX_TIME 2000
#ifdef LOCAL_IO
#define USACO_TASK_FILE 0
// #define TASKNO 20
#ifdef TASKNO
  fileIndex = TASKNO;
#endif
  string fileInName = string(TASK) + to_string(fileIndex) + ".in";
  string fileOutName = string(TASK) + to_string(fileIndex) + ".out";
  freopen(fileInName.c_str(), "r", stdin);
  freopen(fileOutName.c_str(), "w", stdout);
#endif
#endif
}

void Floyd(vector<vector<ll>>& mp) {  // mp[][] = inf; mp[i][i] = 0;
  int n = mp.size();
  for (int i = 0; i < n; i++) {
    mp[i][i] = 0;
  }
  for (int k = 0; k < n; k++) {
    for (int i = 0; i < n; i++) {
      if (i == k) continue;
      for (int j = 0; j < n; j++) {
        if (mp[i][k] + mp[k][j] < mp[i][j]) {
          mp[i][j] = mp[i][k] + mp[k][j];
        }
      }
    }
  }
}

void Dijkstra(int s, int n, vector<vector<pair<ll, ll>>>& S, vector<ll>& dist) {
  // dist.assign(n, INFL);
  dist[s] = 0;
  priority_queue<pair<ll, ll>, vector<pair<ll, ll>>, greater<pair<ll, ll>>> pque;
  pque.push({0, s});
  while (!pque.empty()) {
    auto p = pque.top();
    pque.pop();
    ll v = p.second, d = p.first;
    if (dist[v] < d) continue;
    for (auto& [to, cost] : S[v]) {
      if (dist[to] > dist[v] + cost) {
        dist[to] = dist[v] + cost;
        pque.push({dist[to], to});
      }
    }
  }
}

void Bfs(int s, int n, vector<vector<pair<ll, ll>>>& S, vector<ll>& dist) {
  queue<ll> que;
  que.push(s);
  dist[s] = 0;
  while (!que.empty()) {
    ll u = que.front();
    que.pop();
    for (auto& [v, cost] : S[u]) {
      if (dist[v] != INFL) continue;
      que.push(v);
      dist[v] = dist[u] + cost;
    }
  }
}

ll c, n, m, d, q;
vector<ll> W;                         // 每个地铁站的地铁口走到站厅需要的时间
vector<vector<pair<ll, ll>>> subway;  // 每个线路经过的地铁站与站点到站厅的时间
vector<pair<ll, ll>> querys;
vector<vector<pair<ll, ll>>> stations;        // 经过每个地铁站的线路，以及位于线路的第几个站
vector<vector<ll>> adjacencyMatrix;           // 邻接矩阵，表示每个线路之间的最小换乘时间
vector<vector<pair<ll, ll>>> adjacencyTable;  // 邻接表
unordered_set<int> queryStations;
ll tMax = 0, tMin = INT64_MAX;

void Intput() {
  scanf("%lld %lld %lld %lld %lld", &c, &n, &m, &d, &q);
  W.resize(m);
  for (int i = 0; i < m; i++) {
    scanf("%lld", &W[i]);
  }
  stations.resize(m);
  subway.resize(n);
  tMax = 0, tMin = INT64_MAX;
  for (int i = 0; i < n; i++) {
    ll k;
    scanf("%lld", &k);
    subway[i].resize(k);
    for (int j = 0; j < k; j++) {
      ll a, t;
      scanf("%lld %lld", &a, &t);
      tMax = max(tMax, t);
      tMin = min(tMin, t);
      a--;
      subway[i][j] = {a, t};
      stations[a].push_back({i, j});
    }
  }
  querys.resize(q);
  for (int i = 0; i < q; i++) {
    ll x, y;
    scanf("%lld %lld", &x, &y);
    x--, y--;
    queryStations.insert(x);
    queryStations.insert(y);
    querys[i] = {x, y};
  }
}

bool PropertyB() {  //
  return tMax == tMin;
}

void BuildEdge() {  //
  // 线路: (0,m), 站点: [m,n+m)
  adjacencyMatrix.resize(n + m, vector<ll>(n + m, INFL));
  adjacencyTable.resize(n + m);
  for (int lineId = 0; lineId < n; lineId++) {
    int u = m + lineId;
    for (auto [stationId, lineStationCost] : subway[lineId]) {
      int v = stationId;
      adjacencyTable[u].push_back({v, lineStationCost});
      adjacencyTable[v].push_back({u, lineStationCost});
      // adjacencyMatrix[u][v] = adjacencyMatrix[v][u] = lineStationCost;
    }
  }
  // g.resize(n + m);
  for (int stationId : queryStations) {
    if (PropertyB()) {
      Bfs(stationId, n + m, adjacencyTable, adjacencyMatrix[stationId]);
    } else {
      Dijkstra(stationId, n + m, adjacencyTable, adjacencyMatrix[stationId]);
    }
  }
  // Floyd(adjacencyMatrix);  // 求所有线路之间的最小换乘时间
}

void BuildQuery() {
  for (auto [x, y] : querys) {
    ll baseCost = W[x] + W[y] + adjacencyMatrix[x][y];
    printf("%lld\n", baseCost);
  }
}

bool PropertyA() {  //
  for (auto& line : subway) {
    if (line.size() > 2) return false;
  }
  return true;
}
void SolverA() {
  // 性质A：每条线路至多 2 个站点
  // 考虑连通性，如果一个线路只有一个站点，则这个线路永远不会使用
  // 构图1：基于站点构图，排除掉线路
  adjacencyMatrix.resize(m, vector<ll>(m, INFL));
  adjacencyTable.resize(m);
  for (auto& line : subway) {
    if (line.size() == 1) continue;
    auto [u, uCost] = line[0];
    auto [v, vCost] = line[1];
    // 可能有重复边
    adjacencyTable[u].push_back({v, vCost + uCost});
    adjacencyTable[v].push_back({u, vCost + uCost});
    // ll cost = min(vCost + uCost, AdjacencyMatrix[u][v]);
    // AdjacencyMatrix[u][v] = AdjacencyMatrix[v][u] = cost;
  }
  // Floyd(AdjacencyMatrix);  // 求所有线路之间的最小换乘时间
  for (int stationId : queryStations) {
    Dijkstra(stationId, m, adjacencyTable, adjacencyMatrix[stationId]);
  }
  BuildQuery();
}

void Solver() {  //
  Intput();
  if (PropertyA()) {
    SolverA();
    return;
  }
  BuildEdge();
  BuildQuery();
}

#ifdef USACO_LOCAL_JUDGE
double costTime = 0;
#endif
void ExSolver() {
#ifdef USACO_LOCAL_JUDGE
  auto t1 = std::chrono::steady_clock::now();
#endif
  Solver();
#ifdef USACO_LOCAL_JUDGE
  auto t2 = std::chrono::steady_clock::now();
  auto my = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1);
  costTime = my.count();
#ifndef USACO_TASK_FILE
  MyPrintf("my 用时: %.0lfms\n", costTime);
#endif
#endif
}

#ifdef USACO_TASK_FILE
#include <unistd.h>

#include <cstdio>
int AC = 0;
void DiffAns(int stdout_fd, int i) {
  dup2(stdout_fd, STDOUT_FILENO);
  close(stdout_fd);
  stdout = fdopen(STDOUT_FILENO, "w");
  int fileIndex = i;
#ifdef TASKNO
  fileIndex = TASKNO;
#endif
  string fileAns = string(TASK) + to_string(fileIndex) + ".ans";
  string fileOut = string(TASK) + to_string(fileIndex) + ".out";
  string cmd = string("diff -w " + fileAns + " " + fileOut + " > /dev/null");
  if (system(cmd.c_str())) {
    MyPrintf("case %d: Wrong answer, cost %.0lfms\n", i, costTime);
  } else {
    if (costTime > MAX_TIME) {
      MyPrintf("case %d: Time Limit Exceeded, cost %.0lfms\n", i, costTime);
    } else {
      AC++;
      MyPrintf("case %d: Accepted, cost %.0lfms\n", i, costTime);
    }
  }
}
void DiffSummary(int stdout_fd) {  // 统计通过的用例数量和得分
  dup2(stdout_fd, STDOUT_FILENO);
  close(stdout_fd);
  stdout = fdopen(STDOUT_FILENO, "w");
  MyPrintf("Total: %d / %d, 得分： %d\n", AC, USACO_TASK_FILE, AC * (100 / USACO_TASK_FILE));
}
#endif
int main(int argc, char** argv) {
  CheckUsacoTask();
  int fileIndex = 1;
#ifdef USACO_TASK_FILE
  // 保存当前的 stdout 文件指针
  int stdout_fd = dup(STDOUT_FILENO);
  for (int i = 1; i <= USACO_TASK_FILE; i++) {
    fileIndex = i;
#endif
    InitIO(fileIndex);
    ExSolver();
#ifdef USACO_TASK_FILE
    fclose(stdout);
    DiffAns(stdout_fd, i);
    stdout_fd = dup(STDOUT_FILENO);
  }
  DiffSummary(stdout_fd);
#endif
  return 0;
}
