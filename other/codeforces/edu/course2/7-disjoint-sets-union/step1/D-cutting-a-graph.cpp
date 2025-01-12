/*
ID: tiankonguse
TASK: D. Cutting a graph  D. 切割图形
LANG: C++
MAC EOF: ctrl+D
link: https://codeforces.com/edu/course/2/lesson/7/1/practice/contest/289390/problem/D
PATH: ITMO Academy: pilot course » Disjoint Sets Union » Step 1 » Practice
submission: https://github.com/tiankonguse/leetcode-solutions/tree/master/other/codeforces/
*/
#define TASK "D-cutting-a-graph"
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

int n, m, k;
set<pair<int, int>> edges;
vector<tuple<int, int, int>> ops;

char op[10];
void InitIO() {  //
#ifdef USACO_LOCAL_JUDGE
  freopen("demo.in", "r", stdin);
  // freopen(TASK ".out", "w", stdout);
#endif
  scanf("%d%d%d", &n, &m, &k);
  while (m--) {
    int u, v;
    scanf("%d%d", &u, &v);
    if (u > v) {
      swap(u, v);
    }
    edges.insert({u, v});
  }
  ops.reserve(k);
  while (k--) {
    int u, v;
    scanf("%s%d%d", op, &u, &v);
    if (u > v) {
      swap(u, v);
    }
    if (op[0] == 'c') {
      edges.erase({u, v});
      ops.push_back({0, u, v});
    } else {
      ops.push_back({1, u, v});
    }
  }
}

struct Dsu {
  vector<int> pre;
  void Init(int n) {
    pre.resize(n + 1, 0);
    for (int i = 1; i <= n; i++) {
      pre[i] = i;
    }
  }
  int Get(int u) {
    if (pre[u] != pre[pre[u]]) {  // 需要向上压缩
      pre[u] = Get(pre[u]);
    }
    return pre[u];
  }
  void Union(int u, int v) {  // 保证 u 是新节点
    u = Get(u);
    v = Get(v);
    if (u != v) {
      pre[v] = pre[u];
    }
  }
};

Dsu dsu;
void Solver() {  //
  vector<int> ans;
  ans.reserve(ops.size());
  dsu.Init(n);
  for (auto [u, v] : edges) {
    dsu.Union(u, v);
  }
  std::reverse(ops.begin(), ops.end());
  for (auto [o, u, v] : ops) {
    if (o == 0) {  // cut
      dsu.Union(u, v);
    } else {
      ans.push_back(dsu.Get(u) == dsu.Get(v));
    }
  }

  std::reverse(ans.begin(), ans.end());
  for (auto v : ans) {
    printf("%s\n", v ? "YES" : "NO");
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