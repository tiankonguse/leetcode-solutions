/*
ID: tiankonguse
TASK: A. 前缀和的构造
LANG: C++
MAC EOF: ctrl+D
link: https://codeforces.com/edu/course/3/lesson/10/1/practice/contest/324365/problem/A
PATH: 社区课程 » 前缀和与差数组 » 步骤1 » 实践
submission: https://codeforces.com/edu/course/3/lesson/10/1/practice/contest/324365/submission/296394733
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

vector<ll> preSums;
void Solver() {  //
  preSums.resize(n + 1, 0);
  for (int i = 0; i < n; i++) {
    preSums[i + 1] = preSums[i] + nums[i];
  }
  for (int i = 0; i <= n; i++) {
    printf("%lld%c", preSums[i], i == n ? '\n' : ' ');
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