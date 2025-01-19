/*
ID: tiankonguse
TASK: J. First Non-Bipartite Edge J. 第一非二分边
LANG: C++
MAC EOF: ctrl+D
link: https://codeforces.com/edu/course/2/lesson/7/2/practice/contest/289391/problem/J
PATH: ITMO Academy: pilot course » Disjoint Sets Union » Step 2 » Practice
submission: https://github.com/tiankonguse/leetcode-solutions/tree/master/other/codeforces/
*/
#define TASK "J-first-non-bipartite-edge"
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
int newNode;
void InitIO() {  //
#ifdef USACO_LOCAL_JUDGE
  freopen("demo.in", "r", stdin);
  // freopen(TASK ".out", "w", stdout);
#endif
  scanf("%d%d", &n, &m);
  newNode = n + 1;
}

struct Dsu {
  vector<int> pre;
  vector<int> colors;
  vector<int> heights;

  void Init(int n) {
    n += 2;
    pre.resize(n, 0);
    colors.resize(n, 0);
    heights.resize(n, 0);
    for (int i = 0; i < n; i++) {
      pre[i] = i;
      colors[i] = 0;
      heights[i] = 0;
    }
  }
  int Get(const int u) {
    if (u == pre[u]) {  // 根节点
      colors[u] = 0;    // 根节点，永远是0
      heights[u] = 0;
    } else if (pre[u] == pre[pre[u]]) {  // 第一层儿子
      colors[u] = 1;
      heights[u] = 1;
    } else {  // 进行路径压缩
      const int root = Get(pre[u]);
      colors[u] = 1 - colors[pre[u]];

      if (heights[pre[u]] == 2) {
        // 父亲在第二层，自己可以上升到第一层
        pre[u] = root;
        heights[u] = 1;
      } else {
        heights[u] = 2;
      }
    }

    return pre[pre[u]];  // 由于有两层，父亲的父亲才一定是根节点
  }
  void Union(const int u, const int v) {  // u->v
    const int uu = Get(u);
    const int vv = Get(v);
    if (uu != vv) {
      if (colors[u] == colors[v]) {  // 颜色相同，合并会反转儿子，故满足条件
        pre[vv] = pre[uu];
      } else {  // 颜色不同，合并会反转儿子，不满足条件，需要插入一个中间节点
        const int mid = newNode;
        pre[vv] = pre[mid];
        pre[mid] = pre[uu];
        newNode++;
      }
    }
  }
  int GetColor(const int u) {
    Get(u);
    return colors[u];
  }
};

Dsu dsu;
int b, e;
int ans = -1;
void Solver() {     //
  dsu.Init(n + m);  // 普通的并查集
  for (int i = 1; i <= m; i++) {
    scanf("%d%d", &b, &e);
    const int bb = dsu.Get(b);
    const int ee = dsu.Get(e);
    if (bb != ee) {
      dsu.Union(b, e);
    } else {
      if (dsu.GetColor(b) == dsu.GetColor(e)) {
        ans = i;
        break;
      }
    }
  }
  printf("%d\n", ans);
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