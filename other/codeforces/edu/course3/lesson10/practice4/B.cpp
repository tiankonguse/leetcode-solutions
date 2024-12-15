/*
ID: tiankonguse
TASK: B. 在线段上添加等差级数
LANG: C++
MAC EOF: ctrl+D
link:
https://codeforces.com/edu/course/3/lesson/10/4/practice/contest/324369/problem/B
PATH: 社区课程 » 前缀和与差数组 » 步骤4 » 实践
submission: https://codeforces.com/edu/course/3/lesson/10/4/practice/contest/324369/submission/296414173
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

int n;
vector<ll> nums;
void InitIO() {  //
  scanf("%d", &n);
  nums.resize(n);
  for (int i = 0; i < n; i++) {
    scanf("%lld", &nums[i]);
  }
}

vector<ll> disDisNums;
vector<ll> disNums;
vector<ll> preSum;
void Solver() {  //
  disDisNums.resize(n + 3, 0);
  preSum.resize(n + 3, 0);
  int q;
  scanf("%d", &q);
  while (q--) {
    int l, r;
    ll d;
    scanf("%d%d%lld", &l, &r, &d);
    disDisNums[l] += d;
    disDisNums[r + 1] -= d;
    preSum[r + 1] -= (r - l + 1) * d;
  }

  disNums.resize(n + 3, 0);
  for (int i = 0; i <= n; i++) {
    disNums[i + 1] += disNums[i] + disDisNums[i + 1];
  }

  for (int i = 0; i <= n; i++) {
    preSum[i + 1] += preSum[i] + disNums[i + 1];
  }

  for (int i = 0; i < n; i++) {
    ll v = nums[i] + preSum[i + 1];
    printf("%lld%c", v, i + 1 == n ? '\n' : ' ');
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