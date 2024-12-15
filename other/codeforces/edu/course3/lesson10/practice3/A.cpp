/*
ID: tiankonguse
TASK: A.求矩形上的和
LANG: C++
MAC EOF: ctrl+D
link:
https://codeforces.com/edu/course/3/lesson/10/3/practice/contest/324368/problem/A
PATH: 社区课程 » 前缀和与差数组 » 步骤3 » 实践
submission: https://codeforces.com/edu/course/3/lesson/10/3/practice/contest/324368/submission/296397304
*/
#define TASK "demo"
#define TASKEX ""

#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

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
vector<vector<ll>> g;
void InitIO() {  //
  scanf("%d%d", &n, &m);
  g.resize(n, vector<ll>(m, 0));
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      scanf("%lld", &g[i][j]);
    }
  }
}

vector<vector<ll>> G;
int lx, ly, rx, ry;
void Solver() {  //
  G.resize(n + 1, vector<ll>(m + 1, 0));
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      G[i + 1][j + 1] = G[i][j + 1] + G[i + 1][j] - G[i][j] + g[i][j];
    }
  }

  int q;
  scanf("%d", &q);
  while (q--) {
    scanf("%d%d%d%d", &lx, &ly, &rx, &ry);
    printf("%lld\n",
           G[rx][ry] - G[lx - 1][ry] - G[rx][ly - 1] + G[lx - 1][ly - 1]);
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
  InitIO();
  ExSolver();
  return 0;
}

/*

*/