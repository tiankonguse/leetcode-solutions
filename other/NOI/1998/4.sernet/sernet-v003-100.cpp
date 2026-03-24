/*
ID: tiankonguse
TASK: sernet
LANG: C++
MAC EOF: ctrl+D
link:
PATH:
submission:
*/
#define TASK "sernet"
#define TASKEX ""

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
int debug_log = 0;
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
const int inf = 0x3f3f3f3f, ninf = 0xc0c0c0c0, mod = 1000000007;
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

int n;
typedef pair<ll, ll> pll;
vector<vector<pair<ll, ll>>> g;  // 允许有重复边
unordered_map<int, int> nodes;
ll T;

bool Bfs(ll packId, ll startTime, ll srcNodeId, ll dstNodeId) {
  MyPrintf("packId = %lld, startTime = %lld, srcNodeId = %lld, dstNodeId = %lld\n", packId, startTime, srcNodeId,
           dstNodeId);
  if (srcNodeId == dstNodeId) {
    dstNodeId = -1;  // 如果源点就是终点，标记为终点不存在
  }
  vector<ll> dist(n, INF);
  dist[srcNodeId] = 0;
  priority_queue<pll, vector<pll>, greater<pll>> pque;
  pque.push({0, srcNodeId});
  while (!pque.empty()) {
    auto [d, u] = pque.top();
    pque.pop();
    if (dist[u] < d) continue;     // 重复到达，截止
    if (u == dstNodeId) continue;  // 终点截止
    // 时间 d 到达了顶点 u
    for (auto [v, w] : g[u]) {
      if (startTime + d + w > T) {
        return true;  // 到达 T 时，数据包还在路上
      }
      if (d + w < dist[v]) {
        dist[v] = d + w;
        pque.push({dist[v], v});
      }
    }
  }
  return false;  //
}

void Solver() {  //
  scanf("%d", &n);
  for (int i = 0; i < n; i++) {
    int v;
    scanf("%d", &v);
    int id = nodes.size();
    nodes[v] = id;
    MyPrintf("v(%d) -> id(%d)\n", v, id);
  }
  n = nodes.size();  // 避免输入有重复的顶点
  g.resize(n);

  int m;
  scanf("%d", &m);
  for (int i = 0; i < m; i++) {
    ll u, v, w;
    scanf("%lld%lld%lld", &u, &v, &w);
    u = nodes[u];
    v = nodes[v];
    g[u].push_back({v, w});
    g[v].push_back({u, w});
  }

  vector<tuple<ll, ll, ll, ll>> packs;
  int k;
  scanf("%d", &k);
  packs.reserve(k);
  for (int i = 0; i < k; i++) {
    ll packId, startTime, srcNodeId, dstNodeId;
    scanf("%lld%lld%lld%lld", &packId, &startTime, &srcNodeId, &dstNodeId);
    packs.emplace_back(packId, startTime, nodes[srcNodeId], nodes[dstNodeId]);
  }
  scanf("%lld", &T);
  int ans = 0;
  for (auto [packId, startTime, srcNodeId, dstNodeId] : packs) {
    if (Bfs(packId, startTime, srcNodeId, dstNodeId)) {
      ans++;
    }
  }

  printf("%d\n", ans);
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
