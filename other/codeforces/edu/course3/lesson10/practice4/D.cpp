/*
ID: tiankonguse
TASK: D. Pekora 和蹦床
LANG: C++
MAC EOF: ctrl+D
link:
https://codeforces.com/edu/course/3/lesson/10/4/practice/contest/324369/problem/D
PATH: 社区课程 » 前缀和与差数组 » 步骤4 » 实践
submission: https://codeforces.com/edu/course/3/lesson/10/4/practice/contest/324369/submission/296520814
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

int q, n;
vector<ll> nums;
vector<ll> preSums;
void InitIO() {  //
}

void Solver() {  //
  scanf("%d", &q);
  while (q--) {
    scanf("%d", &n);
    nums.resize(n);
    for (int i = 0; i < n; i++) {
      scanf("%lld", &nums[i]);
    }
    preSums.clear();
    preSums.resize(n + 4, 0);

    ll ans = 0;
    ll pre = 0;
    for (int i = 1; i <= n; i++) {
      const ll v = nums[i - 1];
      pre += preSums[i];  // 到达次数
      // printf("i=%d v=%d pre=%d\n", i, v, pre);

      if (v >= 2) { // [i+2, i+v] 全部加 1
        preSums[i + 2] += 1;
        if (i + v + 1 <= n) {
          preSums[i + v + 1] -= 1;
        }
      }

      if (v == 1) { // 有几个，都跳到下个位置
        preSums[i + 1] += pre;
        preSums[i + 2] -= pre;
      } else {
        ans += max(0ll, v - 1 - pre);
        preSums[i + 1] += max(0ll, pre - (v - 1));
        preSums[i + 2] -= max(0ll, pre - (v - 1));
      }
    }
    printf("%lld\n", ans);
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