/*
ID: tiankonguse
TASK: D. Shift + Esc
LANG: C++
MAC EOF: ctrl+D
link: https://codeforces.com/contest/2049/problem/D
PATH: Codeforces Round 994 (Div. 2)
submission:
*/
#define TASK "D"
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

int t;
void InitIO() {  //
#ifdef USACO_LOCAL_JUDGE
  freopen(TASK ".in", "r", stdin);
  freopen(TASK ".out", "w", stdout);
#endif
  scanf("%d", &t);
}

ll n, m, k;
ll nums[222][222];
ll dp[222][222][222];
ll dpMin[222][222];

inline ll Mymin(ll x, ll y) {
  if (x == -1) return y;
  if (y == -1) return x;
  return min(x, y);
}

inline ll Dis(int a, int b) {  // a -> b
  if (a >= b) {
    return (a - b) * k;
  } else {
    return (m - (b - a)) * k;
  }
}

ll Dfs(int x, int y, int p);
ll DfsMin(int x, int y) {
  ll& ret = dpMin[x][y];
  if (ret != -1) return ret;
  for (int i = 0; i < m; i++) {
    ll tmp = Dis(i, y) + Dfs(x, y, i);
    ret = Mymin(ret, tmp);
  }
  return ret;
}

ll Dfs(int x, int y, int p) {
  ll& ret = dp[x][y][p];
  if (ret != -1) return ret;
  ll now = nums[x][p];
  if (x + 1 == n && y + 1 == m) {
    return ret = now;
  }

  if (y < m - 1) {
    ll tmp = now + Dfs(x, y + 1, (p + 1) % m);
    ret = Mymin(ret, tmp);
  }

  if (x < n - 1) {
    ll tmp = now + DfsMin(x + 1, y);
    ret = Mymin(ret, tmp);
  }
  // printf("x=%d y=%d p=%d ret=%lld\n", x, y, p, ret);

  return ret;
}

ll SolverEx(ll) { return DfsMin(0, 0); }
void Solver() {  //
  while (t--) {
    scanf("%lld%lld%lld", &n, &m, &k);
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        scanf("%lld", &nums[i][j]);
        dpMin[i][j] = -1;
        for (int o = 0; o < m; o++) {
          dp[i][j][o] = -1;
        }
      }
    }
    printf("%lld\n", SolverEx(0));
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