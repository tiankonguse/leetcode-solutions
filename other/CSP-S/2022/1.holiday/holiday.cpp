/*
ID: tiankonguse
TASK: holiday
LANG: C++
MAC EOF: ctrl+D
link: https://www.luogu.com.cn/problem/P8817
PATH: P8817 [CSP-S 2022] 假期计划
submission:
*/
#define TASK "holiday"
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

void InitIO() {  //
#ifdef USACO_LOCAL_JUDGE
#define TASKNO ""
  freopen(TASK TASKNO ".in", "r", stdin);
  freopen(TASK TASKNO ".out", "w", stdout);
#endif
}

int n, m, k;
vector<vector<int>> g;            // 原始图
vector<vector<pair<ll, int>>> G;  // k 步可达图
vector<int> goOne;                // 是否可以到达顶点 1
vector<int> scores;               // 每个点的分数

void Input() {
  scanf("%d%d%d", &n, &m, &k);
  g.resize(n + 1);
  scores.resize(n + 1);
  scores[1] = 0;
  for (int i = 2; i <= n; i++) {
    scanf("%d", &scores[i]);
  }
  for (int i = 0; i < m; i++) {
    int u, v;
    scanf("%d%d", &u, &v);
    g[u].push_back(v);
    g[v].push_back(u);
  }
}

void BuildG() {
  // 第一步：bfs 计算 k 步图
  queue<int> que;
  vector<int> vis(n + 1, 0);
  G.resize(n + 1);
  goOne.resize(n + 1, 0);
  for (int i = 1; i <= n; i++) {  // 以每个点为起点
    while (!que.empty()) que.pop();
    fill(vis.begin(), vis.end(), 0);
    que.push(i);
    vis[i] = 1;
    while (!que.empty()) {
      int u = que.front();
      que.pop();
      for (int v : g[u]) {
        if (vis[v]) continue;
        if (v == 1) {
          goOne[i] = 1;
        }
        vis[v] = 1;
        G[i].push_back({scores[v], v});
        que.push(v);
      }
    }
    sort(G[i].begin(), G[i].end());
  }
}

void Solver() {  //
  Input();
  BuildG();
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