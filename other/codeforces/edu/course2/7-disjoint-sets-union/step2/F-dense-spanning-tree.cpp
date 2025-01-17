/*
ID: tiankonguse
TASK: F. Dense spanning tree  F. 密集生成树
LANG: C++
MAC EOF: ctrl+D
link: https://codeforces.com/edu/course/2/lesson/7/2/practice/contest/289391/problem/F
PATH: ITMO Academy: pilot course » Disjoint Sets Union » Step 2 » Practice
submission: https://github.com/tiankonguse/leetcode-solutions/tree/master/other/codeforces/
*/
#define TASK "F-dense-spanning-tree"
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

template <class T> using min_queue = priority_queue<T, vector<T>, greater<T>>;
template <class T> using max_queue = priority_queue<T>;

int n, m;
vector<tuple<ll, int, int>> edges;
void InitIO() {  //
#ifdef USACO_LOCAL_JUDGE
  freopen("demo.in", "r", stdin);
  // freopen(TASK ".out", "w", stdout);
#endif
  scanf("%d%d", &n, &m);
  edges.reserve(m);
  for (int i = 0; i < m; i++) {
    int b, e, w;
    scanf("%d%d%d", &b, &e, &w);
    edges.push_back({w, b, e});
  }
}

struct Dsu {
  vector<int> pre;
  vector<int> nodes;

  void Init(int n) {
    n += 2;
    pre.resize(n, 0);
    nodes.resize(n, 1);
    for (int i = 0; i < n; i++) {
      pre[i] = i;
      nodes[i] = 1;
    }
  }
  int Get(const int u) {
    if (pre[u] != pre[pre[u]]) {  // 父节点不是根节点
      pre[u] = Get(pre[u]);       // 递归调用父节点，转化为
    }
    return pre[u];
  }
  void Union(int u, int v) {
    u = Get(u);
    v = Get(v);
    if (u != v) {
      pre[v] = pre[u];
      nodes[u] += nodes[v];
    }
  }
};

int t, x, y;
Dsu dsu;
ll disVal = -1;
void UpdateAns(ll w) {
  if (disVal == -1) {
    disVal = w;
  } else {
    disVal = min(disVal, w);
  }
}
void Check() {
  ll preW = INT_MAX;
  for (int l = 0; l < m; l++) {
    auto [wl, bl, el] = edges[l];
    if (wl == preW) {
      continue;  // 相同的最小值，不会有更优答案
    }
    preW = wl;
    dsu.Init(n);  // 普通的并查集
    bool findAns = false;
    for (int r = l; r < m; r++) {
      auto [wr, br, er] = edges[r];
      dsu.Union(br, er);
      if (dsu.nodes[dsu.Get(br)] == n) {
        findAns = true;
        UpdateAns(wr - wl);
        break;
      }
    }
    if (disVal == 0) break;
    if (!findAns) break;
  }
}

void Solver() {  //
  sort(edges.begin(), edges.end());
  Check();
  if (disVal == -1) {
    printf("NO\n");
  } else {
    printf("YES\n");
    printf("%lld\n", disVal);
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