/*
ID: tiankonguse
TASK: H. 高山
LANG: C++
MAC EOF: ctrl+D
link:
https://codeforces.com/edu/course/3/lesson/10/4/practice/contest/324369/problem/H
PATH: 社区课程 » 前缀和与差数组 » 步骤4 » 实践
submission: https://codeforces.com/edu/course/3/lesson/10/4/practice/contest/324369/submission/296719033
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

int n, q, k, l, r;
ll x;
vector<ll> nums;
vector<ll> preSums;
void Solver() {  //
  scanf("%d", &n);
  nums.resize(n + 2, 0);
  for (int i = 0; i < n; i++) {
    scanf("%lld", &nums[i]);
  }
  scanf("%d", &q);
  preSums.resize(n + 2, 0);
  while (q--) {
    scanf("%d%lld", &k, &x);
    l = n - k + 1;
    r = n;
    preSums[l] += x;
    preSums[r + 1] -= x;
  }
  ll pre = 0;
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