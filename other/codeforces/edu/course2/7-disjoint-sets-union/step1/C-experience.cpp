/*
ID: tiankonguse
TASK: C. Experience  C、经验
LANG: C++
MAC EOF: ctrl+D
link: https://codeforces.com/edu/course/2/lesson/7/1/practice/contest/289390/problem/C
PATH: ITMO Academy: pilot course » Disjoint Sets Union » Step 1 » Practice
submission: https://github.com/tiankonguse/leetcode-solutions/tree/master/other/codeforces/
*/
#define TASK "C-experience"
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
void InitIO() {  //
#ifdef USACO_LOCAL_JUDGE
  freopen("demo.in", "r", stdin);
  // freopen(TASK ".out", "w", stdout);
#endif
  scanf("%d%d", &n, &m);
}

struct Dsu {
  vector<int> pre;
  vector<int> val;
  void Init(int n) {
    pre.resize(n + 1, 0);
    val.resize(n + 1, 0);
    for (int i = 1; i <= n; i++) {
      pre[i] = i;
    }
  }
  int Get(int u) {
    if (pre[u] != pre[pre[u]]) {  // 需要向上压缩
      int p = pre[u];
      int pp = Get(p);
      val[u] += val[p];
      pre[u] = pp;
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
  void Add(int u, int v) {
    u = Get(u);
    val[u] += v;
  }
  int GetVal(int u) {
    int p = Get(u);
    if (p == u) {
      return val[p];  // 不可能，父节点全部是虚拟节点
    }
    return val[u] + val[p];
  }
};

char op[10];
Dsu dsu;
void Solver() {  //
  int unionIndex = n + 1;
  dsu.Init(n + m + 1);
  while (m--) {
    int u, v;
    scanf("%s", op);
    if (op[0] == 'j') {
      scanf("%d%d", &u, &v);
      int uu = dsu.Get(u);
      int vv = dsu.Get(v);
      if (uu != vv) {
        int p = unionIndex++;
        dsu.Union(p, uu);
        dsu.Union(p, vv);
      }
    } else if (op[0] == 'a') {
      scanf("%d%d", &u, &v);
      dsu.Add(u, v);
    } else {
      scanf("%d", &u);
      printf("%d\n", dsu.GetVal(u));
    }
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