/*
ID: tiankonguse
TASK: E. Monkeys  E. 猴子
LANG: C++
MAC EOF: ctrl+D
link: https://codeforces.com/edu/course/2/lesson/7/1/practice/contest/289390/problem/E
PATH: ITMO Academy: pilot course » Disjoint Sets Union » Step 1 » Practice
submission: https://github.com/tiankonguse/leetcode-solutions/tree/master/other/codeforces/
*/
#define TASK "E-monkeys"
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

int n, m;
map<pair<int, int>, int> edges;
vector<tuple<int, int, int>> ops;

char op[10];
void InitIO() {  //
#ifdef USACO_LOCAL_JUDGE
  freopen("demo.in", "r", stdin);
  // freopen(TASK ".out", "w", stdout);
#endif
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= n; i++) {
    int l, r;
    scanf("%d%d", &l, &r);
    if (l != -1) {
      edges[{i, 1}] = l;
    }
    if (r != -1) {
      edges[{i, 2}] = r;
    }
  }
  ops.reserve(m);
  for (int i = 0; i < m; i++) {
    int p, h;
    scanf("%d%d", &p, &h);
    pair<int, int> pp = {p, h};
    auto it = edges.find(pp);  // 保证一定存在
    ops.push_back({p, h, it->second});
    edges.erase(it);
  }
}

struct Dsu {
  vector<int> pre;
  vector<int> val;
  void Init(int n) {
    pre.resize(n + 1, 0);
    val.resize(n + 1, -1);
    for (int i = 1; i <= n; i++) {
      pre[i] = i;
    }
  }
  int Get(int u) {
    if (pre[u] != pre[pre[u]]) {  // 需要向上压缩
      int p = pre[u];
      pre[u] = Get(p);
      if (val[p] != -1 && val[u] == -1) {
        val[u] = val[p];
      }
    }
    if (val[pre[u]] != -1 && val[u] == -1) {
      val[u] = val[pre[u]];
    }
    return pre[u];
  }
  void Union(int u, int v) {  // 大的合并到小的
    u = Get(u);
    v = Get(v);
    if (u != v) {
      if (u > v) {
        swap(u, v);
      }
      pre[v] = pre[u];
    }
  }
  void Set(int u, int v) {  //
    val[u] = v;
  }
};

Dsu dsu;

void Solver() {  //
  dsu.Init(n);
  for (auto [pp, v] : edges) {
    auto [p, h] = pp;
    dsu.Union(p, v);
  }
  for (int i = m - 1; i >= 0; i--) {
    auto [p, h, v] = ops[i];
    int pp = dsu.Get(p);
    int vv = dsu.Get(v);
    if (pp == vv) {
      continue;
    }
    if (pp == 1) {
      dsu.Set(vv, i);
    } else if (vv == 1) {
      dsu.Set(pp, i);
    }
    dsu.Union(pp, vv);
  }
  for (int i = 1; i <= n; i++) {
    dsu.Get(i);
    printf("%d\n", dsu.val[i]);
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