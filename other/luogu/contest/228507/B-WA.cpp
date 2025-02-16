/*
ID: tiankonguse
TASK: ASPAP
LANG: C++
MAC EOF: ctrl+D
link:
PATH:
submission:
*/
#define TASK "B"
#define TASKEX ""

#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef unsigned long long ull;

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
const int inf = 0x3f3f3f3f, ninf = 0xc0c0c0c0, mod = 998244353;
const int max3 = 2010, max4 = 20010, max5 = 200010, max6 = 2000010;

template <class T>
using min_queue = priority_queue<T, vector<T>, greater<T>>;
template <class T>
using max_queue = priority_queue<T>;

int t;

vector<ull> A;
void InitIO() {  //
#ifdef USACO_LOCAL_JUDGE
  // freopen(TASK ".in", "r", stdin);
  // freopen(TASK ".out", "w", stdout);
#endif
  scanf("%d", &t);
  A.resize(21, 1);
  for (int i = 1; i <= 20; i++) {
    A[i] = A[i - 1] * i;
    // printf("i=%d A=%llu\n", i, A[i]);
  }
  /*
  i=1 A=1
  i=2 A=2
  i=3 A=6
  i=4 A=24
  i=5 A=120
  i=6 A=720
  i=7 A=5040
  i=8 A=40320
  i=9 A=362880
  i=10 A=3628800
  i=11 A=39916800
  i=12 A=479001600
  i=13 A=6227020800
  i=14 A=87178291200
  i=15 A=1307674368000
  i=16 A=20922789888000
  i=17 A=355687428096000
  i=18 A=6402373705728000
  i=19 A= 121645100408832000
  i=20 A=2432902008176640000
  */
}

ll qpow(ll x, ll v, ll mod) {
  x = x % mod;
  ll y = 1;
  while (v) {
    if (v & 1) y = y * x % mod;
    x = x * x % mod;
    v >>= 1;
  }
  return y;
}
ll inv(ll x, ll mod) { return qpow(x, mod - 2, mod); }

ull BigSum(ull n) {
  // n*(n+1)*(n+2)/6
  ull ans = 1;
  ans = (ans * n) % mod;
  ans = (ans * (n + 1)) % mod;
  ans = (ans * (n + 2)) % mod;
  ans = (ans * inv(6, mod)) % mod;
  return ans;
}

vector<int> nums;
vector<int> selectNums;
void Select(const ull N, ull k) {
  selectNums.clear();
  selectNums.push_back(0);  // 占位符
  for (int n = N; n >= 1; n--) {
    const ull K = A[n - 1];
    ull p = (k - 1) / K + 1;  // 选择第 p 个元素
    selectNums.push_back(nums[p]);
    for (int i = p + 1; i <= n; i++) {
      nums[i - 1] = nums[i];
    }
    k -= (p - 1) * K;
  }
}

ull S(const int n, const ull k) {  // n <= 20
  nums.resize(n + 1);
  for (int i = 1; i <= n; i++) {
    nums[i] = i;
  }
  Select(n, k);
  ull ans = 0;
  for (int i = 1, j = n; i <= n; i++, j--) {
    printf("i=%d v=%d j=%d\n", i, selectNums[i], j);
    ans = (ans + selectNums[i] * j) % mod;
  }
  return ans;
}

ull Solver(ull n, ull k) {  //
  ull ans = 0;
  if (n > 20) {
    ans = (BigSum(n) - BigSum(20) + mod) % mod;
    n = 20;
  }
  return (ans + S(n, k)) % mod;
}

void Check(int n) {
  const ull a = A[n];
  ull pre = S(n, 1);
  for (ull i = 2; i <= a; i++) {
    const ull now = S(n, i);
    printf("n=%d i=%llu v=%llu\n", n, i, now);
    if (now < pre) {
      printf("S(%d,%llu)=%llu > S(%d,%llu)=%llu\n", n, i - 1, pre, n, i, now);
    }
    pre = now;
  }
}
void Check() {
  for (int n = 1; n <= 8; n++) {
    Check(n);
  }
}

void Solver() {  //
  // Check();
  S(4, 6);
  S(4, 7);

  ull n, s;
  while (t--) {
    scanf("%llu%llu", &n, &s);
    printf("%llu\n", Solver(n, s));
  }
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