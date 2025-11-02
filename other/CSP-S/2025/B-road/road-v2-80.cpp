/*
ID: tiankonguse
TASK: road
LANG: C++
MAC EOF: ctrl+D
link:
PATH:
submission:
ides: 如果一个边原先不在原最小生成树上，那么枚举乡村时，这个边也不可能在新的最小生成树上。
*/
#define TASK "road"
#define TASKEX "-v2-80"

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
#ifdef LOCAL_IO
#define USACO_TASK_FILE 0
#define TASKNO 1
#ifndef USACO_TASK_FILE
  fileIndex = TASKNO;
#endif
  string fileInName = string(TASK) + to_string(fileIndex) + ".in";
  string fileOutName = string(TASK) + to_string(fileIndex) + ".out";
  freopen(fileInName.c_str(), "r", stdin);
  freopen(fileOutName.c_str(), "w", stdout);
#endif
#endif
}

class Dsu {
  vector<int> fa, score;

 public:
  void Init(int n) {
    fa.resize(n);
    score.resize(n);
    for (int i = 0; i < n; i++) {
      fa[i] = i, score[i] = 0;
    }
  }

  int Find(int x) {
    if (fa[x] != x) {
      fa[x] = Find(fa[x]);
    }
    return fa[x];
  }

  // Union，也成为了 Merge
  void Union(int x, int y) {
    x = Find(x);
    y = Find(y);
    if (x != y) {
      if (score[x] > score[y]) {
        fa[y] = x;
      } else {
        fa[x] = y;
        if (score[x] == score[y]) {
          ++score[y];
        }
      }
    }
  }
  void AddScore(int x) {
    x = Find(x);
    score[x]++;
  }

  int GetScore(int x) {
    x = Find(x);
    return score[x];
  }
};

int n, m, k;
vector<tuple<ll, int, int>> baseEdges;
vector<tuple<ll, int, int>> selectEdges;
vector<ll> townCosts;
vector<vector<ll>> townEdgeCosts;
Dsu dsu;

void Input() {
  scanf("%d%d%d", &n, &m, &k);
  baseEdges.reserve(m);
  for (int i = 0; i < m; i++) {
    int u, v;
    ll w;
    scanf("%d%d%lld", &u, &v, &w);
    u--, v--;
    baseEdges.push_back({w, u, v});
  }
  townCosts.resize(k);
  townEdgeCosts.resize(k, vector<ll>(n, 0));
  for (int i = 0; i < k; i++) {
    scanf("%lld", &townCosts[i]);
    for (int j = 0; j < n; j++) {
      scanf("%lld", &townEdgeCosts[i][j]);
    }
  }
}

ll ans = 0;
ll MinimumSpanningTree(ll cost, vector<tuple<ll, int, int>>& townSelectEdges) {
  dsu.Init(n + k);
  int baseIndex = 0, baseSize = selectEdges.size();
  int townIndex = 0, townSize = townSelectEdges.size();
  auto MinEdge = [&]() -> tuple<ll, int, int> {
    if (baseIndex == baseSize) {
      return townSelectEdges[townIndex++];
    }
    if (townIndex == townSize) {
      return selectEdges[baseIndex++];
    }
    if (get<0>(selectEdges[baseIndex]) < get<0>(townSelectEdges[townIndex])) {
      return selectEdges[baseIndex++];
    }
    return townSelectEdges[townIndex++];
  };
  while (baseIndex < baseSize || townIndex < townSize) {
    auto [w, u, v] = MinEdge();
    if (dsu.Find(u) != dsu.Find(v)) {
      dsu.Union(u, v);
      cost += w;
    }
    if (cost >= ans) {
      return cost;
    }
  }
  return cost;
}

void Solver() {  //
  Input();

  // 第一步：求原生最小生成树
  sort(baseEdges.begin(), baseEdges.end());
  dsu.Init(n + k);
  selectEdges.reserve(n - 1);
  ans = 0;
  for (auto [w, u, v] : baseEdges) {
    if (dsu.Find(u) != dsu.Find(v)) {
      dsu.Union(u, v);
      ans += w;
      selectEdges.push_back({w, u, v});
    }
  }

  baseEdges.reserve(k * n);
  const int MASK = (1 << k) - 1;
  for (int sub = MASK; sub; sub = (sub - 1) & MASK) {
    baseEdges.clear();
    ll subCost = 0;
    for (int i = 0; i < k; i++) {
      if ((sub >> i) & 1) {
        // 选择第 i 个乡村
        subCost += townCosts[i];
        for (int j = 0; j < n; j++) {
          ll w = townEdgeCosts[i][j];
          int u = n + i;
          int v = j;
          baseEdges.push_back({w, u, v});
        }
      }
    }
    sort(baseEdges.begin(), baseEdges.end());
    ll totalCost = MinimumSpanningTree(subCost, baseEdges);
    ans = min(ans, totalCost);
  }
  printf("%lld\n", ans);
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
  auto my = std::chrono::duration_cast<std::chrono::duration<double, ratio<1, 1000>>>(t2 - t1);
  costTime = my.count();
#ifndef USACO_TASK_FILE
  printf("my 用时: %.0lfms\n", costTime);
#endif
#endif
}

#ifdef USACO_TASK_FILE
#include <unistd.h>

#include <cstdio>
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
  }
  dup2(stdout_fd, STDOUT_FILENO);
  close(stdout_fd);
  stdout = fdopen(STDOUT_FILENO, "w");
  for (int i = 1; i <= USACO_TASK_FILE; i++) {
    int fileIndex = i;
    string fileAns = string(TASK) + to_string(fileIndex) + ".ans";
    string fileOut = string(TASK) + to_string(fileIndex) + ".out";
    string cmd = string("diff -w " + fileAns + " " + fileOut);
    if (system(cmd.c_str())) {
      printf("case %d: Wrong answer, cost %.0lfms\n", i, costTime);
    } else {
      printf("case %d: Accepted, cost %.0lfms\n", i, costTime);
    }
  }
#endif
  return 0;
}
