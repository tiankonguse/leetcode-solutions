/*
ID: tiankonguse
TASK: D 核裂变
LANG: C++
MAC EOF: ctrl+D
link: https://www.luogu.com.cn/contest/210959
PATH:【LGR-210-Div.3】洛谷基础赛 #19 & ALFR Round 3
submission:
*/
#define TASK "D"
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
constexpr ll MOD = 998244353;

const double pi = acos(-1.0), eps = 1e-7;
const int inf = 0x3f3f3f3f, ninf = 0xc0c0c0c0, mod = 998244353;
const int max3 = 2010, max4 = 20010, max5 = 200010, max6 = 2000010;

template <class T>
using min_queue = priority_queue<T, vector<T>, greater<T>>;
template <class T>
using max_queue = priority_queue<T>;

ll n, m, k;
vector<int> nums_m;
vector<vector<int>> g;
void InitIO() {  //
                 // #ifdef USACO_LOCAL_JUDGE
                 //   freopen(TASK ".in", "r", stdin);
                 //   freopen(TASK ".out", "w", stdout);
                 // #endif
  scanf("%lld%lld%lld", &n, &k, &m);
  nums_m.reserve(n + 1);
  g.resize(n + 1);
  for (int i = 0; i < m; i++) {
    int v;
    scanf("%d", &v);
    nums_m.push_back(v);
  }
  for (int i = 1; i <= n; i++) {
    int a;
    scanf("%d", &a);
    g[i].resize(a);
    for (int j = 0; j < a; j++) {
      scanf("%d", &g[i][j]);
    }
  }
}

vector<int> flags;
vector<ll> ans;
void Solver() {  //
  flags.resize(n + 1, 0);
  ans.resize(n + 1, 0);

  for (int i = 0; i < m; i++) {
    const int u = nums_m[i];
    const ll ua = g[u].size();
    flags[u] = 1;

    // 外部来源，每一秒一个中子
    const ll leftK = k % mod;  // 当前秒也算
    ans[u] = (ans[u] + (ua + 1) * leftK) % mod;
  }
  int newPos = 0;
  int allNum = nums_m.size();
  for (ll K = 2; K <= k && newPos < allNum; K++) {
    const ll leftK = (k - K + 1) % mod;  // 当前秒也算
    for (int i = newPos; i < allNum; i++) {
      const int u = nums_m[i];
      for (const auto v : g[u]) {
        const ll va = g[v].size();

        // 第 K 秒开始，u 会向 v 发射一个中子，持续 leftK 秒
        ans[v] = (ans[v] + leftK) % mod;

        if (flags[v] == 0) {
          // 首次被击中，此后 leftK 秒都会被击中
          ans[v] = (ans[v] + va * leftK) % mod;

          flags[v] = 1;
          nums_m.push_back(v);
        }
      }
    }
    newPos = allNum;
    allNum = nums_m.size();
  }
  for (int i = 1; i <= n; i++) {
    printf("%lld%c", ans[i], i == n ? '\n' : ' ');
  }
}

void ExSolver() {
#ifdef USACO_LOCAL_JUDGE
  auto t1 = std::chrono::steady_clock::now();
#endif
  Solver();
#ifdef USACO_LOCAL_JUDGE
  auto t2 = std::chrono::steady_clock::now();
  auto my =
      std::chrono::duration_cast<std::chrono::duration<double, ratio<1, 1000>>>(
          t2 - t1);
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