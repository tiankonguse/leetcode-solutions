/*
ID: tiankonguse
TASK: E.叶戈尔和阵列
LANG: C++
MAC EOF: ctrl+D
link:
https://codeforces.com/edu/course/3/lesson/10/4/practice/contest/324369/problem/E
PATH: 社区课程 » 前缀和与差数组 » 步骤4 » 实践
submission:
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

void InitIO() {  //
}

int n, m, k;
vector<ll> nums;
vector<ll> preSums;
vector<ll> opNums;
vector<tuple<int, int, ll>> ops;
void Solver() {  //
  scanf("%d%d%d", &n, &m, &k);
  nums.resize(n);
  for (int i = 0; i < n; i++) {
    scanf("%lld", &nums[i]);
  }
  ops.resize(m);
  for (int i = 0; i < m; i++) {
    int l, r;
    ll d;
    scanf("%d%d%lld", &l, &r, &d);
    ops[i] = {l, r, d};
  }

  opNums.resize(m + 2, 0);
  while (k--) {
    int x, y;
    scanf("%d%d", &x, &y);
    opNums[x]++;
    opNums[y + 1]--;
  }

  preSums.resize(n + 2, 0);
  ll pre = 0;
  for (int i = 0; i < m; i++) {
    pre += opNums[i + 1];
    auto [l, r, d] = ops[i];
    preSums[l] += pre * d;
    preSums[r + 1] -= pre * d;
  }

  pre = 0;
  for (int i = 0; i < n; i++) {
    pre += preSums[i + 1];
    printf("%lld%c", nums[i] + pre, i + 1 == n ? '\n' : ' ');
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