/*
ID: tiankonguse
TASK: I、添加、总结
LANG: C++
MAC EOF: ctrl+D
link:
https://codeforces.com/edu/course/3/lesson/10/4/practice/contest/324369/problem/I
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

ll M = 1LL << 32;
ll a, b;
ll cur = 0;
ll nextRand() {
  cur = (cur * a + b) % M;
  return cur >> 8;
}

int n = 1 << 24;
vector<ll> preSums;
int m, q;
ll adding;
int l, r;
void Solver() {  //
  preSums.resize(n + 10, 0);
  scanf("%d%d%lld%lld", &m, &q, &a, &b);
  while (m--) {
    adding = nextRand();
    l = nextRand();
    r = nextRand();
    if (l > r) swap(l, r);
    l++, r++;
    preSums[l] = (preSums[l] + adding) % M;
    preSums[r + 1] = (preSums[r + 1] - adding) % M;
  }
  ll pre = 0;
  for (int i = 0; i < n; i++) {
    pre = (pre + preSums[i + 1]) % M;
    preSums[i + 1] = (preSums[i] + pre) % M;
  }
  ll ans = 0;
  while (q--) {
    l = nextRand();
    r = nextRand();
    if (l > r) swap(l, r);
    l++, r++;
    ans = (M + ans + preSums[r] - preSums[l - 1]) % M;
  }
  printf("%lld\n", ans);
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