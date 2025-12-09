/*
ID: tiankonguse
TASK: sale
LANG: C++
MAC EOF: ctrl+D
link:
PATH:
submission:
*/
#define TASK "sale"
#define TASKEX ""

#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

void CheckUsacoTask() {
#ifdef USACO_LOCAL_JUDGE
  // 获取当前文件的完整路径
  string filePath = __FILE__;
  // 从路径中提取文件名（包含扩展名）
  string fileNameEx = filePath.substr(filePath.rfind('/') + 1);
  // 提取文件名（不包含扩展名）
  string fileName = fileNameEx.substr(0, fileNameEx.find("."));
  // 检查文件名是否与预定义的 TASK 和 TASKEX 匹配
  assert(fileName == TASK TASKEX);
#endif
}

#ifdef USACO_LOCAL_JUDGE
int debug_log = 0;
int debug_assert = 0;
#define MyPrintf(...)                   \
  do {                                  \
    if (debug_log) printf(__VA_ARGS__); \
  } while (0)

#define MyAssert(...)                      \
  do {                                     \
    if (debug_assert) assert(__VA_ARGS__); \
  } while (0)
#else
#define MyPrintf(...)
#define MyAssert(...)
#endif

constexpr int INF = 1 << 30;
constexpr ll INFL = 1LL << 60;
constexpr ll MOD = 1000000007;

const double pi = acos(-1.0), eps = 1e-7;
const int inf = 0x3f3f3f3f, ninf = 0xc0c0c0c0, mod = 998244353;
const int max4 = 10010, max5 = 200010, max6 = 2000010;

template <class T>
using min_queue = priority_queue<T, vector<T>, greater<T>>;
template <class T>
using max_queue = priority_queue<T>;

void InitIO(int fileIndex) {  //
#define LOCAL_IO 1
#ifdef USACO_LOCAL_JUDGE
#define MAX_TIME 2000
#ifdef LOCAL_IO
#define USACO_TASK_FILE 11
// #define TASKNO 20
#ifdef TASKNO
  fileIndex = TASKNO;
#endif
  string fileInName = string(TASK) + to_string(fileIndex) + ".in";
  string fileOutName = string(TASK) + to_string(fileIndex) + ".out";
  freopen(fileInName.c_str(), "r", stdin);
  freopen(fileOutName.c_str(), "w", stdout);
#endif
#endif
}

vector<ll> pow2;
vector<ll> P;
vector<ll> RP;

// 快速幂
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

// 模逆元，mod 必须为质数
ll inv(ll x, ll mod) { return qpow(x, mod - 2, mod); }

void Init() {
  pow2.resize(max4);
  pow2[0] = 1;
  for (int i = 1; i < max4; i++) {
    pow2[i] = (pow2[i - 1] * 2) % mod;
  }

  P.resize(max4);
  P[0] = 1;

  for (int i = 1; i < max4; i++) {
    P[i] = (P[i - 1] * i) % mod;
  }

  RP.resize(max4);
  for (int i = 0; i < max4; i++) {
    RP[i] = inv(P[i], mod);
  }
}
inline ll C(ll n, ll r) {
  //   return CC[n][r];
  if (n < r) return 0;
  ll Anr = P[n] * RP[n - r] % mod;
  return Anr * RP[r] % mod;
}

ll Solver(vector<ll>& A, const ll n, const ll m) {
  sort(A.begin(), A.end());
  // A: 1  ... z    ...  x    ... y     ...  n
  // B:    ... z(1) ...  y(2) ... x(1)  ...
  //  y > x + z
  //  y < 2 * x
  //  [y+1, n] 不管是 1 还是 2，都肯定会选择, 共 n-y 个
  //  y 的价钱是 2，没有选择
  //  [x+1,y-1] 只有价钱是 1 时才能选择，共 y-x-1 个
  //  x 的价钱是 1，选择的倒数第二个 1，剩余 1 元
  //  [z+1, x-1] 之间的价格都是 2，无法选择
  //  z 的价钱是 1，最后一个 1，剩余 0 元，有可能不存在
  ll ans = pow2[n];
  //   if (m == 1) {
  //     return ans;
  //   }
  for (int x = 1; x <= n; x++) {
    int z = 0;
    for (int y = x + 1; y <= n; y++) {
      if (A[y] == A[x]) continue;   // 不满足 y > x + z
      if (m - 2 < n - y) continue;  // [y+1, n] 需要全选，价格最低为 1，至少需要 n-y 元
      if (A[y] >= 2 * A[x]) break;  // 不满足 A[y] < 2 * A[x], 后续的都不满足
      // 找到最大的 z， 满足 A[z] + A[x] < A[y], 可以不选，即包括 z
      while (z < n && A[z + 1] + A[x] < A[y]) {
        z++;
      }
      // 已经构造出反例 A[z] + A[x] < A[y], [1,z-1] 这些价格可以是1也可以是2，共 2^z 种情况
      // [y+1, n] 先至少选择一个，剩余 (m-2) - (n-y) 元钱，共有 (n - y) + (y - x - 1) 个位置共选择
      const ll leftOne = (m - 2) - (n - y);
      const ll tmp = C((n - y) + (y - x - 1), leftOne) * pow2[z] % mod;
      ans = (ans - tmp + mod) % mod;
    }
  }

  return ans;
}

vector<ll> A;
void Solver() {  //
  Init();
  ll n, m;

  ll c, t;
  scanf("%lld%lld", &c, &t);
  while (t--) {
    scanf("%lld%lld", &n, &m);
    A.resize(n + 1);
    A[0] = 0;
    for (int i = 1; i <= n; i++) {
      scanf("%lld", &A[i]);
    }
    printf("%lld\n", Solver(A, n, m));
  }
}

#ifdef USACO_LOCAL_JUDGE
double costTime = 0;
#endif
void ExSolver() {
#ifdef USACO_LOCAL_JUDGE
  auto t1 = std::chrono::steady_clock::now();
#endif
  Solver();
#ifdef USACO_LOCAL_JUDGE
  auto t2 = std::chrono::steady_clock::now();
  auto my = std::chrono::duration_cast<std::chrono::duration<double, ratio<1, 1000>>>(t2 - t1);
  costTime = my.count();
#ifndef USACO_TASK_FILE
  printf("my 用时: %.0lfms\n", costTime);
#endif
#endif
}

#ifdef USACO_TASK_FILE
#include <unistd.h>

#include <cstdio>
int AC = 0;
void DiffAns(int stdout_fd, int i) {
  dup2(stdout_fd, STDOUT_FILENO);
  close(stdout_fd);
  stdout = fdopen(STDOUT_FILENO, "w");
  int fileIndex = i;
#ifdef TASKNO
  fileIndex = TASKNO;
#endif
  string fileAns = string(TASK) + to_string(fileIndex) + ".ans";
  string fileOut = string(TASK) + to_string(fileIndex) + ".out";
  string cmd = string("diff -w " + fileAns + " " + fileOut + " > /dev/null");
  if (system(cmd.c_str())) {
    printf("case %d: Wrong answer, cost %.0lfms\n", i, costTime);
  } else {
    if (costTime > MAX_TIME) {
      printf("case %d: Time Limit Exceeded, cost %.0lfms\n", i, costTime);
    } else {
      AC++;
      printf("case %d: Accepted, cost %.0lfms\n", i, costTime);
    }
  }
}
void DiffSummary(int stdout_fd) {  // 统计通过的用例数量和得分
  dup2(stdout_fd, STDOUT_FILENO);
  close(stdout_fd);
  stdout = fdopen(STDOUT_FILENO, "w");
  printf("Total: %d / %d, 得分： %d\n", AC, USACO_TASK_FILE, AC * (100 / USACO_TASK_FILE));
}
#endif
int main(int argc, char** argv) {
  CheckUsacoTask();
  int fileIndex = 1;
#ifdef USACO_TASK_FILE
  // 保存当前的 stdout 文件指针
  int stdout_fd = dup(STDOUT_FILENO);
  for (int i = 1; i <= USACO_TASK_FILE; i++) {
    fileIndex = i;
#endif
    InitIO(fileIndex);
    ExSolver();
#ifdef USACO_TASK_FILE
    fclose(stdout);
    DiffAns(stdout_fd, i);
    stdout_fd = dup(STDOUT_FILENO);
  }
  DiffSummary(stdout_fd);
#endif
  return 0;
}
