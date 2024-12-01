/*
ID: tiankonguse
TASK: schlnet
LANG: C++
MAC EOF: ctrl+D
*/
#define TASK "schlnet"
#define TASKEX "-smp"

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

int debug = 0;
#define MyPrintf(...)               \
  do {                              \
    if (debug) printf(__VA_ARGS__); \
  } while (0)

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

void InitIO() {
#ifndef USACO_LOCAL_JUDGE
  freopen(TASK ".in", "r", stdin);
  freopen(TASK ".out", "w", stdout);
#endif
}

int g[111][111];
int n;

vector<int> merged;
vector<int> visited;   // 全局
vector<int> path;      // dfs 的一个具体路径
vector<int> pashHash;  // dfs 的一个具体路径

void Merge(const int u, const int v) {
  for (int i = 1; i <= n; i++) {
    if (g[i][v]) {
      g[i][u] = 1;
      g[i][v] = 0;
    }
    if (g[v][i]) {
      g[u][i] = 1;
      g[v][i] = 0;
    }
  }
  merged[v] = 1;
}

int DfsMerge(const int u) {
  if (pashHash[u] != -1) {  // 遇到一个环
    return u;
  }
  if (visited[u]) return -1;  // 访问过，不在路径上，确保没有环

  visited[u] = 1;
  pashHash[u] = path.size();
  path.push_back(u);

  int mergedToNode = -1;
  for (int v = 1; v <= n; v++) {
    if (g[u][v] == 0) continue;
    mergedToNode = DfsMerge(v);
    if (mergedToNode == -1) continue;
    if (mergedToNode == u) {
      mergedToNode = -1;
    } else {
      break;
    }
  }
  // 当前节点被合并到 mergedToNode
  if (mergedToNode != -1) {
    Merge(mergedToNode, u);
  }
  path.pop_back();
  pashHash[u] = -1;
  return mergedToNode;
}

void MergeLoopToMin() {
  visited.resize(n + 1, 0);
  merged.resize(n + 1, 0);
  pashHash.resize(n + 1, -1);
  path.reserve(n + 1);
  for (int u = 1; u <= n; u++) {
    if (visited[u]) continue;
    DfsMerge(u);
  }
}

void Solver() {  //
  memset(g, 0, sizeof(g));
  scanf("%d", &n);
  for (int u = 1, v = 0; u <= n; u++) {
    v = 1;
    while (v) {
      scanf("%d", &v);
      g[u][v] = 1;
    }
  }

  // 环缩点
  MergeLoopToMin();

  //   for (int i = 1; i <= n; i++) {
  //     printf("i=%d merged=%d\n", i, merged[i]);
  //   }
  //   printf("%d: ", 0);
  //   for (int v = 1; v <= n; v++) {
  //     printf("%d ", v);
  //   }
  //   printf("\n");
  //   for (int u = 1; u <= n; u++) {
  //     printf("%d: ", u);
  //     for (int v = 1; v <= n; v++) {
  //       printf("%d ", g[u][v]);
  //     }
  //     printf("\n");
  //   }

  int zeroInDeg = 0;
  int zeroOutDeg = 0;
  int mergeNum = 0;
  for (int u = 1; u <= n; u++) {
    if (merged[u]) {
      mergeNum++;
      continue;
    }
    int inDeg = 0, outDeg = 0;
    for (int v = 1; v <= n; v++) {
      if (merged[v]) continue;
      if (u == v) continue;
      inDeg += g[v][u];
      outDeg += g[u][v];
    }
    if (inDeg == 0) {
      zeroInDeg++;
    }
    if (outDeg == 0) {
      zeroOutDeg++;
    }
  }
  int ans1 = zeroInDeg;
  int ans2 = max(zeroInDeg, zeroOutDeg);
  if (mergeNum + 1 == n) {  // 缩点缩到1个
    ans2 = 0;
  }

  printf("%d\n%d\n", ans1, ans2);
}

int main(int argc, char** argv) {
  CheckUsacoTask();
  InitIO();
  Solver();
  return 0;
}

/*

*/