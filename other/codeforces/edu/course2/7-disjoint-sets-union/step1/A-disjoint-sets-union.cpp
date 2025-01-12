/*
ID: tiankonguse
TASK: A. Disjoint Sets Union  A. 不相交集并集
LANG: C++
MAC EOF: ctrl+D
link: https://codeforces.com/edu/course/2/lesson/7/1/practice/contest/289390/problem/A
PATH: ITMO Academy: pilot course » Disjoint Sets Union » Step 1 » Practice
submission: https://github.com/tiankonguse/leetcode-solutions/tree/master/other/codeforces/
*/
#define TASK "A-disjoint-sets-union"
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
  vector<int> height;
  vector<int> size;

  void Init(int n) {
    pre.resize(n + 1, 0);
    height.resize(n + 1, 0);
    size.resize(n + 1, 0);
    for (int i = 1; i <= n; i++) {
      pre[i] = i;
      height[i] = 0;
      size[i] = 1;
    }
  }
  int Get(int u) {
    while (pre[u] != u) {
      u = pre[u] = Get(pre[u]);
    }
    return pre[u];
  }
  void Union(int u, int v) {
    u = Get(u);
    v = Get(v);
    if (u != v) {
      if (height[u] < height[v]) {
        swap(u, v);
      }

      pre[v] = pre[u];
      size[u] += size[v];
      height[u] = max(height[u], height[v] + 1);  // 树高
    }
  }
};

char op[10];
Dsu dsu;
void Solver() {  //
  dsu.Init(n);
  while (m--) {
    int u, v;
    scanf("%s%d%d", op, &u, &v);
    if (op[0] == 'u') {
      dsu.Union(u, v);
    } else {
      printf("%s\n", dsu.Get(u) == dsu.Get(v) ? "YES" : "NO");
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